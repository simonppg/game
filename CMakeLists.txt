cmake_minimum_required (VERSION 2.6)
project (game)

# Creating a static library
add_library(player player.c)
target_include_directories (player PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(player utils)

# Creating a static library
add_library(utils utils.c window_manager.c)
target_include_directories (utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Creating the executable program
add_executable (game game.c)
set(CMAKE_BUILD_TYPE Debug)

# Setting dependencies
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

# Setting include directories
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

# Linking static and shared libraries
target_link_libraries(${PROJECT_NAME} utils player ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

# Adding test
enable_testing()
add_subdirectory(test)
