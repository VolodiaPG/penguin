#include "AbstractGame.hpp"

namespace game
{

AbstractGame::AbstractGame(AbstractBoard *board)
    : board(board)
{
}

} // namespace game