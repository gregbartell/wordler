cmake_minimum_required(VERSION 3.16)

project("wordler")

include(GoogleTest)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra)
list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")

# Generate compile_commands.json, to aid dev tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Force coloring of compiler output by default
option(FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)" TRUE)
if(${FORCE_COLORED_OUTPUT})
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
       add_compile_options (-fdiagnostics-color=always)
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       add_compile_options (-fcolor-diagnostics)
    endif()
endif()

# Download and unpack googletest at configure time
configure_file(GTestCMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# Googlebench adds its own tests to CMake by default - we don't care about them
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Enable googlebench internal tests" FORCE)

# Download and unpack googlebench at configure time
configure_file(GBenchCMakeLists.txt.in googlebench-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googlebench-download)
if(result)
  message(FATAL_ERROR "CMake step for googlebench failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googlebench-download)
if(result)
  message(FATAL_ERROR "Build step for googlebench failed: ${result}")
endif()

# Add googlebench directly to our build. This defines
# the benchmark and benchmark_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googlebench-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googlebench-build
                 EXCLUDE_FROM_ALL)

# Set clang-tidy, if requested
option(USE_CLANG_TIDY "Enable clang-tidy checking" OFF)
# Can't have this on by default (e.g. in .clang-tidy) because clangd doesn't
# respect certain options if a line would cause an error
option(CLANG_TIDY_ERRORS "Set clang-tidy warnings to be build errors" OFF)

if(USE_CLANG_TIDY AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  find_program(CLANG_TIDY_EXE
      NAMES "clang-tidy-12"
      DOC "Path to clang-tidy executable")
  if (CLANG_TIDY_ERRORS)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};--warnings-as-errors=*")
  else()
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
  endif()
endif()

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

# Enables testing for all directories after this command, so should be after
# all of the third-party includes
enable_testing()

add_subdirectory(src)
