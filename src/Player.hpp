#pragma once

#include "Obstacle.hpp"

#include <SDL2/SDL.h>
#include <vector>

class Player {
private:
  float m_x, m_y;
  float m_width, m_height;

public:
  Player(float x, float y, float width, float height);
  SDL_FRect to_SDL_frect() const;
  void update(const std::vector<Obstacle> &obstacles, Uint64 elapsed_time);
};
