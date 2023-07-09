#pragma once

#include "Command.hpp"
#include "Obstacle.hpp"

#include <SDL2/SDL.h>

#include <vector>

class Player {
private:
  float m_x, m_y;
  float m_width, m_height;
  float a_x, a_y;

public:
  Player(float x, float y, float width, float height);
  SDL_FRect to_SDL_frect() const;
  void update(const std::vector<Obstacle> &obstacles, const std::vector<Command> &commands, Uint64 elapsed_time);
};
