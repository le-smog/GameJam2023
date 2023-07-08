#include "LevelFactory.hpp"

#include "Obstacle.hpp"

#include <SDL2/SDL.h>
#include <fmt/std.h>
#include <yaml-cpp/yaml.h>

#include <iostream>
#include <memory>
#include <stdexcept>

static const std::unique_ptr<char, void (*)(void *)> BASE_PATH{SDL_GetBasePath(), SDL_free};

LevelFactory::LevelFactory(std::string_view levels_path) : m_levels_path(BASE_PATH.get()) {
  m_levels_path /= levels_path;
  if (!std::filesystem::is_directory(m_levels_path)) {
    std::string error_message = fmt::format("levels_path '{}' is not a directory", m_levels_path);
    throw std::invalid_argument(error_message);
  }
  if (m_levels_path.empty()) {
    std::string error_message = fmt::format("levels_path '{}' is empty", m_levels_path);
    throw std::invalid_argument(error_message);
  }
}

Level LevelFactory::make_level(std::string_view level_name) {
  std::filesystem::path level_path = m_levels_path / level_name;
  level_path.concat(".yaml");
  YAML::Node config = YAML::LoadFile(level_path.string());
  std::vector<Obstacle> obstacles{};
  for (const auto &test : config["obstacles"]) {
    Obstacle parsed_obstacle =
        Obstacle(test["x"].as<int>(), test["y"].as<int>(), test["width"].as<int>(), test["height"].as<int>());
    obstacles.push_back(parsed_obstacle);
  }

  return Level(level_name, obstacles);
}
