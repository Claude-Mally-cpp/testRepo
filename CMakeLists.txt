cmake_minimum_required(VERSION 3.14...3.22)

# ---- Project ----

# Note: update this to your new project's name and version
project(
  Hobby
  VERSION 1.0
  LANGUAGES CXX)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info

include(cmake/CPM.cmake)

# PackageProject.cmake will be used to make our target installable
cpmaddpackage("gh:TheLartians/PackageProject.cmake@1.8.0")

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

# ---- Add source files ----

set(headers
    "include/hobby/hobby.hpp"
    "include/hobby/hobbyDice.hpp"
    "include/hobby/hobbyMath.hpp"
)

set(sources
    "source/hobby.cpp"
    "source/hobbyMath.cpp"
)

# ---- Create library ----
add_library(${PROJECT_NAME} ${headers} ${sources})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)

target_compile_options(${PROJECT_NAME} PRIVATE ${PROJECT_WARNING_FLAGS})

# being a cross-platform target, we enforce standards conformance on MSVC
# target_compile_options(${PROJECT_NAME} PUBLIC
# "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

# Link dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

# Link SFML to your project
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-audio)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>)

# ---- Install the library ----

install(
  TARGETS Hobby
  EXPORT HobbyConfig
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include)

install(DIRECTORY include/hobby/ DESTINATION include/hobby)

# ---- Create an installable target ----
# this allows users to install and find the library via `find_package()`.

# the location where the project's version header will be placed should match
# the project's regular header paths
string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)

packageproject(
  NAME
  ${PROJECT_NAME}
  VERSION
  ${PROJECT_VERSION}
  NAMESPACE
  ${PROJECT_NAME}
  BINARY_DIR
  ${PROJECT_BINARY_DIR}
  INCLUDE_DIR
  ${PROJECT_SOURCE_DIR}/include
  INCLUDE_DESTINATION
  include/${PROJECT_NAME}-${PROJECT_VERSION}
  VERSION_HEADER
  "${VERSION_HEADER_LOCATION}"
  COMPATIBILITY
  SameMajorVersion
  DEPENDENCIES
  "fmt 11.0.2")
