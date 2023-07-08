#pragma once

#include <filesystem>
#include <string_view>

#include "Level.hpp"

class LevelFactory
{
private:
    std::filesystem::path m_levels_path;
public:
    LevelFactory(std::string_view levels_path);

    Level make_level(std::string_view level_name);
};