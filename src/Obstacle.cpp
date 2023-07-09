#include "Obstacle.hpp"

Obstacle::Obstacle(float x, float y, float width, float height) : m_x(x), m_y(y), m_width(width), m_height(height) {}

SDL_FRect Obstacle::to_SDL_frect() const { return SDL_FRect{m_x, m_y, m_width, m_height}; }
