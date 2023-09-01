#pragma once

namespace AriaSDK
{
    enum SignalType : int
    {
        TTL = 0,
        TCP = 1,
    };

	enum FlowRatePreset : int
	{
		Precision = 0,	// Flow Unit M: 30 µl/min | Flow Unit L: 50 µl/min
		Balanced = 1,	// Flow Unit M: 55 µl/min | Flow Unit L: 250 µl/min
		Fast = 2,		// Flow Unit M: 80 µl/min | Flow Unit L: 500 µl/min
		Max = 3,		// Flow Unit M: 80 µl/min | Flow Unit L: 1000 µl/min
	};

	enum ErrorSeverity : int
	{
		None = 0,
		Warning = 1,
		Error = 2,
	};
	
	enum FlowUnitType : int
	{
		UnknownFlowUnit = 0,
		XS = 1,
		S = 2,
		M = 4,
		L = 8,
		XL = 16,
		MPLUS = 32,
		LPLUS = 64,
	};

	enum SwitchType : int
	{
		UnknownSwitch = 0,
		TwoSwitch = 1,
		MSwitch = 2,
	};

	enum StepType : int
	{
		Flush = 0,
		TimeInjection = 1,
		VolumeInjection = 2,
		Wait = 3,
		WaitForUser = 4,
		WaitForExternalSignal = 5,
		SendExternalSignal = 6,
	};

	enum StepParameter : int
	{
		PRE_SIGNAL = 0, // bool
		PRE_SIGNAL_TYPE = 1, // SignalType
		POST_SIGNAL = 2, // bool
		POST_SIGNAL_TYPE = 3, // SignalType
		INPUT_RESERVOIR = 4, // int
		OUTPUT_DESTINATION = 5, // int
		FLOWRATE = 6, // float (µl/min)
		VOLUME = 7, // float (µl)
		DURATION = 8, // int (seconds)
		SIGNAL_MESSAGE = 9, // string
		AWAITED_SIGNAL_TYPE = 10, // SignalType
		BACKTRACK = 11, // bool
	};

	enum CalibrationState : int
	{
		NotRunning = 0,
		Flushing = 1,
		SettingUp = 2,
		Calibrating = 3,
	};

}
