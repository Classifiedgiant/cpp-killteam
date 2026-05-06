#include "Game.hpp"

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Player.hpp"

Game::Game::Game()
: players_() {}

[[nodiscard]] bool Game::Game::IsPlayerInGame(std::uint32_t playerId) noexcept 
{
    if (players_.first.has_value() && players_.first->GetPlayerPosition() == playerId)
        return true;

    if (players_.second.has_value() && players_.second->GetPlayerPosition() == playerId)
        return true;

    return false;
}

[[nodiscard]] bool Game::Game::IsFull() noexcept 
{
    return players_.first.has_value() && players_.second.has_value();
}

void Game::Game::joinPlayer(std::uint32_t playerId, std::string gameConnectionToken, std::string gameId) noexcept
{
    if (IsFull())
    {
        std::cout << "Game is full\n";
        return;
    }

    if (IsPlayerInGame(playerId))
    {
        std::cout << "Player already in the game\n";
        return;
    }

    if (players_.first.has_value())
        players_.second = Player(playerId, gameConnectionToken, gameId, 2);
    else
        players_.first = Player(playerId, gameConnectionToken, gameId, 1);
}

void Game::Game::SetGameId(const std::string gameId)
{
    if (!this->gameId_.empty())
    {
        std::cout << "Game Id is already set\n";
        return;
    }

    gameId_  = gameId;
}
