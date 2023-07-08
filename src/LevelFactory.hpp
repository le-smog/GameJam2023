#pragma once

#include "Level.hpp"

#include <filesystem>
#include <string_view>

class LevelFactory {
private:
  std::filesystem::path m_levels_path;

public:
  LevelFactory(std::string_view levels_path);

  Level make_level(std::string_view level_name);
};
