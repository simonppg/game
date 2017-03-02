cmake_minimum_required (VERSION 2.6)
project (game)

add_subdirectory(utils)
add_subdirectory(character)

add_executable (game game.c)
set(CMAKE_BUILD_TYPE Debug)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} utils character ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
