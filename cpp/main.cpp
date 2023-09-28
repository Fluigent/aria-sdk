#include <iostream>
#include <fstream>

#include <Windows.h>
#include "AriaSDK.h"

void DisplayError(int errorID)
{
    if (errorID == -1)
    {
        return;
    }
    std::cout << "Error ID:" << errorID << "\n";
    AriaSDK::ErrorSeverity severity = AriaSDK::Error::GetErrorSeverity(errorID);
    char* errorMessage = AriaSDK::Error::GetErrorMessage(errorID);
    switch (severity)
    {
    case AriaSDK::Warning:
        std::cout << "[Warning] " << errorMessage << "\n";
        break;
    case AriaSDK::Error:
        std::cout << "[Error] " << errorMessage << "\n";
        break;
    case AriaSDK::None:
    default:
        std::cout << "[None] " << errorMessage << "\n";
        break;
    }
    AriaSDK::Helper::Free(errorMessage);
}

void GenerateAndStartSequence()
{
    int errorID = -1;
    bool detected = AriaSDK::Instrument::LoadPhysicalInstrument(errorID);
    if (detected)
    {
        std::cout << "Instrument Detected\n";
    }
    else
    {
        DisplayError(errorID);
        std::cout << "No Instrument Detected\n";
    }
    std::cout << "------------\n";

    std::cout << "SetPressureOrder(0) - Take Remote Control\n";
    AriaSDK::FlowControl::SetPressureOrder(0, errorID);
    DisplayError(errorID);
    std::cout << "------------\n";

    std::cout << "Generating Sequence\n";
    AriaSDK::Sequence::EnablePrefill(false, errorID);
    DisplayError(errorID);
    AriaSDK::Configuration::SetPrefillAndPreloadFlowRate(AriaSDK::FlowRatePreset::Max, errorID);
    DisplayError(errorID);
    AriaSDK::StepList::InsertVolumeInjectionStep(0, 2, 1, 500, 100, true, AriaSDK::SignalType::TTL, false, AriaSDK::SignalType::TTL, errorID);
    DisplayError(errorID);
    AriaSDK::StepList::InsertWaitStep(1, 10, true, AriaSDK::SignalType::TTL, false, AriaSDK::SignalType::TTL, errorID);
    DisplayError(errorID);
    AriaSDK::StepList::InsertTimedInjectionStep(2, 3, 1, 200, 60, true, AriaSDK::SignalType::TTL, false, AriaSDK::SignalType::TTL, errorID);
    DisplayError(errorID);
    std::cout << "------------\n";

    std::cout << "Start...\n";
    AriaSDK::Sequence::StartSequence(errorID);
    DisplayError(errorID);

    // Sequence Starting
    while (!AriaSDK::Monitoring::HasSequenceEnded(errorID))
    {
        Sleep(500);
        int currentStep = AriaSDK::Monitoring::GetCurrentStep(errorID);
        if (currentStep >= 0)
        {
            // Regular Sequence Steps
            std::cout << "[" << currentStep << "] Progress: " << AriaSDK::Monitoring::GetProgress(currentStep, errorID) << "\n";
        }
        else
        {
            // Preload & Prefill
            std::cout << "[" << currentStep << "] Progress: " << AriaSDK::Monitoring::GetPrefillAndPreloadProgress(errorID) << "\n";
        }
    }
}

int main()
{
    GenerateAndStartSequence();
}