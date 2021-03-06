#pragma once
#include "../../SDK/SDK.h"

namespace PredictionHook
{
	extern VMT::Table Table;

	namespace RunCommand
	{
		const int index = 17;
		using fn = void(*)(C_Prediction *, C_BaseEntity *, C_UserCmd *, C_MoveHelper *);
		void Hook(C_BaseEntity *pEntity, C_UserCmd *pCmd, C_MoveHelper *pMoveHelper);
	}
}