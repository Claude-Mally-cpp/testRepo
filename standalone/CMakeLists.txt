cmake_minimum_required(VERSION 3.14...3.22)

project(HobbyStandalone LANGUAGES CXX)

# --- Import tools ----
include(../cmake/tools.cmake)

# ---- Dependencies ----
include(../cmake/CPM.cmake)

# Add cxxopts
cpmaddpackage(
  GITHUB_REPOSITORY
  jarro2783/cxxopts
  VERSION
  3.0.0
  OPTIONS
  "CXXOPTS_BUILD_EXAMPLES NO"
  "CXXOPTS_BUILD_TESTS NO"
  "CXXOPTS_ENABLE_INSTALL YES")

# Add fmt
cpmaddpackage(
  NAME
  fmt
  GIT_TAG
  11.0.2
  GITHUB_REPOSITORY
  fmtlib/fmt
  OPTIONS
  "FMT_INSTALL YES" # create an installable target
)

# Add SFML 2.6.1 as a dependency
CPMAddPackage(
    NAME SFML
    VERSION 2.6.1
    GIT_TAG 2.6.1
    GITHUB_REPOSITORY SFML/SFML
    OPTIONS
        "SFML_BUILD_GRAPHICS ON"
        "SFML_BUILD_AUDIO ON"
        "SFML_BUILD_WINDOW ON"
        "SFML_BUILD_NETWORK OFF"
        "SFML_BUILD_EXAMPLES OFF"
        "SFML_USE_SYSTEM_DEPS OFF"
)

# Add Hobby library
cpmaddpackage(NAME Hobby SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

# ---- Create standalone executable ----
file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_executable(${PROJECT_NAME} ${sources})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20 OUTPUT_NAME "Hobby")

# Link dependencies
target_link_libraries(${PROJECT_NAME}
  PRIVATE Hobby cxxopts fmt::fmt sfml-window sfml-graphics
)
