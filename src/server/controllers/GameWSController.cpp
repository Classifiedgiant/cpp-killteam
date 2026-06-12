#include "GameWSController.hpp"

#include <memory>

#include <json/json.h>

#include "Game.hpp"
#include "game_states/StartGameState.hpp"
#include "game_states/WaitingForPlayerState.hpp"


// declared in the main.cpp
// due to unable to pass in the constructor
// due to Websocket controller
extern std::unique_ptr<Game::Game> game;


void Controllers::GameWsController::handleNewConnection(const drogon::HttpRequestPtr& req,
                                                    const drogon::WebSocketConnectionPtr& conn)
{
    const auto playerToken    = req->getParameter("wsToken");
    const auto playerPositionStr = req->getParameter("playerPosition");

    const auto [succeeded, errMsg] = game->ConnectPlayerWebSocket(playerToken, playerPositionStr, conn);
    if (!succeeded)
    {
        conn->shutdown(drogon::CloseCode::kViolation, errMsg);
        return;
    }

    if (game->IsFull())
    {
        // if all players have joined, then start the game.
        game->NotifyPlayersOfStateChange<GameState::StartGameState>();
    }
    else 
    {
        // we are still waiting on one player.
        // The player connected needs to wait before the other player joins.
        game->NotifyPlayersOfStateChange<GameState::WaitingForPlayerState>();
    }
}

void Controllers::GameWsController::handleConnectionClosed(const drogon::WebSocketConnectionPtr& /*conn*/)
{
}

void Controllers::GameWsController::handleNewMessage(const drogon::WebSocketConnectionPtr& conn,
                                                        std::string&& message,
                                                        const drogon::WebSocketMessageType& type)
{
    if (type != drogon::WebSocketMessageType::Text)
    {
        Json::Value errorJson{};
        errorJson["error"] = "Incorrect WebSocket Message Type. Needs to be Text";
        conn->sendJson(errorJson);
        return;
    }

    Json::Value body;
    Json::Reader reader;

    if (!reader.parse(message, body))
    {
        Json::Value errorJson{};
        errorJson["error"] = "Invalid Json";
        conn->sendJson(errorJson);
        return;
    }
}
