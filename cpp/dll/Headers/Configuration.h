#pragma once
#include <string>
#include <vector>
#include "Enums.h"

namespace AriaSDK
{
	class _declspec(dllexport) Configuration
	{
	public:
		// Returns the DateTime format used in Aria SDK functions.
		static char* GetDateTimeFormat();

		// Define the Prefill and Preload Flow Rate from the given [flowRatePreset].
		static void SetPrefillAndPreloadFlowRate(FlowRatePreset flowRatePreset, int &error);
		// Returns the current Prefill and Preload flow rate preset.
		static FlowRatePreset GetPrefillAndPreloadFlowRatePreset(int &error);
		// Returns the current Prefill and Preload flow rate (in µl/min).
		static float GetPrefillAndPreloadFlowRate(int &error);

		// Define the Calibration value [volume:µl] of Calibration Steps 1 or 2.
		static void SetCalibrationValue(int step, float volume, int &error);
		// Define the Calibration value [volume:µl] of Calibration Steps 3 for the given [step3Port].
		static void SetStep3CalibrationValue(int step3Port, float volume, int &error);
		// Returns [step1] and [step2] Calibration values by reference.
		static void GetCalibrationValues(float &step1, float &step2, int &error);
		// Returns a vector containing the Step 3 Calibration values for all Chip Ports.
		static float* GetStep3CalibrationValues(int& calibrationValuesCount, int &error);
		// Returns the maximum number of calibration values in the Calibration Step 3 table.
		static int GetMaxStep3CalibrationValueCount();
	};
}