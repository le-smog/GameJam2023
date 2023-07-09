#pragma once

#include <SDL2/SDL.h>

class Drawer
{
protected:
    SDL_Renderer* m_renderer;
public:
    Drawer(SDL_Renderer* renderer);
};
