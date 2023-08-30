#pragma once

#include "Enums.h"

namespace AriaSDK
{
	class _declspec(dllexport) Instrument
	{
	public:
		// Searches for a connected Aria Instrument and loads it.
		// By Default, a Simulated Instrument is loaded with a 2-Switch and an Unknown Flow Unit Type.
		static bool LoadPhysicalInstrument(int &error);
		// Load a Simulated Instrument with the given [flowUnit] and [externalSwitch] types.
		static void LoadSimulatedInstrument(FlowUnitType flowUnit, SwitchType externalSwitch, int &error);
		// Returns true if the currently loaded instrument is Simulated, false otherwise.
		static bool IsInstrumentSimulated(int &error);
		
		// Returns the current Instrument Flow Unit Type.
		static FlowUnitType GetFlowUnitType(int &error);
		// Returns the current Instrument External Switch Type.
		static SwitchType GetExternalSwitchType(int &error);
		// Returns the Aria Instrument Serial Number.
		static int GetAriaSerialNumber(int &error);
		static int GetFirmwareVersion(int &error);
		static int GetFlowEZFirmwareVersion(int &error);

		// Returns the Minimum Flow Rate Order allowed by the current Instrument.
		static float GetMinFlowRate(int &error);
		// Returns the Maximum Flow Rate Order allowed by the current Instrument.
		static float GetMaxFlowRate(int &error);
		// Returns the Minimum Pressure Order allowed by the current Instrument.
		static float GetMinPressure(int &error);
		// Returns the Maximum Pressure Order allowed by the current Instrument.
		static float GetMaxPressure(int &error);

		// Checks if all the hardware components are detected and working.
		static bool CheckHardware(int &error);
	};
}