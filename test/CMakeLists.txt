project(TestApp LANGUAGES CXX)

find_package(Catch2 CONFIG REQUIRED)
find_package(Drogon CONFIG REQUIRED)
include(CTest)
include(Catch)

add_executable(${PROJECT_NAME}
    game/Game.Test.cpp

    # Controllers
    ${CMAKE_SOURCE_DIR}/src/server/controllers/CreateGameController.cpp
    server/controllers/CreateGameController.Test.cpp)


target_include_directories(${PROJECT_NAME}
PRIVATE
    ${CMAKE_SOURCE_DIR}/src/server/controllers
    ${CMAKE_SOURCE_DIR}/src/util)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    Catch2::Catch2WithMain
    Drogon::Drogon
    GameLib)

catch_discover_tests(${PROJECT_NAME})
