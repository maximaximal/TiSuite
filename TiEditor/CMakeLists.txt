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
    ${SRC}/TiCLexer.cpp 
)
set(HDRS
    ${HDR}/CodeEditor.hpp
    ${HDR}/EditorWindow.hpp 
    ${HDR}/TiCLexer.hpp
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

# Download QScintilla
ExternalProject_Add(project_qscintilla
    URL https://sourceforge.net/projects/pyqt/files/QScintilla2/QScintilla-2.9.1/QScintilla-gpl-2.9.1.tar.gz/download
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/qscintilla-2.9.1
    SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/qscintilla-2.9.1/src/project_qscintilla/
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND cd Qt4Qt5 && qmake qscintilla.pro
    BUILD_IN_SOURCE 1
    BUILD_COMMAND cd Qt4Qt5 && make
    INSTALL_COMMAND ""
)
add_library(lib_qscintilla SHARED IMPORTED)
set_property(TARGET lib_qscintilla PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/qscintilla-2.9.1/src/project_qscintilla/Qt4Qt5/libqscintilla2.so)
add_dependencies(lib_qscintilla project_qscintilla)
set(QSCINTILLA_INCLUDE_DIRS )
include_directories("${CMAKE_CURRENT_BINARY_DIR}/qscintilla-2.9.1/src/project_qscintilla/Qt4Qt5")

target_link_libraries(tiedit lib_qscintilla)

target_link_libraries(tiedit Qt5::Widgets Qt5::Qml Qt5::Quick)

# Link TiC
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../TiC/ TiC)
target_link_libraries(tiedit tic)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../TiC/include)

# C++11
set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
