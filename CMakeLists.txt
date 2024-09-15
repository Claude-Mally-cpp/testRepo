cmake_minimum_required(VERSION 3.14...3.22)

# Define project name explicitly as Hobby
project(Hobby VERSION 1.0 LANGUAGES CXX)

# ---- Add dependencies via CPM ----
include(cmake/CPM.cmake)

# Set the install prefix if not set by the user
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Default install path" FORCE)
endif()

set(CPM_FORCE_BUILD TRUE)

# PackageProject.cmake will be used to make our target installable
cpmaddpackage("gh:TheLartians/PackageProject.cmake@1.8.0")

# Install fmt with an installable target
cpmaddpackage(
  NAME
  fmt
  GIT_TAG
  11.0.2
  GITHUB_REPOSITORY
  fmtlib/fmt
  OPTIONS
  "FMT_INSTALL YES" # this will create an installable target
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

# ---- Debugging step: List all CMake targets ----
get_cmake_property(_variableNames TARGETS)
foreach (_variableName ${_variableNames})
    message(STATUS "CMake target: ${_variableName}")
endforeach()

# ---- Add source files ----
set(headers
    "include/hobby/hobby.hpp"
    "include/hobby/hobbyDice.hpp"
    "include/hobby/hobbyMath.hpp"
    "include/hobby/enumerateFonts.hpp"
)

set(sources
    "source/hobby.cpp"
    "source/hobbyMath.cpp"
    "source/enumerateFonts.cpp"
)

# ---- Create library ----
add_library(${PROJECT_NAME} STATIC ${headers} ${sources})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)

target_compile_options(${PROJECT_NAME} PRIVATE ${PROJECT_WARNING_FLAGS})

# Link dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt sfml-window)

# Include directories
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  PUBLIC ${SFML_INCLUDE_DIR}
         $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>)

# ---- Install the library ----
install(
  TARGETS ${PROJECT_NAME}
  EXPORT HobbyConfig
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
  COMPONENT sfml-graphics sfml-window sfml-audio
)

install(DIRECTORY include/hobby/ DESTINATION include/hobby)

# Install the fonts/Roboto directory
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/fonts/Roboto
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/fonts/Roboto
    FILES_MATCHING PATTERN "*.ttf"
    PATTERN "LICENSE.txt"            # Install the license file
)

# Copy the entire fonts directory (and all subdirectories) to the build directory
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/fonts
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/fonts ${CMAKE_BINARY_DIR}/fonts
    DEPENDS ${PROJECT_SOURCE_DIR}/fonts
    COMMENT "Copying all fonts to the build directory"
)

# Create a custom target that runs the above command
add_custom_target(copy_fonts ALL DEPENDS ${CMAKE_BINARY_DIR}/fonts)

# ---- Create an installable target ----
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
  "fmt 11.0.2"
)
