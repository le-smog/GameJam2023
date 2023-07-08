add_executable(game
  "main.cpp"
)

find_package(fmt CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)

target_link_libraries(game
  PRIVATE
  SDL2::SDL2main
  SDL2::SDL2
  fmt::fmt
  spdlog::spdlog
  yaml-cpp
)

target_set_project_options(game)

add_custom_command(
  TARGET game
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy_directory
  "${CMAKE_CURRENT_LIST_DIR}/levels"
  "${CMAKE_CURRENT_BINARY_DIR}/levels"
  COMMENT "Copying levels to build directory"
)
