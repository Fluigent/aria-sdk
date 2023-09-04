#pragma once
#include <string>
#include "Enums.h"

namespace AriaSDK
{
	class _declspec(dllexport) StepList
	{
	public:
		// Returns the total number of Steps in the Sequence.
		static int GetSequenceStepCount(int &error);
		// Removes the Step at [index] from the sequence.
		static bool RemoveStep(int index, int &error);
		
		// Insert a Flush Step at [index]
		static void InsertFlushStep(int index, int inputReservoir, float flowRate, bool preSignal, SignalType preSignalType, bool postSignal, SignalType postSignalType, int &error);
		// Insert a Send Signal Step at [index]
		static void InsertSendSignalStep(int index, std::string message, bool preSignal, SignalType preSignalType, bool postSignal, SignalType postSignalType, int &error);
		// Insert a Time Injection Step at [index]
		static void InsertTimedInjectionStep(int index, int inputReservoir, int destination, float flowRate, int duration_s, bool preSignal, SignalType preSignalType, bool postSignal, SignalType postSignalType, int &error);
		// Insert a Volume Injection Step at [index]
		static void InsertVolumeInjectionStep(int index, int inputReservoir, int destination, float flowRate, float volume, bool preSignal, SignalType preSignalType, bool postSignal, SignalType postSignalType, int &error);
		// Insert a Wait Step at [index]
		static void InsertWaitStep(int index, int duration_s, bool preSignal, SignalType preSignalType, bool postSignal, SignalType postSignalType, int &error);
		// Insert a Wait for User confirmation Step at [index]
		static void InsertWaitUserStep(int index, int timeout_s, bool preSignal, SignalType preSignalType, bool postSignal, SignalType postSignalType, int &error);
		// Insert a Wait For External Signal (TTL/TCP) Step at [index]
		static void InsertWaitSignalStep(int index, int timeout_s, SignalType signalType, bool enableBacktrack, bool preSignal, SignalType preSignalType, bool postSignal, SignalType postSignalType, int &error);
	};
}