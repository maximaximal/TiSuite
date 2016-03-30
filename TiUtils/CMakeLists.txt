project(TiUtils)
cmake_minimum_required(VERSION 2.8)

include(ExternalProject)

set(ENV{PKG_CONFIG_PATH} 
    "${CMAKE_BINARY_DIR}/Libs/lib/pkgconfig/:$ENV{PKG_CONFIG_PATH}")
set(ENV{LDFLAGS} 
    "$LDFLAGS -lm")

ExternalProject_Add(TiCables
    URL ${CMAKE_CURRENT_SOURCE_DIR}/libticables2-1.3.4.tar.bz2
    CONFIGURE_COMMAND env PKG_CONFIG_PATH=${CMAKE_BINARY_DIR}/Libs/lib/pkgconfig ./configure --enable-libusb10 --prefix=${CMAKE_BINARY_DIR}/Libs
    BUILD_COMMAND make
    BUILD_IN_SOURCE 1
)
ExternalProject_Add(TiConv
    URL ${CMAKE_CURRENT_SOURCE_DIR}/libticonv-1.1.4.tar.bz2
    CONFIGURE_COMMAND env PKG_CONFIG_PATH=${CMAKE_BINARY_DIR}/Libs/lib/pkgconfig ./configure --prefix=${CMAKE_BINARY_DIR}/Libs
    BUILD_COMMAND make
    BUILD_IN_SOURCE 1
)
ExternalProject_Add(TiCalcs
    URL ${CMAKE_CURRENT_SOURCE_DIR}/libticalcs2-1.1.8.tar.bz2
    CONFIGURE_COMMAND env PKG_CONFIG_PATH=${CMAKE_BINARY_DIR}/Libs/lib/pkgconfig ./configure --prefix=${CMAKE_BINARY_DIR}/Libs
    BUILD_COMMAND make
    BUILD_IN_SOURCE 1
)
ExternalProject_Add(TiFiles
    DEPENDS TiConv
    URL ${CMAKE_CURRENT_SOURCE_DIR}/libtifiles2-1.1.6.tar.bz2
    CONFIGURE_COMMAND env PKG_CONFIG_PATH=${CMAKE_BINARY_DIR}/Libs/lib/pkgconfig ./configure --prefix=${CMAKE_BINARY_DIR}/Libs
    BUILD_COMMAND make
    BUILD_IN_SOURCE 1
)

ExternalProject_Add(TiLP
    DEPENDS TiCables TiFiles TiConv TiCalcs
    URL ${CMAKE_CURRENT_SOURCE_DIR}/tilp.tar.gz
    CONFIGURE_COMMAND env PKG_CONFIG_PATH=${CMAKE_BINARY_DIR}/Libs/lib/pkgconfig ./configure --prefix=${CMAKE_BINARY_DIR}/Libs
    BUILD_COMMAND make
    BUILD_IN_SOURCE 1
)
ExternalProject_Add(TilEm
    DEPENDS TiCables TiFiles TiConv TiCalcs
    URL ${CMAKE_CURRENT_SOURCE_DIR}/tilem-2.0.tar.bz2
    CONFIGURE_COMMAND env PKG_CONFIG_PATH=${CMAKE_BINARY_DIR}/Libs/lib/pkgconfig ./configure --prefix=${CMAKE_BINARY_DIR}/Libs
    BUILD_COMMAND make
    BUILD_IN_SOURCE 1
)
ExternalProject_Add(tibasic
    URL ${CMAKE_CURRENT_SOURCE_DIR}/tibasic-1.4.2.tar.bz2
    CONFIGURE_COMMAND ""
    BUILD_COMMAND make
    INSTALL_COMMAND cp tibasic ${CMAKE_BINARY_DIR}/Libs/bin
    BUILD_IN_SOURCE 1
)

set(HDRS
)
set(SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(tiutils ${SRCS} ${HDRS})

add_dependencies(tiutils TiLP)
add_dependencies(tiutils tibasic)
