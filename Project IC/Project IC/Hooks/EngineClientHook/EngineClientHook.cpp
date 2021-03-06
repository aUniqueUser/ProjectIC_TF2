#include "EngineClientHook.h"

bool EngineClientHook::IsPlayingTimeDemo::Hook()
{
	static uintptr_t dwInterpolateServerEntities = gPattern.Find("client.so", "84 C0 0F 85 ? ? ? ? E9 ? ? ? ? 8D 76 00 C6 05");

	if (gGlobalInfo.bNoInterpolation)
	{
		C_BaseEntity *pLocal = gEntCache.pLocal;

        if (pLocal)
		{
            if ((uintptr_t) __builtin_return_address(1) == dwInterpolateServerEntities)
				return true;
		}
	}
	
	return Table.Original<fn>(index)(gInts.Engine);
}

VMT::Table EngineClientHook::Table;