#include "Hooks/Hooks.h"
#include "Input.h"

#include "Features/Visuals/Chams/Chams.h"

#include <pthread.h>
#include <semaphore.h>

static bool sem_main_inited;
static sem_t sem_main;
static pthread_t thread_main;

void *MainThread(void *arg)
{
	gSteam.Init();
	gInts.Init();
	gNetVars.Init();
	gHooks.Init();
	gConVars.Init();
	gChams.InitMaterials();
	gDraw.InitFonts
	({
		//FONT_ESP
		{ 0x0, "Tahoma", 12, 0, FONTFLAG_NONE },
		//FONT_ESP_OUTLINED
		{ 0x0, "Tahoma", 12, 0, FONTFLAG_OUTLINE },

		//FONT_ESP_NAME
		{ 0x0, "Tahoma", 13, 0, FONTFLAG_NONE },
		//FONT_ESP_NAME_OUTLINED
		{ 0x0, "Tahoma", 13, 0, FONTFLAG_OUTLINE },

		//FONT_ESP_COND
		{ 0x0, "Consolas", 10, 0, FONTFLAG_NONE },
		//FONT_ESP_COND_OUTLINED
		{ 0x0, "Consolas", 10, 0, FONTFLAG_OUTLINE },

		//FONT_ESP_PICKUPS
		{ 0x0, "Tahoma", 11, 0, FONTFLAG_NONE },
		//FONT_ESP_PICKUPS_OUTLINED
		{ 0x0, "Tahoma", 11, 0, FONTFLAG_OUTLINE },

		//FONT_DEBUG
		{ 0x0, "Arial", 16, 0, FONTFLAG_OUTLINE },
		//FONT_MENU
		{ 0x0, "Segoe UI", 13, 0, FONTFLAG_ANTIALIAS },
		//FONT_MENU_NAME
		{ 0x0, "Segoe UI", 20, 0, FONTFLAG_ANTIALIAS }
	});

	//Stuck at this, as long as "panic" key is not pressed.
	while (!gInput.IsKeyDown(SDLK_F11))
		std::this_thread::sleep_for(std::chrono::seconds(1));

	gHooks.Release();
	std::_Exit(EXIT_SUCCESS);
}

void __attribute__((constructor)) attach()
{
    if (sem_main_inited)
        return;

    sem_init(&sem_main, 0, 0);

    sem_main_inited = true;

    pthread_create(&thread_main, nullptr, MainThread, nullptr);
}

void detach()
{
    sem_post(&sem_main);
    pthread_join(thread_main, nullptr);
}

void __attribute__((destructor)) deconstruct()
{
    detach();
}
