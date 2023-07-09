#pragma once

#include <SDL2/SDL.h>

class Obstacle {
private:
  float m_x, m_y;
  float m_width, m_height;

public:
  Obstacle(float x, float y, float width, float height);
  SDL_FRect to_SDL_frect() const;
};
