#include "Player.hpp"

Game::Player::Player(std::uint32_t playerId, std::string gameConnectionToken, std::string gameId, std::uint8_t playerPosition)
    : playerId_{playerId}
    , gameId_{gameId}
    , gameConnectionToken_{gameConnectionToken}
    , playerPosition_{playerPosition}
{}
