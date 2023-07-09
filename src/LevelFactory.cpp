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

static Obstacle parse_obstacle_from_node(const YAML::Node &yaml_obstacle) {
  assert_key_exists(yaml_obstacle, "x");
  int x = yaml_obstacle["x"].as<int>();

  assert_key_exists(yaml_obstacle, "y");
  int y = yaml_obstacle["y"].as<int>();

  assert_key_exists(yaml_obstacle, "width");
  int width = yaml_obstacle["width"].as<int>();

  assert_key_exists(yaml_obstacle, "height");
  int height = yaml_obstacle["height"].as<int>();

  return Obstacle(x, y, width, height);
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
  assert_key_exists(player_data, "x");
  assert_key_exists(player_data, "y");
  Player player = Player(player_data["x"].as<int>(), player_data["y"].as<int>(), 20, 20);

  return Level(level_name, player, obstacles);
}
