#include "Interface.h"

void * CInterface::Get(const char *szModule, const char *szObject)
{
	void *Module = dlopen(szModule, RTLD_NOW);
	if (!Module)
		return nullptr;
	
	uintptr_t CreateInterface	= (uintptr_t)dlsym(Module, "CreateInterface");
	uintptr_t ShortJump			= (uintptr_t)CreateInterface + 5;
	uintptr_t Jump				= (((uintptr_t)CreateInterface + 5) + *(uintptr_t *)ShortJump) + 4;
	Interface_t *List		    = **(Interface_t ***)(Jump + 6);

	while (List)
	{
		if (strstr(List->szInterfaceName, szObject) && (strlen(List->szInterfaceName) - strlen(szObject)) < 5)
			return List->Interface();
		List = List->NextInterface;
	}

	return nullptr;
}

CInterface gInterface;