#include "GameWSController.hpp"

#include <memory>

#include "ControllerHelper.hpp"
#include "Game.hpp"

// declared in the main.cpp
// due to unable to pass in the constructor
extern std::unique_ptr<Game::Game> game;


void Controllers::GameWsController::handleNewConnection(const drogon::HttpRequestPtr& connPtr,
                                                    const drogon::WebSocketConnectionPtr& conn)
{

}

void Controllers::GameWsController::handleConnectionClosed(const drogon::WebSocketConnectionPtr& conn)
{

}

void Controllers::GameWsController::handleNewMessage(const drogon::WebSocketConnectionPtr& conn,
                                                        std::string&& message,
                                                        const drogon::WebSocketMessageType& type)
{

   const auto blah = game->hasAllPlayers();
}