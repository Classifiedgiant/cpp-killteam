#include "GameWSController.hpp"

#include <memory>
#include "Game.hpp"

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