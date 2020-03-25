#include "AbstractGame.hpp"

namespace game
{

template<class PlayerT, class CellT>
AbstractGame<PlayerT, CellT>::AbstractGame(AbstractBoard<PlayerT, CellT> *board)
    : board(board)
{
}

// Compile specifically to prevent undefined errors on that specific type of combination

template class AbstractGame<tic_tac_toe::Player, tic_tac_toe::BoardCell>;

} // namespace game