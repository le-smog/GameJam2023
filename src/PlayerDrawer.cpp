#include "PlayerDrawer.hpp"
#include "Drawer.hpp"
#include <spdlog/spdlog.h>

PlayerDrawer::PlayerDrawer(SDL_Renderer *renderer) : Drawer(renderer) {}

void PlayerDrawer::drawPlayer(const Player &player) const {
  SDL_FRect hitbox = player.to_SDL_frect();
  SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
  int res = SDL_RenderDrawRectF(m_renderer, &hitbox);
  if (res < 0) {
    spdlog::error("Could not draw player");
  }
}
