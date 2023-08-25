import sys, time

from Aria.SDK import Instrument, Error, StepList
from Aria.SDK import Monitoring, FlowControl, Configuration, Sequence, Enums
from Aria.SDK import ErrorSeverity, FlowRatePreset, SignalType

def DisplayError(error):
    severity = Error.GetErrorSeverity(error)
    if severity.value__ == 0:
        print(f"[INFO] - {Error.GetErrorTimestamp(error)} - {Error.GetErrorMessage(error)}")
    elif severity == ErrorSeverity.Warning:
        print(f"[WARNING] - {Error.GetErrorTimestamp(error)} - {Error.GetErrorMessage(error)}")
    elif severity == ErrorSeverity.Error:
        print(f"[Error] - {Error.GetErrorTimestamp(error)} - {Error.GetErrorMessage(error)}")


# INITIALIZATION
success, error = Instrument.LoadPhysicalInstrument()
if (success):
    print("Instrument detected and loaded")
else:
    DisplayError(error)
    error = Instrument.LoadSimulatedInstrument(Enums.FlowUnitType.L, Enums.SwitchType.MSwitch)
    if error != -1:
        DisplayError(error)
        sys.exit(0)
    print("Using a simuated instrument")

print("Set pressure to 0 - Take remote control")
error = FlowControl.SetPressureOrder(0)
DisplayError(error)


# SEQUENCE GENERATION
print("=== Generating Sequence ===")

error = Sequence.EnablePrefill(True)
if error != -1 : DisplayError(error)
error = Configuration.SetPrefillAndPreloadFlowRate(FlowRatePreset.Max)
if error != -1 : DisplayError(error)
print("Config defined")

error = StepList.InsertVolumeInjectionStep(-1, 1, 1, 500, 100, True, SignalType.TTL, False, SignalType.TTL)
print("Volume injection defined")
if error != -1 : DisplayError(error)
error = StepList.InsertWaitUserStep(-1, 3600, False, SignalType.TTL, False, SignalType.TTL)
print("Wait defined")
if error != -1 : DisplayError(error)
error = StepList.InsertTimedInjectionStep(-1, 1, 1, 200, 60, False, SignalType.TTL, False, SignalType.TTL)
print("Timed injection defined")
if error != -1 : DisplayError(error)
print('=== Sequence generated ===')

# SEQUENCE EXECUTION
print("\n=== Start sequence ===")
error = Sequence.StartSequence()
if error != -1 : DisplayError(error)
running = False
# Wait for the sequence to REALLY start
while not running:
    time.sleep(0.5)
    running, error = Monitoring.IsSequenceRunning()

# Enter the sequence loop
finished = False
while not finished:
    time.sleep(0.5)
    finished, error = Monitoring.HasSequenceEnded()
    currentStep, error = Monitoring.GetCurrentStep()
    
    if currentStep == Monitoring.GetPrefillStepNumber():
        progress, error = Monitoring.GetPrefillAndPreloadProgress()
        if error != -1 : DisplayError(error)
        print(progress)
        print(f"Prefill: {progress:.2f}%")
    elif currentStep == Monitoring.GetPreloadStepNumber():
        progress, error = Monitoring.GetPrefillAndPreloadProgress()
        if error != -1 : DisplayError(error)
        print(f"Preload: {progress:.2f}%")
    else:
        progress, error = Monitoring.GetProgress(currentStep)
        if error != -1 : DisplayError(error)
        print(f"Step {currentStep}: {progress:.2f}%")    
    
    currentPressure, error = FlowControl.GetMeasuredPressure()
    if error != -1: DisplayError(error)
    currentFlowrate, error = FlowControl.GetMeasuredFlowRate()
    if error != -1: DisplayError(error)
        
    print(f"[{str(currentStep)}] Progress: {str(round(progress,2))} % | Pressure: {round(currentPressure,2)} mbar, Flowrate: {round(currentFlowrate,2)}")
        
    paused, error = Monitoring.IsSequencePaused()
    if error != -1: DisplayError(error)

    if paused:
        next = input(f"Paused. Press any key to continue.")
        Monitoring.ResumeSequenceExecution()
        if error != -1: DisplayError(error)

    errorId, error = Error.TryGetNextAsyncError()
    while errorId:
        DisplayError(errorId)
        errorId = Error.TryGetNextAsyncError()

print("\n=== End of sequence ===")

input("End of execution. Press any key to close.")

