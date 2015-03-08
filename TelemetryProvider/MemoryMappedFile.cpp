#include "MemoryMappedFile.h"

#include <Windows.h>
#include "MappedTelemetryData.h"

MemoryMappedFile::MemoryMappedFile()
{
    _mappedFile = NULL;
    CreateMapping();
}

MemoryMappedFile::~MemoryMappedFile()
{
    CloseMapping();
    _mappedFile = NULL;
}

bool MemoryMappedFile::IsFileMapped()
{
    return (_mappedFile != NULL);
}

void MemoryMappedFile::UpdateMappedFile(MappedTelemetryData& newData)
{
    auto filePtr = MapViewOfFile(_mappedFile, FILE_MAP_WRITE, 0, 0, sizeof(MappedTelemetryData));
    CopyMemory(filePtr, &newData, sizeof(newData));
    UnmapViewOfFile(filePtr);
}

void MemoryMappedFile::CreateMapping()
{
    _mappedFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,           // use paging file
        NULL,                           // default security
        PAGE_READWRITE,                 // read/write access
        0,                              // maximum object size (high-order DWORD)
        sizeof(MappedTelemetryData),    // maximum object size (low-order DWORD)
        L"SCS_Telemetry_Data_OG");      // name of mapping object
}

void MemoryMappedFile::CloseMapping()
{
    CloseHandle(_mappedFile);
}
