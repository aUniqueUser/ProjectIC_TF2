#pragma once

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_system.h>
#include <SDL2/SDL_mouse.h>

class C_Input
{
private:
    bool IsKeyMouseKey(int key);

public:
    bool IsKeyDown(int key);
};

extern C_Input gInput;