#include "LevelFactory.hpp"

#include "Obstacle.hpp"
#include "Player.hpp"

#include <SDL2/SDL.h>
#include <fmt/std.h>
#include <spdlog/spdlog.h>
#include <yaml-cpp/yaml.h>

#include <memory>
#include <stdexcept>

static const std::unique_ptr<char, void (*)(void *)> BASE_PATH{SDL_GetBasePath(), SDL_free};

void assert_key_exists(const YAML::Node &node, const std::string &key) {
  if (!node[key]) {
    spdlog::critical("Missing {} on obstacle at line: {}", key, node.Mark().line + 1);
    std::exit(4);
  }
}

static Obstacle parse_obstacle_from_node(const YAML::Node &obstacle_data) {
  assert_key_exists(obstacle_data, "x");
  float x = obstacle_data["x"].as<float>();

  assert_key_exists(obstacle_data, "y");
  float y = obstacle_data["y"].as<float>();

  assert_key_exists(obstacle_data, "width");
  float width = obstacle_data["width"].as<float>();

  assert_key_exists(obstacle_data, "height");
  float height = obstacle_data["height"].as<float>();

  return Obstacle(x, y, width, height);
}

static Player parse_player_from_node(const YAML::Node &player_data) {
  assert_key_exists(player_data, "x");
  float player_x = player_data["x"].as<float>();

  assert_key_exists(player_data, "y");
  float player_y = player_data["y"].as<float>();

  static constexpr float DEFAULT_PLAYER_SIZE = 20.f;
  return Player(player_x, player_y, DEFAULT_PLAYER_SIZE, DEFAULT_PLAYER_SIZE);
}

LevelFactory::LevelFactory(std::string_view levels_path) : m_levels_path(BASE_PATH.get()) {
  m_levels_path /= levels_path;
  if (!std::filesystem::is_directory(m_levels_path)) {
    spdlog::critical("levels_path '{}' is not a directory", m_levels_path);
    std::exit(4);
  }
  if (std::filesystem::is_empty(m_levels_path)) {
    spdlog::critical("levels_path '{}' is empty", m_levels_path);
    std::exit(4);
  }
}

Level LevelFactory::make_level(std::string_view level_name) {
  std::filesystem::path level_path = m_levels_path / level_name;
  level_path.concat(".yaml");
  if (!std::filesystem::exists(level_path)) {
    spdlog::critical("'{}' is not a valid level name", level_name);
    std::exit(4);
  }

  YAML::Node level_data = YAML::LoadFile(level_path.string());
  assert_key_exists(level_data, "obstacles");
  const YAML::Node &obstacles_data = level_data["obstacles"];

  std::vector<Obstacle> obstacles{};
  for (const auto &obstacle : obstacles_data) {
    Obstacle parsed_obstacle = parse_obstacle_from_node(obstacle);
    obstacles.push_back(parsed_obstacle);
  }

  assert_key_exists(level_data, "player");
  const YAML::Node &player_data = level_data["player"];
  Player player = parse_player_from_node(player_data);

  return Level(level_name, player, obstacles);
}
