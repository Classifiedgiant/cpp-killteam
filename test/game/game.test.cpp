#include <catch2/catch_test_macros.hpp>

#include <Game.hpp>

TEST_CASE("Game throws when constructed with player as 0")
{
    CHECK_THROWS_AS(Game::Game(0), std::domain_error);
    CHECK_NOTHROW(Game::Game(1));
}

TEST_CASE("Game does not have all players without a join")
{
    Game::Game sut(120);
    CHECK_FALSE(sut.hasAllPlayers());
}

TEST_CASE("Game is ready when all Players join")
{
    Game::Game sut(112);
    std::ignore = sut.joinPlayer(120);
    CHECK(sut.hasAllPlayers() == true);
}

TEST_CASE("Game cannot join the same player again")
{
    const auto player { 10 };
    Game::Game sut(player);
    CHECK_FALSE(sut.joinPlayer(player));
}

TEST_CASE("Game cannot join more than two players")
{
    Game::Game sut(1);
    std::ignore = sut.joinPlayer(2);
    CHECK_FALSE(sut.joinPlayer(4));
}



