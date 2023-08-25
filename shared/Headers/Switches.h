#pragma once

namespace AriaSDK
{
	// Functions in this class that need to move a Switch require the Aria Instrument to be in Remote Control Mode.
	// To enter into Remote Control Mode, use the FlowControl::SetPressureOrder() function.
	class _declspec(dllexport) Switches
	{
	public:
		// (Remote Control) Switch the Internal M-Switch to connect to the given [reservoirNumber] (1 - 10).
		static void SelectReservoir(int reservoirNumber, int &errorID);
		// Return the currently selected reservoir.
		static int GetSelectedReservoir(int &error);

		// (Remote Control) Switch the Internal 2-Switch to stop or allow flow.
		static void StopFlow(bool stop, int &error);
		// Return true if the flow is stopped by the Internal 2-Switch, false if it is open.
		static bool IsFlowStopped(int &error);

		// Returns the maximum Port Number of the External Switch (2-Switch: 2 | M-Switch: 10)
		static int GetExternalSwitchMaxReachablePort(int &error);
		// (Remote Control) Switch the External Switch the given Chip [port]
		static void SetExternalSwitchPort(int port, int &error);
		// Returns the current Chip Port of the External Switch.
		static int GetCurrentExternalSwitchPort(int &error);

		// Enable or Disable the given External Switch [port]
		// Enabled ports can be used in Sequences as well as Calibration and Cleaning Procedures.
		static void SetEnabledPort(int port, bool enabled, int &error);
		// Returns true if the External Switch [port] is Enabled, false otherwise.
		static bool IsPortEnabled(int port, int &error);

		// Returns the External Switch Port Number of the Waste Port. (2-Switch: 2 | M-Switch: 10)
		static int GetWastePort(int &error);
		// Returns the External Switch Port Number of the Default Output Port. (2-Switch: 1 | M-Switch: 1)
		static int GetDefaultOutputPort(int &error);
	};
}