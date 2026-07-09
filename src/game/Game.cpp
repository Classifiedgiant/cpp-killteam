#include "Game.hpp"

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Player.hpp"

Game::Game::Game()
: gameId_{""}
, players_{} {}
// , currentState_{} {}


[[nodiscard]] bool Game::Game::IsPlayerInGame(std::uint32_t playerId) noexcept
{
    if (players_.first.has_value() && players_.first->GetPlayerId() == playerId)
        return true;

    if (players_.second.has_value() && players_.second->GetPlayerId() == playerId)
        return true;

    return false;
}

[[nodiscard]] bool Game::Game::IsFull() noexcept
{
    return players_.first.has_value() && players_.second.has_value();
}

void Game::Game::JoinPlayer(std::uint32_t playerId, std::string gameConnectionToken, std::string gameId) noexcept
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

[[nodiscard]] Game::Player* Game::Game::GetPlayer(unsigned int playerId) noexcept
{

    if (players_.first && players_.first->GetPlayerId() == playerId)
        return &players_.first.value();
    else if (players_.second && players_.second->GetPlayerId() == playerId)
        return &players_.second.value();

    std::cout << "Player " << playerId << " not found.\n";
    return nullptr;
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

std::pair<bool, std::string> Game::Game::ConnectPlayerWebSocket(std::string_view wsToken, std::string_view playerId, drogon::WebSocketConnectionPtr conn)
{
    if (wsToken.empty() || playerId.empty()) return {false, "Player Token or playerId is empty"};

    try
    {
        const auto id = static_cast<unsigned int>(std::stoull(std::string(playerId)));
        auto player = GetPlayer(id);

        if (!player)
            return {false, "Player not in game"};

        if (player->GetConnectionToken() != wsToken)
            return {false, "Player can't access game"};

        player->SetWebsocketConnected(conn);
    }
    catch (const std::exception& ex)
    {
        std::cout << "Unable to pass playerId: " << playerId << "\n";
        return {false, "Player not in game"};
    }

    return {true, ""};
}
