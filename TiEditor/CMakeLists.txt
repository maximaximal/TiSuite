cmake_policy(SET CMP0048 NEW)

project(TiEditor
    VERSION 0.3.4
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

# Macro for CXX11
macro(Use_CXX11)
    if (CMAKE_VERSION VERSION_LESS "3.1")
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            set (CMAKE_CXX_FLAGS "-std=gnu++11 ${CMAKE_CXX_FLAGS}")
        endif ()
    else ()
        set (CMAKE_CXX_STANDARD 11)
    endif ()
endmacro(Use_CXX11)
Use_CXX11()

# Find Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets)

add_executable(tiedit ${SRCS} ${HDRS} ${RSCS})

add_definitions(${Qt5Widgets_DEFINITIONS})

target_link_libraries(tiedit Qt5::Widgets)

# Find QScintilla
find_package(QScintilla REQUIRED)
if(${QSCINTILLA_FOUND})
    target_link_libraries(tiedit ${QSCINTILLA_LIBRARY} ${QSCINTILLA_LIBRARIES})
    include_directories(SYSTEM ${QSCINTILLA_INCLUDE_DIR} ${QSCINTILLA_INCLUDE_DIRS})
endif()

# Find TiC 
find_package(TiC REQUIRED)
if(${TiC_FOUND})
    message(STATUS "TiC Lib: " ${TiC_LIBRARY})
    message(STATUS "TiC Include: " ${TiC_INCLUDE_DIRS})
    target_link_libraries(tiedit ${TiC_LIBRARY})
    include_directories(STATUS ${TiC_INCLUDE_DIRS})
endif()

# Config
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.hpp.in"
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Config.hpp)

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
set(CPACK_DEBIAN_PACKAGE_DEPENDS "tic-lib (>= 0.3.0), libqt5widgets5 (>= 5.2.1), libqt5scintilla2-11 (>= 2.8.1-2)")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/maximaximal/TiSuite")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "TiC")

include(CPack)
