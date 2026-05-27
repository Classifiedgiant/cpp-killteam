#ifndef KILLTEAM_SRC_GAME_H
#define KILLTEAM_SRC_GAME_H

#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

#include <json/json.h>

// #include "game_states/IGameState.hpp"
#include "Player.hpp"


namespace Game
{
class Game
{
std::string gameId_ = {};

std::pair<std::optional<Player>, std::optional<Player>> players_;

// TODO: Add back later
// GameStates::IGameState* currentState_ = nullptr;

public:
Game();

[[nodiscard]] bool IsPlayerInGame(std::uint32_t playerId) noexcept;
[[nodiscard]] bool IsFull() noexcept;

void JoinPlayer(std::uint32_t playerId, std::string gameConnectionToken, std::string gameId) noexcept;

[[nodiscard]] std::optional<Player> GetPlayer(unsigned int player) noexcept;

std::string GetGameId() const noexcept { return gameId_; };
void SetGameId(const std::string gameId);

std::pair<bool, std::string> ConnectPlayerWebSocket(std::string_view wsToken, std::string_view playerPosition, drogon::WebSocketConnectionPtr conn);

void NotifyPlayers(std::string jsonMsg);

private:
bool IsBothPlayerWebSocketConnected() const { return players_.first->IsWebSocketConnected() && players_.second->IsWebSocketConnected(); };
};
}


#endif