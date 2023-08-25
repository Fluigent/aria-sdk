#pragma once
#include <string>
#include "Enums.h"

namespace AriaSDK
{

	class _declspec(dllexport) Step
	{
	public:
		// Returns the estimated delay (in seconds) before the Step at [index] is executed.
		static int GetEstimatedStepStartTime(int index, int &error);
		// Returns the estimated duration (in seconds) of the Step at [index].
		static int GetEstimatedStepDuration(int index, int &error);
		// Returns the Step Type of the Step at [index].
		static StepType GetStepType(int index, int &error);

		// Set the Parameter for the step at [index] with the given [value:int].
		static void SetParameter(int index, StepParameter parameterType, int value, int &error);
		// Set the Parameter for the step at [index] with the given [value:bool].
		static void SetParameter(int index, StepParameter parameterType, bool value, int &error);
		// Set the Parameter for the step at [index] with the given [value:float].
		static void SetParameter(int index, StepParameter parameterType, float value, int &error);
		// Set the Parameter for the step at [index] with the given [value:string].
		static void SetParameter(int index, StepParameter parameterType, std::string value, int &error);
		// Set the Parameter for the step at [index] with the given [value:SignalType].
		static void SetParameter(int index, StepParameter parameterType, SignalType value, int &error);

		// Returns the Parameter value (int) according to the [parameterType] for the step at [index]
		static int GetIntParameter(int index, StepParameter parameterType, int &error);
		// Returns the Parameter value (bool) according to the [parameterType] for the step at [index]
		static bool GetBoolParameter(int index, StepParameter parameterType, int &error);
		// Returns the Parameter value (float) according to the [parameterType] for the step at [index]
		static float GetFloatParameter(int index, StepParameter parameterType, int &error);
		// Returns the Parameter value (string) according to the [parameterType] for the step at [index]
		static std::string GetStringParameter(int index, StepParameter parameterType, int &error);
		// Returns the Parameter value (SignalType) according to the [parameterType] for the step at [index]
		static SignalType GetSignalTypeParameter(int index, StepParameter parameterType, int &error);
	};
}