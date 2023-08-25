using aria_sdk;
using System;
using System.Threading;

namespace aria_sdk_example
{
    internal class Program
    {
        static void Main(string[] args)
        {

            Instrument.LoadPhysicalInstrument(out int error);
            if (error != -1)
            {
                PrintError(error);
                Instrument.LoadSimulatedInstrument(aria_sdk.Enums.FlowUnitType.L, aria_sdk.Enums.SwitchType.MSwitch, out _);
            }
            var simulated = Instrument.IsInstrumentSimulated(out error);
            PrintError(error);
            if (simulated)
            {
                Console.WriteLine("Using a simulated instrument");
            }
            Configuration.SetPrefillAndPreloadFlowRate(aria_sdk.Enums.FlowRatePreset.Max, out _);
            var ttl = aria_sdk.Enums.SignalType.TTL;
            StepList.InsertVolumeInjectionStep(-1, 1, 1, 500.0f, 100.0f, false, ttl, false, ttl, out error);
            PrintError(error);
            StepList.InsertWaitUserStep(-1, 3600, false, ttl, false, ttl, out error);
            PrintError(error);
            StepList.InsertTimedInjectionStep(-1, 1, 1, 200.0f, 60, false, ttl, false, ttl, out error);
            PrintError(error);
            Sequence.StartSequence(out error);
            PrintError(error);
            var jsonString = Sequence.GenerateSequenceJSON(out error);
            PrintError(error);
            Console.WriteLine("Serialized sequence data:");
            Console.WriteLine(jsonString);
            Sequence.LoadSequenceFromJSON(jsonString, out error);
            PrintError(error);
            var finished = false;
            while (!finished)
            {
                finished = Monitoring.HasSequenceEnded(out error);
                PrintError(error);
                var step = Monitoring.GetCurrentStep(out error);
                PrintError(error);
                if (step == Monitoring.GetPrefillStepNumber())
                {
                    var progress = Monitoring.GetPrefillAndPreloadProgress(out error);
                    PrintError(error);
                    Console.WriteLine($"Prefill: {progress:F2}%");
                }
                else if (step == Monitoring.GetPreloadStepNumber())
                {
                    var progress = Monitoring.GetPrefillAndPreloadProgress(out error);
                    PrintError(error);
                    Console.WriteLine($"Preload: {progress:F2}%");
                }
                else
                {
                    var progress = Monitoring.GetProgress(step, out error);
                    PrintError(error);
                    Console.WriteLine($"Step {step}: {progress:F2}%");
                }
                var pressure = FlowControl.GetMeasuredPressure(out error);
                PrintError(error);
                var flowrate = FlowControl.GetMeasuredFlowRate(out error);
                PrintError(error);
                Console.WriteLine($"{pressure:F1} mbar, {flowrate:F1} µL/min");
                Thread.Sleep(TimeSpan.FromSeconds(1));
                var paused = Monitoring.IsSequencePaused(out error);
                PrintError(error);
                if (paused)
                {
                    Console.WriteLine($"Paused. Press any key to continue.");
                    Console.ReadKey(true);
                    Monitoring.ResumeSequenceExecution(out error);
                    PrintError(error);
                }
                while (Error.TryGetNextAsyncError(out error))
                {
                    PrintError(error);
                }
            }
            Console.WriteLine($"End of execution. Press any key to close.");
            Console.ReadKey(true);
        }
        static void PrintError(int error)
        {
            if (error != -1)
            {
                var timestamp = Error.GetErrorTimestamp(error);
                var severity = Error.GetErrorSeverity(error);
                var message = Error.GetErrorMessage(error);
                Console.WriteLine($"{timestamp}\t{severity}\t{message}");
                Error.ResetErrors();
            }
        }
    }
}
