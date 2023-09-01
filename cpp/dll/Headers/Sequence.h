#pragma once
#include <string>

namespace AriaSDK
{
	class _declspec(dllexport) Sequence
	{
	public:
		// Start the current Sequence.
		static void StartSequence(int &error);

		// Returns the Sequence saved as a JSON string.
		static std::string GenerateSequenceJSON(int &error);
		// Load Sequence from the file at [filePath]
		static void LoadSequence(std::string filePath, int &error);
		// Load Sequence from a JSON String.
		static void LoadSequenceFromJSON(std::string jsonString, int &error);

		// Returns the reservoir used to store the buffer solution.
		static int GetBufferReservoir(int &error);
		// Define the reservoir used to store the buffer solution.
		static void SetBufferReservoir(int reservoirNumber, int &error);
		// Returns the estimated required volume with which to fill the given Reservoir before starting the Sequence.
		static float GetReservoirEstimatedRequiredVolume(int reservoirNumber, int &error);
		// Returns True if the required volume for the given Reservoir is above that Reservoir Capacity, false otherwise.
		// Reservoirs over capacity will require to refill them during the Sequence Execution.
		static bool IsReservoirEstimatedOverCapacity(int reservoirNumber, int &error);

		// Enable or disable the Prefill phase at the begining of the Sequence.
		// The Prefill fills the tubing between the Reservoir and the Internal M-Switch.
		// Prefill can be safely disabled only if the tubing is already filled with the correct content.
		static void EnablePrefill(bool enabled, int &error);
		// Returns True if Prefill is enabled, false otherwise.
		static bool IsPrefillEnabled(int &error);

		// Enable or Disable Zero Pressure Mode.
		// Zero Pressure Mode forces the pressure to reset to 0 every time a Switch is moved
		// to avoid flow rate spikes, irregularities, etc.
		static void EnableZeroPessureMode(bool enabled, int &error);
		// Returns True if Zero Pressure Mode is enabled, false otherwise.
		static bool IsZeroPressureModeEnabled(int &error);

		// Define if the the Sequence must start as soon as possible, or with a delay.
		static void SetSequenceStartASAP(bool startASAP, int &error);
		// Returns True if Start ASAP is enabled, false otherwise.
		static bool IsSequenceStartingASAP(int &error);
		// Define the time at which the Sequence will be executed if Start ASAP is disabled. 
		static void SetSequenceStartTime(std::string dateTime, int &error);
		
		// Returns the estimated start time of the first Step of the Sequence.
		static std::string GetSequenceStartTime(int &error);
		// Returns the estimated total duration of the Sequence.
		static int GetTotalDuration(int &error);
	};
}