cmake_minimum_required(VERSION 3.20)
project(gamejam-july-2023 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(ProjectOptions)

find_package(fmt 9 CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src")
