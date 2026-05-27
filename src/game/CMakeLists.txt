project(GameLib LANGUAGES CXX)

find_package(jsoncpp CONFIG REQUIRED)

add_library(${PROJECT_NAME}
    Game.cpp
    Player.cpp)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
PUBLIC
    JsonCpp::JsonCpp)

