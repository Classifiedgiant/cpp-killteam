#ifndef KILLTEAM_SRC_GAME_PLAYER_H
#define KILLTEAM_SRC_GAME_PLAYER_H

#include <cstdint>
#include <string>

// TODO: Create a ServerPlayer class
// to handle drogon & player related element
// This would remove this include dependency
// in the Player class
#include <drogon/WebSocketConnection.h>

namespace Game
{
class Player
{
// game connection info
std::string gameId_;
std::string gameConnectionToken_;
drogon::WebSocketConnectionPtr webSocketConnection_ = nullptr;

// game info
std::uint32_t   playerId_;
std::uint8_t playerPosition_;

public:
    Player(std::uint32_t playerId, std::string gameConnectionToken, std::string gameId, std::uint8_t playerPosition);

    std::uint32_t GetPlayerId() const { return playerId_; };
    std::string GetConnectionToken() const { return gameConnectionToken_; };
    std::string_view GetGameId() const { return gameId_; };
    std::uint8_t GetPlayerPosition() const { return playerPosition_; };

    // connectioninfo
    bool IsWebSocketConnected() const { return webSocketConnection_ == nullptr;};
    void SetWebsocketConnected(const drogon::WebSocketConnectionPtr connection) { webSocketConnection_ = connection; };
    void SendMsg(std::string dataBuf);
};
}

#endif