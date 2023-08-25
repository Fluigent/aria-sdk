import json, warnings, os
import clr

from aria_sdk import Sequence as SDK_Sequence
from aria_sdk import StepList, Step, Configuration
from aria_sdk.Enums import ErrorSeverity, FlowRatePreset, FlowUnitType, SignalType, StepParameter, StepType, SwitchType
from System import DateTime

class Sequence(SDK_Sequence):

    def GenerateSequenceJSON():
        def GenerateDuration(seconds):
            m, s = divmod(seconds, 60)
            h, m = divmod(m, 60)
            d, h = divmod(h, 24)
            durationSTR = "{:d}.{:02d}:{:02d}:{:02d}".format(d, h, m, s)
            return durationSTR


        # Saving progress trackers
        currentProperty = ""
        currentStep = -1

        try:
            seq, error = SDK_Sequence.GetSequenceObject()
            if (error != -1):
                return '', error
            
            # Child Objects
            currentProperty = "Reservoirs"
            reservoirs = []
            for reservoir in seq.Reservoirs:
                r = {}
                r["Reservoir"] = int(reservoir.Reservoir)
                r["Name"] = reservoir.Name
                r["Size"] = int(reservoir.Size)
                reservoirs.append(r)
            
            currentProperty = "PrefillStep"
            prefillStep = {}
            prefillStep["PrefillEnabled"] = seq.PrefillStep.PrefillEnabled

            # Step List
            listSteps = []
            for i in range(0, seq.Steps.Count):
                currentStep = i
                step = {}
                stepSource = seq.Steps[i]
                stepType, error = Step.GetStepType(i)

                if (stepType == StepType.Flush):
                    step["$type"] = "ClearTubing"
                    reservoir, error = Step.GetIntParameter(i, StepParameter.INPUT_RESERVOIR)
                    if (error != -1): return "", error
                    step["Reservoir"] = reservoir - 1
                    flowRate, error = Step.GetFloatParameter(i, StepParameter.FLOWRATE)
                    if (error != -1): return "", error
                    step["Qorder"] = str(flowRate) + " µl/min"
                    step["StringInjectionDestinations"] = ""
                    
                elif (stepType == StepType.VolumeInjection):
                    step["$type"] = "InjectVolume"
                    reservoir, error = Step.GetIntParameter(i, StepParameter.INPUT_RESERVOIR)
                    if (error != -1): return "", error
                    step["Reservoir"] = reservoir - 1
                    flowRate, error = Step.GetFloatParameter(i, StepParameter.FLOWRATE)
                    if (error != -1): return "", error
                    step["Qorder"] = str(flowRate) + " µl/min"
                    volume, error = Step.GetFloatParameter(i, StepParameter.VOLUME)
                    if (error != -1): return "", error
                    step["Volume"] = str(volume) + " µl"
                    destination, error = Step.GetIntParameter(i, StepParameter.OUTPUT_DESTINATION)
                    if (error != -1): return "", error
                    step["StringInjectionDestinations"] = destination
                elif (stepType == StepType.TimeInjection):
                    step["$type"] = "InjectTime"
                    reservoir, error = Step.GetIntParameter(i, StepParameter.INPUT_RESERVOIR)
                    if (error != -1): return "", error
                    step["Reservoir"] = reservoir - 1
                    flowRate, error = Step.GetFloatParameter(i, StepParameter.FLOWRATE)
                    if (error != -1): return "", error
                    step["Qorder"] = str(flowRate) + " µl/min"
                    destination, error = Step.GetIntParameter(i, StepParameter.OUTPUT_DESTINATION)
                    if (error != -1): return "", error
                    step["StringInjectionDestinations"] = destination
                    durationSeconds, error = Step.GetIntParameter(i, StepParameter.DURATION)
                    if (error != -1): return "", error
                    step["InjectionDuration"] = GenerateDuration(durationSeconds)

                elif (stepType == StepType.Wait):
                    step["$type"] = "Incubate"
                    durationSeconds, error = Step.GetIntParameter(i, StepParameter.DURATION)
                    if (error != -1): return "", error
                    step["Duration"] = GenerateDuration(durationSeconds)
                elif (stepType == StepType.WaitForUser):
                    step["$type"] = "WaitForUser"
                    durationSeconds, error = Step.GetIntParameter(i, StepParameter.DURATION)
                    if (error != -1): return "", error
                    step["Timeout"] = GenerateDuration(durationSeconds)
                elif (stepType == StepType.WaitForExternalSignal):
                    step["$type"] = "WaitForExternal"
                    signalType, error = Step.GetSignalTypeParameter(i, StepParameter.AWAITED_SIGNAL_TYPE)
                    if (error != -1): return "", error
                    step["SignalType"] = int(signalType)
                    backtrack, error = Step.GetBoolParameter(i, StepParameter.BACKTRACK)
                    if (error != -1): return "", error
                    step["BacktrackEnabled"] = backtrack
                    durationSeconds, error = Step.GetIntParameter(i, StepParameter.DURATION)
                    if (error != -1): return "", error
                    step["Timeout"] = GenerateDuration(durationSeconds)

                elif (stepType == StepType.SendExternalSignal):
                    step["$type"] = "SendExternalSignal"
                    step["SignalType"] = int(SignalType.TCP)
                    message, error = Step.GetStringParameter(i, StepParameter.SIGNAL_MESSAGE)
                    if (error != -1): return "", error
                    step["Message"] = message
                else:
                    error = -2
                    warnings.warn("Save File Generation Error: Unknown step type")
                    return "Save File Generation Error: Unknown step type", error
                
                # Generic Step Parameters
                step["Description"] = stepSource.Description
                step["Index"] = stepSource.Index
                step["StepNumber"] = stepSource.StepNumber
                step["TtlStart"] = stepSource.NotifyExternalSystemAtStart
                step["StartSignalType"] = int(stepSource.StartSignalType)
                step["TtlEnd"] = stepSource.NotifyExternalSystemAtEnd
                step["EndSignalType"] = int(stepSource.EndSignalType)
                step["IsEnabled"] = True
                listSteps.append(step)

            currentStep = -1
            serializableSeq = {}
            # Sequence Parameters
            currentProperty="UserComment"
            serializableSeq["UserComment"] = seq.UserComment
            currentProperty="Steps"
            serializableSeq["Steps"] = listSteps
            currentProperty="Reservoirs"
            serializableSeq["Reservoirs"] = reservoirs
            currentProperty="InjectionMethod"
            serializableSeq["InjectionMethod"] = int(seq.InjectionMethod)
            currentProperty="ZeroPressureBeforeSwitch"
            serializableSeq["ZeroPressureBeforeSwitch"] = seq.ZeroPressureBeforeSwitch
            currentProperty="BufferReservoir"
            serializableSeq["BufferReservoir"] = int(seq.BufferReservoir)
            currentProperty="StartAsap"
            serializableSeq["StartTime"] = seq.StartTime.ToString()
            currentProperty="StartAsap"
            serializableSeq["StartAsap"] = seq.StartAsap
            currentProperty="PrefillStep"
            serializableSeq["PrefillStep"] = prefillStep
            currentProperty="PreloadFlowRatePreset"
            serializableSeq["PreloadFlowRatePreset"] = int(seq.PreloadFlowRatePreset)

            currentProperty = ""
            sequenceJSON = json.dumps(serializableSeq, indent=2)
            return sequenceJSON, error
        except:
            message
            if (currentStep >= 0):
                message = "Sequence Saving Error: Error at Step " + str(currentStep)
            elif (currentProperty != ""):
                message = "Sequence Saving Error: Error when saving the property - " + currentProperty
            else:
                message = "Sequence Saving Error"
            warnings.warn(message)
            return message, -2
    
    def LoadSequenceFromJSON(sequenceJSON):
        def ParseQuantityValue(stringValue):
            # Split and Parse value and unit
            split = stringValue.split(" ")
            if (len(split) != 2):
                warnings.warn("Invalid Value Format")
                return 0, -2
            valueSTR = split[0]
            value = 0.0
            try:
                value = float(valueSTR)
            except ValueError:
                warnings.warn("Invalid Value Format")
                return 0, -2
            unit = split[1]
            
            # Apply unit multiplier to get µl or µl/min values
            if "/" in unit:
                # FLOW RATE
                if (unit == "µl/min" or unit == "\\u00b5l/min"):
                    return value, -1
                elif (unit == "nl/min"):
                    return value / 1000, -1
                elif (unit == "µl/s" or unit == "\\u00b5l/s"):
                    return value * 60, -1
                elif (unit == "µl/h" or unit == "\\u00b5l/h"):
                    return value / 60, -1
                elif (unit == "ml/min"):
                    return value * 1000, -1
                elif (unit == "ml/h"):
                    return (value * 1000) / 60, -1
                else:
                    warnings.warn("Unknown Flow Rate Value Unit")
                    return 0, -2
            else:
                # VOLUME
                if (unit == "µl" or unit == "\\u00b5l"):
                    return value, -1
                elif (unit == "nl"):
                    return value / 1000, -1
                elif (unit == "ml"):
                    return value * 1000, -1
                else:
                    warnings.warn("Unknown Volume Value Unit")
                    return 0, -2
        def ParseTime(timeSTR):
            try:
                splitTime = timeSTR.split(":")
                if (len(splitTime) != 3):
                    warnings.warn("Could not parse Time Value")
                    return 0, -2
                dayHourSTR = splitTime[0]
                minutes = int(splitTime[1])
                seconds = int(splitTime[2])
                splitDayHours = dayHourSTR.split(".")
                days = 0
                hours = 0
                if (len(splitDayHours) == 1):
                    hours = int(splitDayHours[0])
                elif (len(splitDayHours) == 2):
                    days = int(splitDayHours[0])
                    hours = int(splitDayHours[1])
                else:
                    warnings.warn("Could not parse Time Value")
                    return 0, -2
                return days*24*60*60 + hours*60*60 + minutes*60 + seconds, -1
            except ValueError:
                warnings.warn("Could not parse Time Value")
                return 0, -2
        
        try:
            error = -1
            sequenceDict = json.loads(sequenceJSON)
            seq, error = SDK_Sequence.GetSequenceObject()
            if (error != -1):
                return error

            # Sequence object-specific parameters setup
            for i, reservoir in enumerate(sequenceDict["Reservoirs"]):
                seq.Reservoirs[i].Name = reservoir["Name"]
            seq.PrefillStep.PrefillEnabled = sequenceDict["PrefillStep"]["PrefillEnabled"]
            seq.UserComment = sequenceDict["UserComment"]

            seq.ZeroPressureBeforeSwitch = sequenceDict["ZeroPressureBeforeSwitch"]
            seq.StartTime = DateTime.Parse(sequenceDict["StartTime"])
            seq.StartAsap = sequenceDict["StartAsap"]
            
            seq.Steps.Clear()
            error = SDK_Sequence.SetSequenceObject(seq)
            if (error != -1):
                return error
            
            # Called after the correct sequence object has been loaded
            error = SDK_Sequence.SetBufferReservoir(sequenceDict["BufferReservoir"])
            if (error != -1):
                return error
            error = Configuration.SetPrefillAndPreloadFlowRate(FlowRatePreset(sequenceDict["PreloadFlowRatePreset"]))
            if (error != -1):
                return error

            # Step List
            for index, step in enumerate(sequenceDict["Steps"]):
                
                signalStart = step["TtlStart"]
                signalStartType = SignalType(step["StartSignalType"])
                signalEnd = step["TtlEnd"]
                signalEndType = SignalType(step["EndSignalType"])
                
                stepType = step["$type"]
                # FLUSH
                if (stepType == "ClearTubing"):
                    reservoir = step["Reservoir"] + 1 # Reservoir store in BASE 0
                    flowRate, error = ParseQuantityValue(step["Qorder"])
                    if (error != -1):
                        warnings.warn("Unable to load Flush step at index " + str(index))
                        return error
                    error = StepList.InsertFlushStep(index, reservoir, flowRate, signalStart, signalStartType, signalEnd, signalEndType)
                    if (error != -1):
                        warnings.warn("Unable to load Flush step at index " + str(index))
                        return -2
                # VOLUME
                elif (stepType == "InjectVolume"):
                    reservoir = step["Reservoir"] + 1 # Reservoir store in BASE 0
                    step["Volume"]
                    volume, error = ParseQuantityValue(step["Volume"])
                    if (error != -1):
                        warnings.warn("Unable to load Volume Injection step at index " + str(index))
                        return error
                    flowRate, error = ParseQuantityValue(step["Qorder"])
                    if (error != -1):
                        warnings.warn("Unable to load Volume Injection step at index " + str(index))
                        return error
                    # Destination
                    destList = str(step["StringInjectionDestinations"]).split(", ")
                    if (len(destList) == 0):
                        warnings.warn("Unable to load Volume Injection step at index " + str(index))
                        return -2
                    destination = 1
                    try:
                        destination = int(destList[0])
                    except ValueError:
                        warnings.warn("Unable to load Volume Injection step at index " + str(index))
                        return -2
                    # Add Step
                    error = StepList.InsertVolumeInjectionStep(index, reservoir, destination, flowRate, volume, signalStart, signalStartType, signalEnd, signalEndType)
                    if (error != -1):
                        warnings.warn("Unable to load Volume Injection step at index " + str(index))
                        return -2
                    pass
                # TIMED
                elif (stepType == "InjectTime"):
                    reservoir = step["Reservoir"] + 1 # Reservoir store in BASE 0
                    flowRate, error = ParseQuantityValue(step["Qorder"])
                    if (error != -1):
                        warnings.warn("Unable to load Timed Injection step at index " + str(index))
                        return -2
                    duration, error = ParseTime(step["InjectionDuration"])
                    if (error != -1):
                        warnings.warn("Unable to load Timed Injection step at index " + str(index))
                        return -2
                    
                    # Destination
                    destList = str(step["StringInjectionDestinations"]).split(", ")
                    if (len(destList) == 0):
                        warnings.warn("Unable to load Timed Injection step at index " + str(index))
                        return -2
                    destination = 1
                    try:
                        destination = int(destList[0])
                    except ValueError:
                        warnings.warn("Unable to load Timed Injection step at index " + str(index))
                        return -2
                    # Add Step
                    error = StepList.InsertTimedInjectionStep(index, reservoir, destination, flowRate, duration, signalStart, signalStartType, signalEnd, signalEndType)
                    if (error != -1):
                        warnings.warn("Unable to load Timed Injection step at index " + str(index))
                        return -2
                # WAIT
                elif (stepType == "Incubate"):
                    duration, error = ParseTime(step["Duration"])
                    if (error != -1):
                        warnings.warn("Unable to load Wait step at index " + str(index))
                        return -2
                    # Add Step
                    error = StepList.InsertWaitStep(index, duration, signalStart, signalStartType, signalEnd, signalEndType)
                    if (error != -1):
                        warnings.warn("Unable to load Wait step at index " + str(index))
                        return -2
                # WAIT FOR USER
                elif (stepType == "WaitForUser"):
                    timeout, error = ParseTime(step["Timeout"])
                    if (error != -1):
                        warnings.warn("Unable to load Wait For User step at index " + str(index))
                        return -2
                    # Add Step
                    error = StepList.InsertWaitUserStep(index, timeout, signalStart, signalStartType, signalEnd, signalEndType)
                    if (error != -1):
                        warnings.warn("Unable to load Wait For User step at index " + str(index))
                        return -2
                # WAIT FOR SIGNAL
                elif (stepType == "WaitForExternal"):
                    signalType = SignalType(step["SignalType"])
                    timeout, error = ParseTime(step["Timeout"])
                    if (error != -1):
                        warnings.warn("Unable to load Wait For Signal step at index " + str(index))
                        return -2
                    backtrackEnabled = step["BacktrackEnabled"]
                    # Add Step
                    error = StepList.InsertWaitSignalStep(index, timeout, signalType, backtrackEnabled, signalStart, signalStartType, signalEnd, signalEndType)
                    if (error != -1):
                        warnings.warn("Unable to load Wait For Signal step at index " + str(index))
                        return -2
                # SEND SIGNAL
                elif (stepType == "SendExternalSignal"):
                    message = step["Message"]
                    # Add Step
                    error = StepList.InsertSendSignalStep(index, message, signalStart, signalStartType, signalEnd, signalEndType)
                    if (error != -1):
                        warnings.warn("Unable to load Send Signal step at index " + str(index))
                        return -2
                else:
                    warnings.warn("Invalid Step Type: " + stepType)
                    return -2

            return error
        except:
            warnings.warn("Sequence Loading Error")
            return -2
    
    def LoadSequence(filePath):
        try:
            sequenceJSON = ""
            if not os.path.isfile(filePath):
                warnings.warn("File not found")
                return -2
            file = open(filePath, "rb")
            sequenceJSON = file.read()
            return Sequence.LoadSequenceFromJSON(sequenceJSON)
        except:
            warnings.warn("Unable to load Sequence from given file path")
            return -2

