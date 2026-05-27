#include "Player.hpp"

namespace Game {
Player::Player(std::uint32_t playerId, std::string gameConnectionToken, std::string gameId, std::uint8_t playerPosition)
    : playerId_{playerId}
    , gameId_{gameId}
    , gameConnectionToken_{gameConnectionToken}
    , playerPosition_{playerPosition}
{}

void Player::SendMsg(std::string jsonMsg)
{
    if (webSocketConnection_)
    {
        webSocketConnection_->send(jsonMsg);
        return;
    }

    std::cout << "Can't send message to player " << playerPosition_ << " as there is no websocketConnection\n";
}
}