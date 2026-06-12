project(GameLib LANGUAGES CXX)

find_package(jsoncpp CONFIG REQUIRED)
find_package(Protobuf REQUIRED)

add_library(${PROJECT_NAME}
    Game.cpp
    Player.cpp

    # Proto files
    ${CMAKE_CURRENT_SOURCE_DIR}/proto/startgame.proto)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    game_states

    # protobuf files
    ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME}
PUBLIC
    JsonCpp::JsonCpp
    protobuf::libprotobuf)

protobuf_generate(TARGET ${PROJECT_NAME} IMPORT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/proto)