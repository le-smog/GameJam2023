#include "Player.hpp"

#include <SDL2/SDL.h>

Player::Player(float x, float y, float width, float height) : m_x(x), m_y(y), m_width(width), m_height(height) {}

SDL_FRect Player::to_SDL_frect() const { return SDL_FRect{m_x, m_y, m_width, m_height}; }

void Player::update(const std::vector<Obstacle> &obstacles, Uint64 elapsed_time) {
  float next_y = m_y + 0.1f * elapsed_time;

  SDL_FRect hitbox = this->to_SDL_frect();
  hitbox.y = next_y;
  for (auto &obstacle : obstacles) {
    SDL_FRect obstacle_hitbox = obstacle.to_SDL_frect();
    if (SDL_HasIntersectionF(&hitbox, &obstacle_hitbox)) {
      return;
    }
  }
  m_y = next_y;
}