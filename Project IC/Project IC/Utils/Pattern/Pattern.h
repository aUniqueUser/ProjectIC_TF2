#pragma once

#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <elf.h>
#include <link.h>

#include <sys/mman.h>

class CPattern
{
private:
    Elf32_Shdr *GetSectionHeader(void *vModule, const char *szSectionName);
    uintptr_t FindPattern(uintptr_t dwAddress, uintptr_t dwLength, const char *szPattern);
    void *GetModuleHandleSafe(const char *szModuleName);
public:
	uintptr_t Find(const char *szModuleName, const char *szPattern);
};

extern CPattern gPattern;