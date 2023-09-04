#pragma once

namespace AriaSDK
{
	class _declspec(dllexport) FlowControl
	{
	public:
		// Set the Flow Rate Order of the Aria Instrument to [flowRate:µl/min].
		static void SetFlowRateOrder(float flowRate, int &error);
		// Returns the last Flow Rate Order sent to the Aria Instrument (in µl/min).
		static float GetFlowRateOrder(int &error);
		// Returns the current Flow Rate value measured by the Aria Instrument (in µl/min).
		static float GetMeasuredFlowRate(int &error);

		// Set the Pressure Order of the Aria Instrument to [pressure:mBar].
		// Also allows to Take Remote Control of the Aria Instrument.
		static void SetPressureOrder(float pressure, int &error);
		// Returns the last Pressure Order sent to the Aria Instrument (in mBar).
		static float GetPressureOrder(int &error);
		// Returns the current Pressure value measured by the Aria Instrument (in mBar).
		static float GetMeasuredPressure(int &error);
	};
}