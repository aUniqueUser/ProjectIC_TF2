#include "Input.h"

bool C_Input::IsKeyMouseKey(int key)
{
    return key == SDL_BUTTON_LEFT || key == SDL_BUTTON_MIDDLE || key == SDL_BUTTON_RIGHT || key == SDL_BUTTON_X1 || key == SDL_BUTTON_X2;
}

bool C_Input::IsKeyDown(int key)
{
    if (IsKeyMouseKey(key))
    {
        auto flag = SDL_GetMouseState(nullptr, nullptr);
        if (flag & SDL_BUTTON(key))
            return true;
    }
    else
    {
        auto keys = SDL_GetKeyboardState(nullptr);
        if (keys[SDL_GetScancodeFromKey(key)])
            return true;
    }

    return false;
}

C_Input gInput;