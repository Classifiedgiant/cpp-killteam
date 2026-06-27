#ifndef KILLTEAM_SRC_GAME_GAME_STATE_STARTGAMESTATE_H
#define KILLTEAM_SRC_GAME_GAME_STATE_STARTGAMESTATE_H

#include <concepts>
#include <random>
#include <utility>

#include "start_game.pb.h"

#include "StateConcepts.hpp"

namespace GameState
{
class StartGameState
{

public:
static GameStates::StartGame CreateStateCommand() noexcept {

    // create random generator for which player starts
    std::random_device rd{};
    std::mt19937 gen{rd()};

    std::bernoulli_distribution dist(0.5);

    GameStates::StartGame msg{};

    msg.mutable_player1army()->set_name("Player 1 Army");
    msg.mutable_player2army()->set_name("Player 2 Army");

    return msg;
}

};
}
#endif