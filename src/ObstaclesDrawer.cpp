#include "ObstaclesDrawer.hpp"

#include <spdlog/spdlog.h>

ObstaclesDrawer::ObstaclesDrawer(SDL_Renderer *renderer) : m_renderer(renderer) {}

void ObstaclesDrawer::drawObstacle(const std::vector<Obstacle> &obstacles) const {
  std::vector<SDL_FRect> SDL_obstacles{};
  for (const auto &obstacle : obstacles) {
    SDL_FRect rect = obstacle.to_SDL_frect();
    SDL_obstacles.push_back(rect);
  }
  SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
  int res = SDL_RenderDrawRectsF(m_renderer, SDL_obstacles.data(), static_cast<int>(SDL_obstacles.size()));
  if (res < 0) {
    spdlog::error("Could not draw rects: {}", SDL_GetError());
  }
}
