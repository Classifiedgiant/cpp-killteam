#include <iostream>
#include <memory>

#include <drogon/drogon.h>

#include "CreateGameController.hpp"
#include "GameWSController.hpp"
#include "Game.hpp"


std::unique_ptr<Game::Game> game = std::make_unique<Game::Game>();

int main()
{

    auto createGameController = std::make_shared<Controllers::CreateGameController>(*game);
    auto gameWsController = std::make_shared<Controllers::GameWsController>();

    std::cout << "Starting the server...\n";
    auto& drogonApp = drogon::app();

    drogonApp.setLogPath("./")
    .setLogLevel(trantor::Logger::kWarn)
    .addListener("0.0.0.0", 1337)
    .setThreadNum(16);

    drogonApp.registerController(createGameController);

    drogonApp.registerHandler(
        "/game",
        [&createGameController] (const drogon::HttpRequestPtr& req,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback)
            {
                createGameController->joinGame(req, std::move(callback));
            },
        {drogon::Post}
    );

    drogonApp.registerWebSocketController("/game", "Controllers::GameWsController");
    drogonApp.registerWebSocketControllerRegex("/game/[^/]*", "Controllers::GameWsController");

    drogonApp.run();

    return 0;
}
