#ifndef KILLTEAM_SRC_GAME_GAMESTATE
#define KILLTEAM_SRC_GAME_GAMESTATE

#include <utility>

namespace Game
{
class Game
{
std::pair<unsigned int, unsigned int> players_;

public:
    explicit Game(unsigned int player);

    [[nodiscard]] bool joinPlayer(unsigned int player) noexcept;

    [[nodiscard]] bool hasAllPlayers() const noexcept;
};
}

#endif
