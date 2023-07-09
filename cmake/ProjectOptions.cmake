include_guard()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type to use" FORCE)
  set_property(
    CACHE CMAKE_BUILD_TYPE
    PROPERTY STRINGS
    "Debug"
    "Release"
    "MinSizeRel"
    "RelWithDebInfo")
endif()

include(CheckSupportedWarnings)
check_supported_warnings()

include(CheckFeatures)
check_lto(HAVE_LTO)
check_pie()
check_asan()

include(CMakeDependentOption)
cmake_dependent_option(ENABLE_LTO "Enable link-time optimisation" ON "HAVE_LTO" OFF)
cmake_dependent_option(ENABLE_PIE "Enable position independent code" ON "CMAKE_CXX_LINK_PIE_SUPPORTED" OFF)
cmake_dependent_option(ENABLE_ASAN "Enable address sanitizer" ON "HAVE_ASAN" OFF)

function(target_set_project_options TARGET)
  target_compile_options(${TARGET} PRIVATE ${SUPPORTED_WARNINGS})

  if(ENABLE_ASAN)
    if(MSVC)
      target_compile_options(${TARGET} PRIVATE "/fsanitize=address" "/Zi")
      target_link_options(${TARGET} PRIVATE "/fsanitize=address")
    else()
      target_compile_options(${TARGET} PRIVATE "-fsanitize=address" "-fno-omit-frame-pointer")
      target_link_options(${TARGET} PRIVATE "-fsanitize=address")
    endif()
  endif()

  if(MSVC)
    target_compile_options(${TARGET} PRIVATE "/sdl" "/DYNAMICBASE" "/guard:cf")
    target_link_options(${TARGET} PRIVATE "/NXCOMPAT" "/CETCOMPAT")
  else()
    # If _FORTIFY_SOURCE is a builtin define, we need to undefine it first
    target_compile_options(${TARGET} PRIVATE "-U_FORTIFY_SOURCE" "-D_FORTIFY_SOURCE=3")
  endif()

  set_target_properties(${TARGET}
    PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED OFF
    CXX_EXTENSIONS OFF
    INTERPROCEDURAL_OPTIMIZATION "${ENABLE_LTO}"
    POSITION_INDEPENDENT_CODE "${ENABLE_PIE}"
  )
endfunction()
