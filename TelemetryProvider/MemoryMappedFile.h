#pragma once

#include <Windows.h>
#include "MappedTelemetryData.h"

class MemoryMappedFile
{
public:
    MemoryMappedFile();
    ~MemoryMappedFile();

    bool IsFileMapped();
    void UpdateMappedFile(MappedTelemetryData& newData);

private:
    void CreateMapping();
    void CloseMapping();

    HANDLE _mappedFile;
};

