#pragma once
#include "../../SDK/SDK.h"

namespace EngineClientHook
{
	extern VMT::Table Table;

	namespace IsPlayingTimeDemo
	{
		const int index = 78;
		using fn = bool(*)(C_EngineClient *);
		bool Hook();
	}
}