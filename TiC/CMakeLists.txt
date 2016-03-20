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
)
set(SRCS
    ${SRC}/Lexer.cpp
    ${SRC}/SourceBlock.cpp
    ${SRC}/TokenTree.cpp
    ${SRC}/Type.cpp
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

find_package(Boost COMPONENTS system program_options REQUIRED)
if(${Boost_FOUND})
    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
    target_link_libraries(tic  ${Boost_LIBRARIES})
    target_link_libraries(ticf ${Boost_LIBRARIES})
endif()
