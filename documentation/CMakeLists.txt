cmake_minimum_required(VERSION 3.14...3.22)

project(HobbyDocs)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

cpmaddpackage(NAME Hobby SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

# ---- Doxygen variables ----

# set Doxyfile variables
set(DOXYGEN_PROJECT_NAME Hobby)
set(DOXYGEN_PROJECT_VERSION ${Hobby_VERSION})
set(DOXYGEN_PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}/..")
set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doxygen")

find_package(Doxygen REQUIRED)

set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/docs)
configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

add_custom_target(GenerateDocs
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM)
