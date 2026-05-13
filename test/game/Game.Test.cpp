#include <catch2/catch_test_macros.hpp>

#include <tuple>

#include "Game.hpp"

using namespace std::string_literals;

auto CreatePlayer(std::uint32_t playerId)
{
    return std::make_tuple(playerId, "abc"s, "1231234"s);
}

void JoinPlayer(Game::Game& sut, auto args) {
    std::apply([&sut](auto&&... playerArgs) { sut.JoinPlayer(playerArgs...); }, args);
}

// Test Constants
const std::string gameId = "asdfs10";

TEST_CASE("Game does not have all players without a join")
{
    Game::Game sut;
    CHECK_FALSE(sut.IsFull());

    JoinPlayer(sut, CreatePlayer(1));
    
    CHECK_FALSE(sut.IsFull());
}

TEST_CASE("Game is ready when all Players join")
{
    Game::Game sut;
    JoinPlayer(sut, CreatePlayer(1));
    JoinPlayer(sut, CreatePlayer(2));
    CHECK(sut.IsFull());
}

TEST_CASE("Game cannot join the same player again")
{
    Game::Game sut;

    JoinPlayer(sut, CreatePlayer(2));
    JoinPlayer(sut, CreatePlayer(2));
    CHECK(sut.IsFull());
    CHECK(sut.IsPlayerInGame(2));
}

TEST_CASE("Game cannot join more than two players")
{
    Game::Game sut;

    JoinPlayer(sut, CreatePlayer(1));
    JoinPlayer(sut, CreatePlayer(2));
    CHECK(sut.IsFull());

    JoinPlayer(sut, CreatePlayer(4));
    CHECK_FALSE(sut.IsPlayerInGame(4));
}

TEST_CASE("Player websocket connections fails when either token or playerPositions it empty")
{
    Game::Game sut{};

    CHECK_FALSE(sut.ConnectPlayerWebSocket("", "randomVal").first);
    CHECK_FALSE(sut.ConnectPlayerWebSocket("ablsdofdsfo", "").first);
}

TEST_CASE("Player websocket connections fails when either playerPosition is not convertable to values 1 or 2")
{
    Game::Game sut{};

    // fill the game with players
    sut.JoinPlayer(1234, "abc", gameId);
    sut.JoinPlayer(102, "def", gameId);

    CHECK_FALSE(sut.ConnectPlayerWebSocket("abc", "10239").first);
    CHECK_FALSE(sut.ConnectPlayerWebSocket("abc", "abc").first);
    CHECK_FALSE(sut.ConnectPlayerWebSocket("abc", "abc1").first);
}

TEST_CASE("Player websocket connections fails when token doesn't match token")
{
    Game::Game sut{};

    sut.JoinPlayer(1234, "abc", gameId);

    CHECK_FALSE(sut.ConnectPlayerWebSocket("def", "1").first);
}

TEST_CASE("Player websocket connection passes when token and player position match")
{
    Game::Game sut{};

    sut.JoinPlayer(102, "abc", gameId);
    sut.JoinPlayer(12, "lol", gameId);

    CHECK(sut.ConnectPlayerWebSocket("abc", "1").first);
    CHECK(sut.ConnectPlayerWebSocket("lol", "2").first);
}


