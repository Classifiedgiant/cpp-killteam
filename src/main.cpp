#include <iostream>
#include <memory>
#include <regex>

#include <drogon/drogon.h>

#include "CreateGameController.hpp"
#include "GameWSController.hpp"
#include "Game.hpp"


std::unique_ptr<Game::Game> game = std::make_unique<Game::Game>();

namespace
{
    const std::regex localhostOriginRegex(R"(^http://localhost(:\d+)?$)");

    std::string allowedOriginFor(const drogon::HttpRequestPtr &req)
    {
        const auto &origin = req->getHeader("Origin");
        if (std::regex_match(origin, localhostOriginRegex))
        {
            return origin;
        }
        return "http://localhost";
    }
}

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


    // Add cors pre and postflight checks
    drogonApp.registerPreRoutingAdvice(
        [](const drogon::HttpRequestPtr &req,
        drogon::AdviceCallback &&callback,
        drogon::AdviceChainCallback &&chainCallback) {
            if (req->method() == drogon::Options)
            {
                auto resp = drogon::HttpResponse::newHttpResponse();
                resp->addHeader("Access-Control-Allow-Origin", allowedOriginFor(req));
                resp->addHeader("Access-Control-Allow-Methods", "GET,POST,PUT,DELETE,OPTIONS");
                resp->addHeader("Access-Control-Allow-Headers", "Content-Type,Authorization");
                callback(resp);
                return;
            }
            chainCallback();
        });

    drogonApp.registerPostHandlingAdvice(
        [](const drogon::HttpRequestPtr &req, const drogon::HttpResponsePtr &resp) {
            resp->addHeader("Access-Control-Allow-Origin", allowedOriginFor(req));
        });

    drogonApp.run();

    return 0;
}
