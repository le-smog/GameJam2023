#pragma once

#include "Obstacle.hpp"

#include <SDL2/SDL.h>

#include <vector>

class ObstaclesDrawer {
private:
  SDL_Renderer *m_renderer;

public:
  ObstaclesDrawer(SDL_Renderer *renderer);
  void drawObstacle(std::vector<Obstacle> obstacles);
};
