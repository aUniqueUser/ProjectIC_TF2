#include "Pattern.h"
#include <cstdio>

#define INRANGE(x,a,b)	(x >= a && x <= b) 
#define GetBits(x)		(INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define GetByte(x)		(GetBits(x[0]) << 4 | GetBits(x[1]))

/* Written by F1ssi0N */

// module should be a pointer to the base of an elf32 module
// this is not the value returned by dlopen (which returns an opaque handle to
// the module) the best method to get this address is with fopen() and mmap()
// (check the GetClientSignature() and GetEngineSignature() for an example)
Elf32_Shdr *CPattern::GetSectionHeader(void *vModule, const char *szSectionName)
{
    // we need to get the modules actual address from the handle
    Elf32_Ehdr *ehdr = (Elf32_Ehdr *) vModule;
    Elf32_Shdr *shdr = (Elf32_Shdr *) ((uintptr_t) vModule + ehdr->e_shoff);
    Elf32_Shdr *strhdr = &shdr[ehdr->e_shstrndx];

    char *strtab        = nullptr;
    unsigned strtabSize = 0;
    if (strhdr != nullptr && strhdr->sh_type == 3)
    {
        strtab = (char *) ((uintptr_t) vModule + strhdr->sh_offset);
        strtabSize = strhdr->sh_size;
    }

    for (int i = 0; i < ehdr->e_shnum; i++)
    {
        Elf32_Shdr *hdr = &shdr[i];
        if (hdr && hdr->sh_name < strtabSize)
        {
            if (!strcmp(strtab + hdr->sh_name, szSectionName))
                return hdr;
        }
    }
    return nullptr;
}

uintptr_t CPattern::FindPattern(uintptr_t dwAddress, uintptr_t dwLength, const char *szPattern)
{
    const char *pattern  = szPattern;
    uintptr_t firstMatch = 0;

    uintptr_t start = dwAddress;
    uintptr_t end   = dwLength;

    for (uintptr_t pos = start; pos < end; pos++)
    {
        if (*pattern == 0)
            return firstMatch;

        const uint8_t currentPattern = *reinterpret_cast<const uint8_t *>(pattern);
        const uint8_t currentMemory  = *reinterpret_cast<const uint8_t *>(pos);

        if (currentPattern == '\?' || currentMemory == GetByte(pattern))
        {
            if (!firstMatch)
                firstMatch = pos;
            if (!pattern[2])
                return firstMatch;

            pattern += currentPattern != '\?' ? 3 : 2;
        }
        else
        {
            pattern    = szPattern;
            firstMatch = 0;
        }
    }
    printf("FATAL! Could not locate pattern: %s", szPattern);
    return 0;
}

void *CPattern::GetModuleHandleSafe(const char *szModuleName)
{
	void *hmModuleHandle;
	do
	{
		hmModuleHandle = dlopen(szModuleName, RTLD_NOW);
		usleep(1);
	} while (hmModuleHandle == nullptr);

	return hmModuleHandle;
}

uintptr_t CPattern::Find(const char *szModuleName, const char *szPattern)
{
    // we need to do this because (i assume that) under the hood, dlopen only loads up the sections that it needs
    // into memory, meaning that we cannot get the string table from the module.
    static int fd = open(szModuleName, O_RDONLY);
    static void *vModule = mmap(nullptr, lseek(fd, 0, SEEK_END), PROT_READ, MAP_SHARED, fd, 0);
    if ((uintptr_t) vModule == 0xffffffff)
        return 0;

    static auto *lmModuleMap = (link_map *)GetModuleHandleSafe(szModuleName);

    static Elf32_Shdr *textHeader = GetSectionHeader(lmModuleMap, ".text");

    static int iTextOffset = textHeader->sh_offset;
    static int iTextSize = textHeader->sh_size;

    // we need to remap the address that we got from the pattern search from our mapped file to the actual memory
    // we do this by rebasing the address (subbing the mmapped one and replacing it with the dlopened one.
    uintptr_t pattern = FindPattern(((uintptr_t) vModule) + iTextOffset, ((uintptr_t) vModule) + iTextOffset + iTextSize, szPattern);
    if (!pattern)
        return 0;
    return pattern - (uintptr_t)(vModule) + lmModuleMap->l_addr;
}

CPattern gPattern;