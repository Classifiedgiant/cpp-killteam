#include "Game.hpp"

#include <stdexcept>


Game::Game::Game(unsigned int player)
: players_()
{
    // game is always started by one player
    if (player == 0)
    {
        throw std::domain_error("Player can't be 0");
    }
    players_.first = player;
}

[[nodiscard]] bool Game::Game::hasAllPlayers() const noexcept
{
  return players_.first > 0 && players_.second > 0;
}

[[nodiscard]] bool Game::Game::joinPlayer(unsigned int newPlayer) noexcept
{
    if (players_.first == newPlayer
        || players_.second == newPlayer
        || players_.second > 0)
    {
        return false;
    }

    players_.second = newPlayer;
    return true;
}
