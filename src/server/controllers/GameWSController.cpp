#include "GameWSController.hpp"

#include <memory>

#include <json/json.h>
#include <print>

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
    const auto playerId = req->getParameter("playerId");

    const auto [succeeded, errMsg] = game->ConnectPlayerWebSocket(playerToken, playerId, conn);
    std::println("Player Connected. Player Id {0}, Player Token {1}, Websocket: {2}", playerId, playerToken, succeeded);
    if (!succeeded)
    {
        conn->shutdown(drogon::CloseCode::kViolation, errMsg);
        return;
    }

    if (game->IsFull())
    {
        std::println("Game Is Full");
        // if all players have joined, then start the game.
        const auto players = game->GetPlayers();
        const auto p1 = players.first->GetPlayerId();
        const auto p2 = players.second->GetPlayerId();
        game->NotifyPlayersOfStateChange<GameState::StartGameState>(p1, p2);
    }
    else 
    {
        // we are still waiting on one player.
        // The player connected needs to wait before the other player joins.
        std::println("Waiting");
        game->NotifyPlayersOfStateChange<GameState::WaitingForPlayerState>();
    }
}

void Controllers::GameWsController::handleConnectionClosed(const drogon::WebSocketConnectionPtr& /*conn*/)
{
}

void Controllers::GameWsController::handleNewMessage(const drogon::WebSocketConnectionPtr& /*conn*/,
                                                        std::string&& /*message*/,
                                                        const drogon::WebSocketMessageType& /*type*/)
{
}
