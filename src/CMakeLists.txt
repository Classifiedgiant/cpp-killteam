find_package(Drogon CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp

    # Controllers
    server/controllers/CreateGameController.cpp
    )

target_include_directories(${PROJECT_NAME}
PRIVATE
    server/controllers)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    Drogon::Drogon
    GameLib)