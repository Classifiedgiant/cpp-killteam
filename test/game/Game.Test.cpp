#include <catch2/catch_test_macros.hpp>

#include <tuple>

#include "Game.hpp"

using namespace std::string_literals;

auto CreatePlayer(std::uint32_t playerId)
{
    return std::make_tuple(playerId, "abc"s, "1231234"s);
}

void JoinPlayer(Game::Game& sut, auto args) {
    std::apply([&sut](auto&&... playerArgs) { sut.joinPlayer(playerArgs...); }, args);
}

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



