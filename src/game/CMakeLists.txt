project(GameLib LANGUAGES CXX)

add_library(${PROJECT_NAME}
    Game.cpp)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})

