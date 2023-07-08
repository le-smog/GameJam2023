#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "Obstacle.hpp"

class ObstaclesDrawer
{
private:
    SDL_Renderer *m_renderer;
public:
    ObstaclesDrawer(SDL_Renderer* renderer);
    void drawObstacle(std::vector<Obstacle> obstacles);
};
