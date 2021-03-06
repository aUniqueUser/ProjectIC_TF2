#include "TriggerBot.h"
#include "Input.h"

bool C_TriggerBot::IsTriggerKeyDown()
{
	switch (nTriggerKey)
	{
		case 0:
			return true;
		case 1:
			return gInput.IsKeyDown(SDLK_LSHIFT);
		case 2:
			return gInput.IsKeyDown(SDL_BUTTON_LEFT);
		case 3:
			return gInput.IsKeyDown(SDL_BUTTON_MIDDLE);
	}

	return false;
}

void C_TriggerBot::Run(C_UserCmd *pCmd)
{
	if (!bActive || !IsTriggerKeyDown())
		return;

	gTriggerShoot.Run(pCmd);
	gTriggerStab.Run(pCmd);
}

C_TriggerBot gTriggerBot;