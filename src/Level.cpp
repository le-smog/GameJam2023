#include "Level.hpp"

#include <fmt/std.h>

Level::Level(std::string_view level_name, std::vector<Obstacle> &obstacles)
    : m_level_name(level_name), m_obstacles(obstacles) {}

const std::vector<Obstacle> &Level::getObstacles() { return m_obstacles; }
