project(TestApp LANGUAGES CXX)

find_package(Catch2 CONFIG REQUIRED)
include(CTest)
include(Catch)

add_executable(${PROJECT_NAME}
    game/Game.Test.cpp

    # Controllers
    server/controllers/CreateGameController.Test.cpp)


target_link_libraries(${PROJECT_NAME}
PRIVATE
    Catch2::Catch2WithMain
    GameLib)

catch_discover_tests(${PROJECT_NAME})
