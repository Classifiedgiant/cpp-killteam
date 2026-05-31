find_package(Drogon CONFIG REQUIRED)
find_package(Protobuf REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp

    # Controllers
    server/controllers/CreateGameController.cpp
    server/controllers/GameWSController.cpp

    # Proto files
    ${CMAKE_SOURCE_DIR}/data/gamestates/startgame.proto
    )

target_include_directories(${PROJECT_NAME}
PRIVATE
    server/controllers
    util

    # for the generate protobuf files
    ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME}
PRIVATE
    Drogon::Drogon
    protobuf::libprotobuf
    GameLib)

protobuf_generate(TARGET ${PROJECT_NAME} IMPORT_DIRS ${CMAKE_SOURCE_DIR}/data/gamestates)
