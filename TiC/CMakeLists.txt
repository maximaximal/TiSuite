project(TiC)
cmake_minimum_required(VERSION 3.1)

include(ExternalProject)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HDR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(TIC_VERSION_MAJOR 0)
set(TIC_VERSION_MINOR 2)
set(TIC_VERSION_PATCH 0)
set(TIC_VERSION ${TIC_VERSION_MAJOR}.${TIC_VERSION_MINOR}.${TIC_VERSION_PATCH})

include_directories(${HDR})

set(HDRS
    ${HDR}/tic/Lexer.hpp
    ${HDR}/tic/SourceBlock.hpp
    ${HDR}/tic/TokenTree.hpp
    ${HDR}/tic/Type.hpp
    ${HDR}/tic/Error.hpp
    ${HDR}/tic/ErrorHandler.hpp
    ${HDR}/tic/AST.hpp
    ${HDR}/tic/OutputMgr.hpp

    ${HDR}/tic/ast/Node.hpp
    ${HDR}/tic/ast/List.hpp
    ${HDR}/tic/ast/Scope.hpp
    ${HDR}/tic/ast/Function.hpp
    ${HDR}/tic/ast/Program.hpp
    ${HDR}/tic/ast/FunctionCall.hpp
    ${HDR}/tic/ast/FunctionParameter.hpp
    ${HDR}/tic/ast/VariableDeclaration.hpp
    ${HDR}/tic/ast/Variable.hpp
    ${HDR}/tic/ast/FunctionCall.hpp
    ${HDR}/tic/ast/Number.hpp
    ${HDR}/tic/ast/Command.hpp
    ${HDR}/tic/ast/Return.hpp
)
set(SRCS
    ${SRC}/Lexer.cpp
    ${SRC}/SourceBlock.cpp
    ${SRC}/TokenTree.cpp
    ${SRC}/Type.cpp
    ${SRC}/Error.cpp
    ${SRC}/ErrorHandler.cpp
    ${SRC}/OutputMgr.cpp
    ${SRC}/AST.cpp
    ${SRC}/AST_PythonModules.cpp

    ${SRC}/ast/Node.cpp
    ${SRC}/ast/List.cpp
    ${SRC}/ast/Scope.cpp
    ${SRC}/ast/Function.cpp
    ${SRC}/ast/Program.cpp
    ${SRC}/ast/Unsafe.cpp
    ${SRC}/ast/UnsafeVariable.cpp
    ${SRC}/ast/FunctionParameter.cpp
    ${SRC}/ast/VariableDeclaration.cpp
    ${SRC}/ast/Variable.cpp
    ${SRC}/ast/FunctionCall.cpp
    ${SRC}/ast/Number.cpp
    ${SRC}/ast/Command.cpp
    ${SRC}/ast/Return.cpp
)

# Macro for CXX14
macro(Use_CXX14)
    if (CMAKE_VERSION VERSION_LESS "3.1")
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            set (CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")
        endif ()
    else ()
        set (CMAKE_CXX_STANDARD 14)
    endif ()
endmacro(Use_CXX14)
Use_CXX14()

add_library(tic SHARED ${SRCS} ${HDRS})
add_executable(ticf ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_link_libraries(ticf tic)

set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost COMPONENTS system program_options python3 REQUIRED)
if(${Boost_FOUND})
    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
    target_link_libraries(tic  ${Boost_LIBRARIES})
    target_link_libraries(ticf ${Boost_LIBRARIES})
endif()

find_package(PythonLibs REQUIRED)
if(${PYTHONLIBS_FOUND})
    message(STATUS "Python Libraries: " ${PYTHON_LIBRARY})
    target_link_libraries(tic ${PYTHON_LIBRARY})
    target_link_libraries(ticf ${PYTHON_LIBRARY})
    include_directories(SYSTEM ${PYTHON_INCLUDE_DIRS})
endif()

# CMake package 
include(GenerateExportHeader)
generate_export_header(tic)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/TiCConfigVersion.cmake"
    VERSION ${TIC_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# TiCConfig.cmake.in 
configure_file(${CMAKE_MODULE_PATH}/TiCConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/TiCConfig.cmake"
  COPYONLY
)

# Config File 
configure_file(${CMAKE_MODULE_PATH}/Config.hpp.in
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tic/Config.hpp)

set(ConfigPackageLocation lib/cmake)

# Install
install(TARGETS tic
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    COMPONENT lib
)
install(TARGETS ticf
    RUNTIME DESTINATION bin
    COMPONENT bin
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include
    COMPONENT dev
)
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/TiCConfigVersion.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/TiCConfig.cmake
    DESTINATION 
        ${ConfigPackageLocation}/tic/
    COMPONENT lib
)
# Packaging
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_RPM_COMPONENT_INSTALL ON)
set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
set(CPACK_DEB_USE_DISPLAY_NAME_IN_FILENAME ON)

set(CPACK_PACKAGE_NAME "tic")
set(CPACK_PACKAGE_VENDOR "maximaximal.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A toolset to compile the advanced TiBasic language.")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Max Heisinger <mail@maximaximal.com>")
set(CPACK_PACKAGE_VERSION ${TIC_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR ${TIC_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${TIC_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${TIC_VERSION_PATCH})
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/maximaximal/TiSuite")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "TiC")

set(CPACK_COMPONENTS_ALL lib dev bin)

set(CPACK_COMPONENT_BIN_DISPLAY_NAME "ticf")

set(CPACK_COMPONENT_DEV_DEPENDS lib)
set(CPACK_COMPONENT_BIN_DEPENDS lib)

set(CPACK_DEBIAN_LIB_PACKAGE_DEPENDS "libboost-system1.54.0, libboost-program-options1.54.0, libboost-python1.54.0")
set(CPACK_DEBIAN_DEV_PACKAGE_DEPENDS "tic-lib (>= 0.2.0)")
set(CPACK_DEBIAN_BIN_PACKAGE_DEPENDS "tic-lib (>= 0.2.0)")

set(CPACK_ALL_INSTALL_TYPES Full Developer)

include(CPack)
