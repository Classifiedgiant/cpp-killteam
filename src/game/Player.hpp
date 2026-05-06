#ifndef KILLTEAM_SRC_GAME_PLAYER_H
#define KILLTEAM_SRC_GAME_PLAYER_H

#include <cstdint>
#include <string>

namespace Game
{
class Player
{
// game connection info
std::uint32_t   playerId_;
std::string gameId_;
std::string gameConnectionToken_;

// game info
std::uint8_t playerPosition_;

public:
    Player(std::uint32_t playerId, std::string gameConnectionToken, std::string gameId, std::uint8_t playerPosition);

    std::uint32_t GetPlayerId() const { return playerId_; };
    std::string GetConnectioToken() const { return gameConnectionToken_; };
    std::string_view GetGameId() const { return gameId_; };
    std::uint8_t GetPlayerPosition() const { return playerPosition_; };
};
}

#endif