#ifndef KILLTEAM_SRC_GAME_GAMESTATE
#define KILLTEAM_SRC_GAME_GAMESTATE

#include <optional>
#include <utility>

namespace Game
{
class Game
{
std::pair<std::optional<unsigned int>, std::optional<unsigned int>> players_;

public:
Game();

[[nodiscard]] bool joinPlayer(unsigned int player) noexcept;

[[nodiscard]] bool hasAllPlayers() const noexcept;
};
}

#endif
