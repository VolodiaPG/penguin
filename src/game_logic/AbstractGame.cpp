#include "AbstractGame.hpp"

namespace game
{

template <class CellT, class PlayerT, class PawnT>
AbstractGame<CellT, PlayerT, PawnT>::AbstractGame(AbstractBoard<CellT, PlayerT, PawnT> *board)
    : board(board)
{
}

// Compile specifically to prevent undefined errors on that specific type of combination

template class AbstractGame<tic_tac_toe::BoardCell, tic_tac_toe::Player, tic_tac_toe::Player>;
template class AbstractGame<penguin::BoardCell, penguin::HumanPlayer, penguin::PenguinPawn>;

} // namespace game