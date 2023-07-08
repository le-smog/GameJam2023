add_executable(game
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

add_custom_command(
  TARGET game
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy_directory
  "${CMAKE_CURRENT_LIST_DIR}/levels"
  "${CMAKE_CURRENT_BINARY_DIR}/levels"
  COMMENT "Copying levels to build directory"
)
