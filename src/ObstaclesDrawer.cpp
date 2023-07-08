#include "ObstaclesDrawer.hpp"

#include <spdlog/spdlog.h>

ObstaclesDrawer::ObstaclesDrawer(SDL_Renderer *renderer) : m_renderer(renderer) {}

void ObstaclesDrawer::drawObstacle(std::vector<Obstacle> obstacles) {
  std::vector<SDL_Rect> SDL_obstacles{};
  for (auto &obstacle : obstacles) {
    SDL_Rect rect = obstacle.to_SDL_rect();
    SDL_obstacles.push_back(rect);
  }
  SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
  int res = SDL_RenderDrawRects(m_renderer, SDL_obstacles.data(), static_cast<int>(SDL_obstacles.size()));
  if (res < 0) {
    spdlog::error("Could not draw rects: {}", SDL_GetError());
  }
}
