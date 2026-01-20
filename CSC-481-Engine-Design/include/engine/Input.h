#pragma once

#include <SDL3/SDL.h>

class Input {
public:
    // Asks if a key is currently being pressed.
    static bool isKeyPressed(SDL_Scancode key);
    // Grabs the latest keyboard state. Call this once per frame.
    static void updateKeyboardState();
private:
    // A list of all keys on the keyboard and whether each one is pressed or not.
    static const bool* keyboardState;
};