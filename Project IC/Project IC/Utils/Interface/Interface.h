#pragma once

#include <cstdint>
#include <cstring>
#include <dlfcn.h>

class CInterface
{
private:
	typedef void *(*InstantiateInterface)();

	struct Interface_t
	{
		InstantiateInterface Interface;
		const char *szInterfaceName;
		Interface_t *NextInterface;
	};

public:
	void * Get(const char *szModule, const char *szObject);
};

extern CInterface gInterface;