add_library(character character.c)
target_include_directories (character PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
TARGET_LINK_LIBRARIES(character utils)
