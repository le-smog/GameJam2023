function(check_lto RESULT)
  if(LTO_ALREADY_CHECKED)
    return()
  endif()

  message(CHECK_START "Checking for LTO support in C++")
  include(CheckIPOSupported)
  check_ipo_supported(RESULT "HAVE_IPO" LANGUAGES CXX)

  if(HAVE_IPO)
    message(CHECK_PASS "supported")
  else()
    message(CHECK_FAIL "unsupported")
  endif()

  set(LTO_ALREADY_CHECKED TRUE CACHE INTERNAL "")
  set(${RESULT} ${HAVE_IPO} PARENT_SCOPE)
endfunction()

function(check_pie)
  if(PIE_ALREADY_CHECKED)
    return()
  endif()

  message(CHECK_START "Checking for PIE support in C++")
  include(CheckPIESupported)
  check_pie_supported(LANGUAGES CXX)

  if(CMAKE_CXX_LINK_PIE_SUPPORTED)
    message(CHECK_PASS "supported")
  else()
    message(CHECK_FAIL "unsupported")
  endif()

  set(PIE_ALREADY_CHECKED TRUE CACHE INTERNAL "")
endfunction()

function(check_asan)
  include(CMakePushCheckState)
  cmake_push_check_state(RESET)

  if(MSVC)
    set(CMAKE_REQUIRED_FLAGS "/fsanitize=address /Zi")
    set(CMAKE_REQUIRED_LINK_OPTIONS "/fsanitize=address")
  else()
    set(CMAKE_REQUIRED_FLAGS "-fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=address")
  endif()

  include(CheckCXXSourceCompiles)
  check_cxx_source_compiles(
    "int main() {}"
    HAVE_ASAN
  )
  cmake_pop_check_state()
endfunction()
