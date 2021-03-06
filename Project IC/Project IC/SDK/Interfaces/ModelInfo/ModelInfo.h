#pragma once
#include "../../Includes/Includes.h"

class C_ModelInfoClient
{
public:
	model_t *GetModel(int index)
	{
		typedef model_t *(*FN)(void *, int);
		return GetVFunc<FN>(this, 1)(this, index);
	}

	int	GetModelIndex(const char *name)
	{
		typedef int (*FN)(void *, const char *);
		return GetVFunc<FN>(this, 2)(this, name);
	}

	const char *GetModelName(const model_t *model) 
	{
		typedef const char *(*FN)(void *, const model_t *);
		return GetVFunc<FN>(this, 3)(this, model);
	}

	studiohdr_t *GetStudioModel(const model_t *model)
	{
		typedef studiohdr_t *(*FN)(void *, const model_t *);
		return GetVFunc<FN>(this, 28)(this, model);
	}
};

#define VMODELINFO_CLIENT_INTERFACE_VERSION	"VModelInfoClient006"