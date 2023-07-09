#include "PlayerDrawer.hpp"
#include "Drawer.hpp"
#include <spdlog/spdlog.h>

void PlayerDrawer::drawPlayer(const Player& player) {
    SDL_Rect hitbox = player.to_SDL_rect();
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    int res = SDL_RenderDrawRect(m_renderer, &hitbox);
    if (res < 0) {
        spdlog::error("Could not draw player");
    }
}

PlayerDrawer::PlayerDrawer(SDL_Renderer* renderer): Drawer(renderer) {}
