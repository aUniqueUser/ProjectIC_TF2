#pragma once
#include "../../Includes/Includes.h"

class C_ClientEntityList
{
public:
	C_BaseEntity *GetClientEntity(int nEntityIndex)
	{
		typedef C_BaseEntity *(*FN)(void *, int);
		return GetVFunc<FN>(this, 3)(this, nEntityIndex);
	}

	C_BaseEntity *GetClientEntityFromHandle(int hEntity)
	{
		typedef C_BaseEntity *(*FN)(void *, int);
		return GetVFunc<FN>(this, 4)(this, hEntity);
	}

	int GetHighestEntityIndex()
	{
		typedef int(*FN)(void *);
		return GetVFunc<FN>(this, 6)(this);
	}
};

#define VCLIENTENTITYLIST_INTERFACE_VERSION	"VClientEntityList003"