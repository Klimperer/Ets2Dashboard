// TestApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>

#include "../TelemetryProvider/MappedTelemetryData.h"

float MetersPerSecondToKilometersPerHour(float metersPerSecond)
{
    return metersPerSecond * 3.6f;
}

void DisplaySpeedFromMappedFile()
{
    auto mappedFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,           // use paging file
        NULL,                           // default security
        PAGE_READWRITE,                 // read/write access
        0,                              // maximum object size (high-order DWORD)
        sizeof(MappedTelemetryData),    // maximum object size (low-order DWORD)
        L"SCS_Telemetry_Data_OG");      // name of mapping object

    while (true)
    {
        auto filePtr = MapViewOfFile(mappedFile, FILE_MAP_READ, 0, 0, sizeof(MappedTelemetryData));

        MappedTelemetryData* data = (MappedTelemetryData*)filePtr;

        if (data->gamePaused)
        {
            std::cout << "The game is paused ..." << std::endl;
        }
        else
        {
            std::cout << "You're driving " << MetersPerSecondToKilometersPerHour(data->speed) << " kph" << std::endl;
        }

        UnmapViewOfFile(filePtr);

        Sleep(20);
    }

    CloseHandle(mappedFile);
}

int _tmain(int argc, _TCHAR* argv[])
{
    //auto mmf = new MemoryMappedFile();
    //auto mapped = mmf->IsFileMapped();

    //MappedTelemetryData data;
    //data.speed = 12.34f;

    //mmf->UpdateMappedFile(data);

    //delete mmf;

    while (true)
    {
        DisplaySpeedFromMappedFile();
    }
}
