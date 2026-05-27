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

[[nodiscard]] std::optional<Game::Player> Game::Game::GetPlayer(unsigned int player) noexcept
{
    switch (player)
    {
        case 1:
            return players_.first;
        case 2:
            return players_.second;

        default:
        {
            std::cout << "Player " << player << " not found.\n";
            return {};
        }
    }
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

std::pair<bool, std::string> Game::Game::ConnectPlayerWebSocket(std::string_view wsToken, std::string_view playerPosition, drogon::WebSocketConnectionPtr conn)
{
    if (wsToken.empty() || playerPosition.empty()) return {false, "Player Token or Player position is empty"};

    try
    {
        const auto playerPos = static_cast<unsigned int>(std::stoull(std::string(playerPosition)));
        auto player = GetPlayer(playerPos);

        if (!player)
            return {false, "Player not in game"};

        if (player->GetConnectionToken() != wsToken)
            return {false, "Player can't access game"};

        player->SetWebsocketConnected(conn);
    }
    catch (const std::exception& ex)
    {
        std::cout << "Unable to pass player position: " << playerPosition << "\n";
        return {false, "Player not in game"};
    }

    if (IsBothPlayerWebSocketConnected())
        NotifyPlayers("StartGame");
    else
        conn->send("WaitingForPlayers");


    return {true, ""};
}

void Game::Game::NotifyPlayers(std::string jsonMsg)
{
    players_.first->SendMsg(jsonMsg);
    players_.second->SendMsg(jsonMsg);
}