cmake_policy(SET CMP0048 NEW)

project(TiEditor
    VERSION 0.1.0
)
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

set(SRCS
    ${SRC}/main.cpp
    ${SRC}/CodeEditor.cpp
    ${SRC}/EditorWindow.cpp 
    ${SRC}/TiCCompile.cpp 
    ${SRC}/TiCLexer.cpp 
)
set(HDRS
    ${HDR}/CodeEditor.hpp
    ${HDR}/EditorWindow.hpp 
    ${HDR}/TiCCompile.hpp 
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
    URL_HASH SHA256=79e9c39d51549061d3d489387bcee86ff20c1f746d1b25ac173d5165426eabaf
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

add_dependencies(tiedit project_qscintilla)
target_link_libraries(tiedit lib_qscintilla)

target_link_libraries(tiedit Qt5::Widgets)

# Find TiC 
find_package(TiC REQUIRED)
if(${TiC_FOUND})
    message(STATUS "TiC Lib: " ${TiC_LIBRARY})
    message(STATUS "TiC Include: " ${TiC_INCLUDE_DIRS})
    target_link_libraries(tiedit ${TiC_LIBRARY})
    include_directories(STATUS ${TiC_INCLUDE_DIRS})
endif()

# C++14
set (CMAKE_CXX_FLAGS "--std=gnu++14 ${CMAKE_CXX_FLAGS}")

# Install 
install(TARGETS tiedit 
    RUNTIME DESTINATION bin
)

# Packaging
set(CPACK_PACKAGE_NAME "tiedit")
set(CPACK_PACKAGE_VENDOR "maximaximal.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An IDE for Texas Instruments calculators with integrated support for Advanced TiBasic (TiC)")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Max Heisinger <mail@maximaximal.com>")
set(CPACK_PACKAGE_VERSION ${TiEditor_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR ${TiEditor_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${TiEditor_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${TiEditor_VERSION_PATCH})
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/maximaximal/TiSuite")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "TiC")

include(CPack)
