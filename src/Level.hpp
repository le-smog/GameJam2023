#pragma once

#include "Obstacle.hpp"
#include "Player.hpp"

#include <string>
#include <vector>

class Level {
private:
  std::string_view m_level_name;
  Player m_player;
  std::vector<Obstacle> m_obstacles;

public:
  Level(std::string_view level_name, Player &player, std::vector<Obstacle> &obstacles);
  const std::vector<Obstacle> &getObstacles();
};
