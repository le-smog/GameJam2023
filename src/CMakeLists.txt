add_executable(game
  WIN32
  "main.cpp"
)

set_target_properties(game
  PROPERTIES
  CXX_STANDARD 23
  CXX_STANDARD_REQUIRED OFF
  CXX_EXTENSIONS OFF
  INTERPROCEDURAL_OPTIMIZATION "${USE_LTO}"
  POSITION_INDEPENDENT_CODE "${USE_PIE}"
)

find_package(SDL2 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)

target_link_libraries(game
  PRIVATE
  SDL2::SDL2main
  SDL2::SDL2
  spdlog::spdlog
  yaml-cpp
)
