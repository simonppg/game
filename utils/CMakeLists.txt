add_library(utils utils.c window_manager.c)
target_include_directories (utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
