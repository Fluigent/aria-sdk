#pragma once
#include <string>
#include <vector>
#include "Enums.h"

namespace AriaSDK
{
	class _declspec(dllexport) Procedures
	{
	public:
		// Start the step 1 of calibration. Reservoir 1 should be empty, Reservoir 10 should be filled with water.
		// Once the calibration is over (GetCalibrationState() => NotRunning), GetLastMeasuredCalibrationVolume() will return the calibration value.
		static void StartCalibrationStep1(int &error);
		// Start the step 2 of calibration. Reservoir 1 should be empty, Reservoir 10 should be filled with water.
		// The tubing should be unplugged from the external Switch.
		// When the water reaches the end of the unplugged tubing, call ValidateCalibration() and then GetLastMeasuredCalibrationVolume().
		static void StartCalibrationStep2(int &error);
		// Start the step 3 of calibration when the external switch is a 2-Switch. Reservoir 1 should be empty, Reservoir 10 should be filled with water.
		// The tubing shoud be unplugged from the chip.
		// When the water reaches the end of the unplugged tubing, call ValidateCalibration() and then GetLastMeasuredCalibrationVolume().
		static void StartCalibrationStep3_2Switch(int &error);
		// Start the step 3 of calibration for the given [port] of the external M-Switch. Reservoir 1 should be empty, Reservoir 10 should be filled with water.
		// The tubing should be unplugged from the chip.
		// When the water reaches the end of the unplugged tubing, call ValidateCalibration() and then GetLastMeasuredCalibrationVolume().
		static void StartCalibrationStep3_MSwitch(int port, int &error);
		// Returns the last volume measured during a calibration procedure.
		// Allows to monitor the current calibration measurements and then get the final calibration value.
		static float GetLastMeasuredCalibrationVolume(int &error);
		// Returns the state of the current calibration if one is running, NotRunning otherwise.
		static CalibrationState GetCalibrationState(int &error);
		// Validate that the current calibration is complete (for steps 2 and 3 requiring user input to end the step).
		static void ValidateCalibration(int &error);
		// Stops the current calibration.
		static void CancelCalibration(int &error);

		// Start the Step 1 of the Cleaning Procedure : the cleaned [reservoirNumbers] should be filled with Water,
		// as well as the [bufferReservoirNumber] (9 - 10).
		static void StartCleaning1_Water(std::vector<int> reservoirNumbers, int count, int bufferReservoirNumber, int &error);
		// Start the Step 2 of the Cleaning Procedure : the cleaned [reservoirNumbers] should be filled with Tergazyme,
		// as well as the [bufferReservoirNumber] (9 - 10).
		static void StartCleaning2_Tergazyme(std::vector<int> reservoirNumbers, int count, int bufferReservoirNumber, int &error);
		// Start the Step 3 of the Cleaning Procedure : the cleaned [reservoirNumbers] should be emptied,
		// as well as the [bufferReservoirNumber] (9 - 10).
		static void StartCleaning3_Air(std::vector<int> reservoirNumbers, int count, int bufferReservoirNumber, int &error);
		// Start the Step 4 of the Cleaning Procedure : the cleaned [reservoirNumbers] should be filled with IPA,
		// as well as the [bufferReservoirNumber] (9 - 10).
		static void StartCleaning4_IPA(std::vector<int> reservoirNumbers, int count, int bufferReservoirNumber, int &error);
		// Start the Step 5 of the Cleaning Procedure : the cleaned [reservoirNumbers] should be emptied,
		// as well as the [bufferReservoirNumber] (9 - 10).
		static void StartCleaning5_Air(std::vector<int> reservoirNumbers, int count, int bufferReservoirNumber, int &error);
	};
}