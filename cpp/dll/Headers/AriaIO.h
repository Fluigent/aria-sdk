#pragma once
#include <string>
#include "Enums.h"

namespace AriaSDK
{

	class _declspec(dllexport) AriaIO
	{
	public:
		// Send a TTL Signal through the Aria Instrument
		static void SendTTLSignal(int &error);
		// Start waiting for a TTL signal. TTL check is done every [period:ms] milliseconds (adapt according to incoming TTL pulse duration)
		static void StartAwaitingTTLSignal(int period, int &error);
		// Start waiting for a TTL signal. TTL check is done every [period:ms] milliseconds (adapt according to incoming TTL pulse duration)
		// Stops awaiting after the [timeout:ms] is over.
		static void StartAwaitingTTLSignal(int period, int timeout, int &error);
		// Checks if a TTL signal was received. If it was, stops the current TTL waiting process
		static bool CheckTTLSignal(int &error);
		// Stop the current TTL waiting process
		static void StopAwaitingTLL(int &error);

		// Define the duration of the TTL pulse sent by the Aria Instrument (TTL pulse = [duration] * 100ms)
		static void SetTTLPulseDuration(int duration, int &error);
		// Get the current duration of the TTL pulse sent by the Aria Instrument. (TTL pulse = [duration] * 100ms)
		static int GetTTLPulseDuration(int &error);

		// Send a TCP Text Message
		static void SendTCPMessage(std::string message, int &error);
		// Start waiting for a TCP Message with the content [awaitedMessage]
		static void StartAwaitingTCPMessage(std::string awaitedMessage, int &error);
		// Checks if a TCP message with the content [awaitedMessage] was received
		// If it was, stops the process waiting for this message
		static bool CheckTCPMessage(std::string awaitedMessage, int &error);
		// Stop waiting for a TCP message with the content [awaitedMessage]
		static void StopAwaitingTCPMessage(std::string awaitedMessage, int &error);

		// Set TCP Mode : Servor or Client
		static void SetTCPMode(bool enableServer, int &error);
		// Checks if Aria is in TCP Server mode
		static bool IsTCPServerMode(int &error);
		// Define the TCP port used for the TCP Client and Server
		static void SetTCPPort(int port, int &error);
		// Retrieve the current TCP port used for the TCP Client and Server
		static int GetTCPPort(int &error);
	};
}