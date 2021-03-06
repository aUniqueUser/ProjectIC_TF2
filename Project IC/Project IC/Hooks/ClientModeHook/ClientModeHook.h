#pragma once
#include "../../SDK/SDK.h"

namespace ClientModeHook
{
	extern VMT::Table Table;

	namespace OverrideView
	{
		const int index = 16;
		using fn = void(*)(C_ClientModeShared *, C_ViewSetup *);
		void Hook(C_ViewSetup *pView);
	}

	namespace ShouldDrawViewModel
	{
		const int index = 24;
		using fn = bool(*)(C_ClientModeShared *);
		bool Hook();
	}

	namespace CreateMove
	{
		const int index = 21;
		using fn = bool(*)(C_ClientModeShared *, float, C_UserCmd*);
		bool Hook(float input_sample_frametime, C_UserCmd *pCmd);
	}
}