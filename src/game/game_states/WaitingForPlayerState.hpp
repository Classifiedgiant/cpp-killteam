#ifndef KILLTEAM_SRC_GAME_GAME_STATE_WAITINGFORPLAYER_H
#define KILLTEAM_SRC_GAME_GAME_STATE_WAITINGFORPLAYER_H

#include <concepts>
#include <random>
#include <utility>

#include "waiting_for_player.pb.h"

#include "StateConcepts.hpp"

namespace GameState
{
class WaitingForPlayerState
{

public:
static GameStates::WaitingForPlayer CreateStateCommand() noexcept {
    return GameStates::WaitingForPlayer();
}

};
}
#endif