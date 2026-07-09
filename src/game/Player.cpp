#include "Player.hpp"

namespace Game {
Player::Player(std::uint32_t playerId, std::string gameConnectionToken, std::string gameId, std::uint8_t playerPosition)
    : gameId_{gameId}
    , gameConnectionToken_{gameConnectionToken}
    , playerId_{playerId}
    , playerPosition_{playerPosition}
{}

void Player::SendMsg(std::string dataBuf)
{
    if (webSocketConnection_)
    {
        webSocketConnection_->send(dataBuf, drogon::WebSocketMessageType::Binary);
        return;
    }

    std::cout << "Can't send message to player " << playerPosition_ << " as there is no websocketConnection\n";
}
}