project(TiC)
cmake_minimum_required(VERSION 3.1)

include(ExternalProject)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HDR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${HDR})

set(HDRS
    ${HDR}/tic/Lexer.hpp
    ${HDR}/tic/SourceBlock.hpp
    ${HDR}/tic/TokenTree.hpp
    ${HDR}/tic/Type.hpp
    ${HDR}/tic/Error.hpp
    ${HDR}/tic/ErrorHandler.hpp
    ${HDR}/tic/AST.hpp

    ${HDR}/tic/ast/Node.hpp
    ${HDR}/tic/ast/List.hpp
    ${HDR}/tic/ast/Function.hpp
    ${HDR}/tic/ast/FunctionCall.hpp
    ${HDR}/tic/ast/FunctionParameter.hpp
    ${HDR}/tic/ast/VariableDeclaration.hpp
    ${HDR}/tic/ast/Variable.hpp
    ${HDR}/tic/ast/FunctionCall.hpp
)
set(SRCS
    ${SRC}/Lexer.cpp
    ${SRC}/SourceBlock.cpp
    ${SRC}/TokenTree.cpp
    ${SRC}/Type.cpp
    ${SRC}/Error.cpp
    ${SRC}/ErrorHandler.cpp
    ${SRC}/AST.cpp

    ${SRC}/ast/Node.cpp
    ${SRC}/ast/List.cpp
    ${SRC}/ast/Function.cpp
    ${SRC}/ast/FunctionParameter.cpp
    ${SRC}/ast/VariableDeclaration.cpp
    ${SRC}/ast/Variable.cpp
    ${SRC}/ast/FunctionCall.cpp
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