#pragma once
#include <string>
#include "Enums.h"

namespace AriaSDK
{
	// Almost all functions of the Aria SDK return an [error:int] ID by reference as their last parameter.
	// [-1] indicates that no error was detected and should be the default value.
	class _declspec(dllexport) Error
	{
	public:
		// Returns the Message of the Error with identifier: [errorID]
		static char* GetErrorMessage(int errorID);
		// Returns the Severity of the Error with identifier: [errorID]
		static ErrorSeverity GetErrorSeverity(int errorID);
		// Returns timestamp at which the error [errorID] occured.
		static char* GetErrorTimestamp(int errorID);
		// Deletes all previous Error records.
		// Next Error ID will be [0]
		static void ResetErrors();

		// Checks if there are unhandled async errors.
		static bool HasAsyncError();
		// Returns the number of async errors still unhandled.
		static int GetAsyncErrorCount();
		// If there are async errors, returns true and the identifier of the oldest async error by reference.
		// That error is considered handled.
		static bool TryGetNextAsyncError(int &errorID);
	};
}