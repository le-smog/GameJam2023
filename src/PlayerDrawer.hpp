#pragma once

#include "Drawer.hpp"
#include "Player.hpp"

class PlayerDrawer : public Drawer {
public:
  PlayerDrawer(SDL_Renderer *renderer);
  void drawPlayer(const Player &player) const;
};
