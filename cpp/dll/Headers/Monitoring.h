#pragma once
#include <string>
#include "Enums.h"

namespace AriaSDK
{

	class _declspec(dllexport) Monitoring
	{
	public:
		// Returns true if the current Sequence his in progress, false otherwise.
		// A paused Sequence is still Running.
		static bool IsSequenceRunning(int &error);
		// Pauses the Sequence.
		static void PauseSequence(int &error);
		// Returns true if the Sequence is paused, false otherwise.
		static bool IsSequencePaused(int &error);
		// Resume the execution of a paused Sequence.
		static void ResumeSequenceExecution(int &error);
		// Cancel the current Procedure or Sequence.
		static void Cancel(int &error);

		// Returns the Step Index of the Prefill Phase of the Sequence.
		static int GetPrefillStepNumber();
		// Returns the Step Index of the Preload Phase of the Sequence.
		static int GetPreloadStepNumber();
		// Returns the Step Index of the Step currently running. (base 1)
		static int GetCurrentStep(int &error);

		// Returns the Progress level (%) of the Step at [index]. (base 1)
		static float GetProgress(int index, int &error);
		// Returns the cumulated Progress for the Prefill and Preload phases.
		static float GetPrefillAndPreloadProgress(int &error);
		// Returns true if the Sequence execution ended.
		static bool HasSequenceEnded(int &error);
	};
}