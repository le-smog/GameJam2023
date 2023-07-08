#pragma once

#include <SDL2/SDL.h>

class Obstacle
{
private:
    int m_x, m_y;
    int m_width, m_height;
public:
    Obstacle(int x, int y, int width, int height);
    SDL_Rect to_SDL_rect();
};
