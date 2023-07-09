#include "Obstacle.hpp"

Obstacle::Obstacle(int x, int y, int width, int height) : m_x(x), m_y(y), m_width(width), m_height(height) {}

SDL_Rect Obstacle::to_SDL_rect() { return SDL_Rect{m_x, m_y, m_width, m_height}; }
