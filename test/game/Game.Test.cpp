#include <catch2/catch_test_macros.hpp>

#include <tuple>

#include <Game.hpp>


TEST_CASE("Game does not have all players without a join")
{
    Game::Game sut;
    CHECK_FALSE(sut.hasAllPlayers());

    CHECK(sut.joinPlayer(120) == true);
    CHECK_FALSE(sut.hasAllPlayers());
}

TEST_CASE("Game is ready when all Players join")
{
    Game::Game sut;
    std::ignore = sut.joinPlayer(110);
    std::ignore = sut.joinPlayer(120);
    CHECK(sut.hasAllPlayers() == true);
}

TEST_CASE("Game cannot join the same player again")
{
    const auto player { 10 };
    Game::Game sut;
    CHECK(sut.joinPlayer(player) == true);
    CHECK_FALSE(sut.joinPlayer(player));
}

TEST_CASE("Game cannot join more than two players")
{
    Game::Game sut;
    std::ignore = sut.joinPlayer(1);
    std::ignore = sut.joinPlayer(2);
    CHECK_FALSE(sut.joinPlayer(4));
}



