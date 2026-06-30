#ifndef KILLTEAM_SRC_GAME_GAME_STATE_STARTGAMESTATE_H
#define KILLTEAM_SRC_GAME_GAME_STATE_STARTGAMESTATE_H

#include <utility>

#include "start_game.pb.h"

#include "StateConcepts.hpp"

namespace GameState
{
class StartGameState
{

public:
static GameStates::StartGame CreateStateCommand(uint32_t player1Id, uint32_t player2Id) noexcept
{
    GameStates::StartGame msg{};

    msg.set_gametype(GameStates::GameType::GAMETYPE_FREE_FOR_ALL);

    msg.set_player1(player1Id);
    msg.set_player2(player2Id);

    *msg.mutable_player1army() = CreatePlayer1Army();
    *msg.mutable_player2army() = CreatePlayer2Army();

    *msg.mutable_level() = CreateLevel();
    return msg;
}

private:
static GameStates::Army CreatePlayer1Army()
{
    GameStates::Army army{};
    army.set_name("Imperial");

    // all of these values are made up for the time being for testing
    auto op = army.add_operative();
    op->set_movememnt(4);
    op->set_actionpointlimit(3);
    op->set_groupactivation(1);
    op->set_defense(4);
    op->set_save(3);
    op->set_wounds(2);
    op->set_keywords(0, "Imperial");

    return army;
}

static GameStates::Army CreatePlayer2Army()
{
    GameStates::Army army{};
    army.set_name("Orks");

    // all of these values are made up for the time being for testing
    auto op = army.add_operative();
    op->set_movememnt(4);
    op->set_actionpointlimit(3);
    op->set_groupactivation(1);
    op->set_defense(5);
    op->set_save(3);
    op->set_wounds(4);
    op->set_keywords(0, "Orks");

    return army;
}

static GameStates::Level CreateLevel()
{
    GameStates::Level level{};
    level.set_resource("level_1.ods");

    return level;
}

};
}
#endif