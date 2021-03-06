#pragma once

#include "../../SDK/SDK.h"

namespace ModelRenderHook
{
	extern VMT::Table Table;

	namespace DrawModelExecute
	{
		using fn = void(*)(C_ModelRender*, const DrawModelState_t&, const ModelRenderInfo_t&, matrix3x4*);
		constexpr int index = 19;
		void Hook(const DrawModelState_t& pState, const ModelRenderInfo_t& pInfo, matrix3x4* pBoneToWorld);
	}
}