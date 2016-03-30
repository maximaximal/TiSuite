project(TiEditor)
cmake_minimum_required(VERSION 3.0.2)

include(ExternalProject)
include(FindPkgConfig)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

SET(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/)
SET(HDR ${CMAKE_CURRENT_SOURCE_DIR}/include/)
set(RSC ${CMAKE_CURRENT_SOURCE_DIR}/Data/ressources)
set(FOR ${CMAKE_CURRENT_SOURCE_DIR}/Data/forms)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR})

set(TiEditor_VERSION_MAJOR "0" CACHE STRING "Major-Version")
set(TiEditor_VERSION_MINOR "7" CACHE STRING "Minor-Version")
set(TiEditor_VERSION_PATCH "0" CACHE STRING "Patch-Version")
set(TiEditor_VERSION_TWEAK "0" CACHE STRING "Tweak-Version")
set(TiEditor_VERSION ${TiEditor_VERSION_MAJOR}.${TiEditor_VERSION_MINOR}.${TiEditor_VERSION_PATCH}.${TiEditor_VERSION_TWEAK})

set(SRCS
    ${SRC}/main.cpp
    ${SRC}/CodeEditor.cpp
    ${SRC}/EditorWindow.cpp 
    ${SRC}/TiHighlighter.cpp 
)
set(HDRS
    ${HDR}/CodeEditor.hpp
    ${HDR}/EditorWindow.hpp 
    ${HDR}/TiHighlighter.hpp
)
set(RSCS

)

# Find Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets)
find_package(Qt5Qml)
find_package(Qt5Quick)

add_executable(tiedit ${SRCS} ${HDRS} ${RSCS})

# Compatability with Wt and boost
ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

target_link_libraries(tiedit Qt5::Widgets Qt5::Qml Qt5::Quick)
