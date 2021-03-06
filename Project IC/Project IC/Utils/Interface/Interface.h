#pragma once
#include <Windows.h>

class CInterface
{
private:
	typedef void *(*InstantiateInterface)();

	struct Interface_t
	{
		InstantiateInterface Interface;
		PCHAR szInterfaceName;
		Interface_t *NextInterface;
	};

public:
	void * Get(PCCH szModule, PCCH szObject);
};

extern CInterface gInterface;