cmake_minimum_required(VERSION 3.14...3.22)

project(HobbyTests LANGUAGES CXX)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

cpmaddpackage("gh:doctest/doctest@2.4.9")
cpmaddpackage("gh:TheLartians/Format.cmake@1.7.3")

if(TEST_INSTALLED_VERSION)
  find_package(Hobby REQUIRED)
else()
  cpmaddpackage(NAME Hobby SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
endif()

# ---- Create binary ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_executable(${PROJECT_NAME} ${sources})

if(TEST_INSTALLED_VERSION)
  # Add the installed include directories to the test target
  target_include_directories(${PROJECT_NAME} PRIVATE /usr/local/include /usr/include)
endif()

target_link_libraries(${PROJECT_NAME} doctest::doctest Hobby::Hobby fmt::fmt)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)

# enable compiler warnings
if(NOT TEST_INSTALLED_VERSION)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES
                                              "GNU")
    target_compile_options(Hobby PUBLIC -Wall -Wpedantic -Wextra -Werror)
  elseif(MSVC)
    target_compile_options(Hobby PUBLIC /W4 /WX)
    target_compile_definitions(${PROJECT_NAME}
                               PUBLIC DOCTEST_CONFIG_USE_STD_HEADERS)
  endif()
endif()

# ---- Add HobbyTests ----

enable_testing()

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(${PROJECT_NAME})

# ---- code coverage ----

if(ENABLE_TEST_COVERAGE)
  target_compile_options(Hobby PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(Hobby PUBLIC -fprofile-arcs -ftest-coverage)
endif()
