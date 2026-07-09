#ifndef KILLTEAM_SRC_GAME_H
#define KILLTEAM_SRC_GAME_H

#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

#include <json/json.h>

#include "Player.hpp"

// needed for HasCreateStateCommand state
#include "game_states/StateConcepts.hpp"
#include "server_message.pb.h"

using Players = std::pair<std::optional<Game::Player>, std::optional<Game::Player>>;

namespace Game
{
class Game
{
std::string gameId_ = {};

Players players_;

// TODO: Add back later
// GameStates::IGameState* currentState_ = nullptr;

public:
Game();

[[nodiscard]] bool IsPlayerInGame(std::uint32_t playerId) noexcept;
[[nodiscard]] bool IsFull() noexcept;

void JoinPlayer(std::uint32_t playerId, std::string gameConnectionToken, std::string gameId) noexcept;

[[nodiscard]] Player* GetPlayer(unsigned int playerId) noexcept;
[[nodiscard]] const Players& GetAllPlayers() noexcept { return players_; }

std::string GetGameId() const noexcept { return gameId_; };
void SetGameId(const std::string gameId);

std::pair<bool, std::string> ConnectPlayerWebSocket(std::string_view wsToken, std::string_view playerPosition, drogon::WebSocketConnectionPtr conn);

template<typename T, typename... Args>
requires HasCreateStateCommand<T, Args...>
void NotifyPlayersOfStateChange(Args&&... args) {

    std::cout << "Notifying players...\n";
    auto stateMessage = T::CreateStateCommand(std::forward<Args>(args)...);

    GameStates::ServerMessage envelope{};
    SetServerMessagePayload(envelope, stateMessage);

    std::string serializeStr{};
    envelope.SerializeToString(&serializeStr);

    if (players_.first.has_value())
        players_.first->SendMsg(serializeStr);

    if (players_.second.has_value())
        players_.second->SendMsg(serializeStr);
}

private:
static void SetServerMessagePayload(GameStates::ServerMessage& envelope, const GameStates::StartGame& msg) {
    *envelope.mutable_startgame() = msg;
}

static void SetServerMessagePayload(GameStates::ServerMessage& envelope, const GameStates::WaitingForPlayer& msg) {
    *envelope.mutable_waitingforplayer() = msg;
}

bool IsBothPlayerWebSocketConnected() const { return players_.first->IsWebSocketConnected() && players_.second->IsWebSocketConnected(); };
};
}


#endif