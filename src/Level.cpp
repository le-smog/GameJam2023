#include "Level.hpp"
#include "Player.hpp"

#include <fmt/std.h>

Level::Level(std::string_view level_name, Player &player, std::vector<Obstacle> &obstacles)
    : m_level_name(level_name), m_player(player), m_obstacles(obstacles) {}

const std::vector<Obstacle> &Level::getObstacles() { return m_obstacles; }

const Player& Level::getPlayer() {
    return m_player;
}
