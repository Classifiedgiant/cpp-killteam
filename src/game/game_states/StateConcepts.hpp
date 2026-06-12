
#ifndef KILLTEAM_SRC_GAME_GAME_STATE_STATECONCEPTS_H
#define KILLTEAM_SRC_GAME_GAME_STATE_STATECONCEPTS_H

// concept to enforce
template<typename T, typename... Args>
concept HasCreateStateCommand = requires(Args... args) {
    { T::CreateStateCommand(args...) };
};

#endif