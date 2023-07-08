#pragma once

#include "Obstacle.hpp"

#include <string>
#include <vector>

class Level {
private:
  std::string_view m_level_name;
  std::vector<Obstacle> m_obstacles;

public:
  Level(std::string_view level_name, std::vector<Obstacle> &obstacles);
  const std::vector<Obstacle> &getObstacles();
};
