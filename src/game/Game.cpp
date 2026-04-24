#include "Game.hpp"

#include <stdexcept>


Game::Game::Game()
: players_() {}

[[nodiscard]] bool Game::Game::hasAllPlayers() const noexcept
{
  return players_.first.has_value() && players_.second.has_value();
}

[[nodiscard]] bool Game::Game::joinPlayer(unsigned int newPlayer) noexcept
{
    // set up first player if this first player
    if (players_.first.has_value() == false)
    {
        players_.first = newPlayer;
        return true;
    }
    else
    {
        if (players_.first == newPlayer)
        {
            // TODO: log same player trying to join agian
            return false;
        }
    }

    // player two
    if (players_.second.has_value() == false)
    {
        players_.second = newPlayer;
        return true;
    }
    else
    {
        if (players_.second == newPlayer)
        {
            // TODO: log same player trying to join agian
            return false;
        }
    }

    return false;
}
