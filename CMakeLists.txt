cmake_minimum_required(VERSION 3.20)
project(gamejam-july-2023 LANGUAGES CXX)

message(CHECK_START "Checking for LTO support in C++")
include(CheckIPOSupported)
check_ipo_supported(RESULT "HAVE_IPO" LANGUAGES CXX)

if(HAVE_IPO)
  message(CHECK_PASS "supported")
else()
  message(CHECK_FAIL "unsupported")
endif()

message(CHECK_START "Checking for PIE support in C++")
include(CheckPIESupported)
check_pie_supported(LANGUAGES CXX)

if(CMAKE_CXX_LINK_PIE_SUPPORTED)
  message(CHECK_PASS "supported")
else()
  message(CHECK_FAIL "unsupported")
endif()

include(CMakeDependentOption)
cmake_dependent_option(USE_LTO "Enable link-time optimisation" ON "HAVE_LTO" OFF)
cmake_dependent_option(USE_PIE "Enable position independent code" ON "HAVE_PIE" OFF)

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src")
