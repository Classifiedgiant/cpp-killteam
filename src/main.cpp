#include <iostream>
#include <memory>

#include <drogon/drogon.h>

#include "CreateGameController.hpp"
#include "Game.hpp"


int main()
{
    auto game = std::make_unique<Game::Game>();

    auto createGameController = std::make_shared<Controllers::CreateGameController>(*game);

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
                createGameController->asyncHandleHttpRequest(req, std::move(callback));
            }
    );
    drogonApp.run();

    return 0;
}
