#include "Player.hpp"

#include <SDL2/SDL.h>

Player::Player(int x, int y, int width, int height) : m_x(x), m_y(y), m_width(width), m_height(height) {}

SDL_Rect Player::to_SDL_rect() const { return SDL_Rect{m_x, m_y, m_width, m_height}; }
