#ifndef KILLTEAM_SRC_GAME_GAMESTATE_H
#define KILLTEAM_SRC_GAME_GAMESTATE_H

#include <optional>
#include <string>
#include <string_view>
#include <utility>

#include "Player.hpp"

namespace Game
{
class Game
{
std::string gameId_;
std::string connectionToken_;

std::pair<std::optional<Player>, std::optional<Player>> players_;

public:
Game();

[[nodiscard]] bool IsPlayerInGame(std::uint32_t playerId) noexcept;
[[nodiscard]] bool IsFull() noexcept;

void JoinPlayer(std::uint32_t playerId, std::string gameConnectionToken, std::string gameId) noexcept;

[[nodiscard]] std::optional<Player> GetPlayer(unsigned int player) noexcept;

std::string GetGameId() const noexcept { return gameId_; };
void SetGameId(const std::string gameId);

std::pair<bool, std::string> ConnectPlayerWebSocket(std::string_view wsToken, std::string_view playerPosition);
};
}


#endif