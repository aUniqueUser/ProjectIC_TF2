#pragma once

#include "../../SDK/SDK.h"

namespace EngineVGuiHook
{
	extern VMT::Table Table;

	namespace Paint
	{
		using fn = void(*)(C_EngineVGui *, int);
		constexpr int index = 13;
		void Hook(int mode);
	}
}