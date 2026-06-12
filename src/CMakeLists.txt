find_package(Drogon CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp

    # Controllers
    server/controllers/CreateGameController.cpp
    server/controllers/GameWSController.cpp)

target_include_directories(${PROJECT_NAME}
PRIVATE
    server/controllers
    util

    # for the generate protobuf files
    ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME}
PRIVATE
    Drogon::Drogon
    GameLib)
