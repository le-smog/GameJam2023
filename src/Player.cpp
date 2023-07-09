#include "Player.hpp"

#include <SDL2/SDL.h>

Player::Player(int x, int y, int width, int height) : m_x(x), m_y(y), m_width(width), m_height(height) {}

SDL_Rect Player::to_SDL_rect() const { return SDL_Rect{m_x, m_y, m_width, m_height}; }

void Player::update(const std::vector<Obstacle> &obstacles, Uint64 elapsed_time) {
    // Apply gravity
    m_y += 0.01*elapsed_time;

    SDL_Rect hitbox = this->to_SDL_rect();
    for (auto &obstacle: obstacles) {
        SDL_Rect obstacle_hitbox = obstacle.to_SDL_rect();
        if (SDL_HasIntersection(&hitbox, &obstacle_hitbox)) {
            // find side of collision
            // Block speed on the side of the collision
        }
    }
 }