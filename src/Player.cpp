#include "Player.hpp"

#include <SDL2/SDL.h>
#include <cmath>

Player::Player(float x, float y, float width, float height)
    : m_x(x), m_y(y), m_width(width), m_height(height), a_x(0), a_y(0) {}

SDL_FRect Player::to_SDL_frect() const { return SDL_FRect{m_x, m_y, m_width, m_height}; }

void Player::update(const std::vector<Obstacle> &obstacles, const std::vector<Command> &commands, Uint64 elapsed_time) {
  float delta = static_cast<float>(elapsed_time);
  float gravity = 0.1f * delta;

  SDL_FRect hitbox = this->to_SDL_frect();
  hitbox.y += gravity;
  bool has_intersected = false;
  for (auto &obstacle : obstacles) {
    SDL_FRect obstacle_hitbox = obstacle.to_SDL_frect();
    has_intersected = has_intersected || SDL_HasIntersectionF(&hitbox, &obstacle_hitbox);
  }
  bool can_jump = false;
  if (has_intersected) {
    a_y = 0;
    can_jump = true;
  } else {
    a_y += gravity;
  }

  static constexpr float Y_ACCEL = 69.f;
  static constexpr float X_ACCEL = .5f;
  static constexpr float X_FRICTION = .2f;
  float friction_accel = SDL_clamp(X_FRICTION, 0.f, std::fabs(a_x));
  a_x += std::copysignf(friction_accel, -1.f * a_x);
  for (auto command : commands) {
    switch (command) {
    case Command::CMD_JUMP:
      if (!can_jump) {
        break;
      }
      a_y -= Y_ACCEL * delta;
      break;
    case Command::CMD_LEFT:
      a_x -= X_ACCEL * delta;
      break;
    case Command::CMD_RIGHT:
      a_x += X_ACCEL * delta;
      break;
    default:
      break;
    }
  }

  static constexpr float MAX_ACCEL = .05f;
  m_x += SDL_clamp(a_x, -MAX_ACCEL, MAX_ACCEL);
  m_y += SDL_clamp(a_y, -MAX_ACCEL, MAX_ACCEL);
}