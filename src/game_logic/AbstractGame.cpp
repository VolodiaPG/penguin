#include "tic_tac_toe/Player.hpp"
#include "tic_tac_toe/BoardCell.hpp"

#include "penguin/HumanPlayer.hpp"
#include "penguin/PenguinPawn.hpp"
#include "penguin/BoardCell.hpp"

#include "AbstractGame.hpp"

namespace game
{

template <class CellT, class PlayerT, class PawnT>
AbstractGame<CellT, PlayerT, PawnT>::AbstractGame(AbstractBoard<CellT, PlayerT, PawnT> *board)
    : board(board)
{
}

template class AbstractGame<tic_tac_toe::BoardCell, tic_tac_toe::Player, tic_tac_toe::Player>;
template class AbstractGame<penguin::BoardCell, penguin::HumanPlayer, penguin::PenguinPawn>;

} // namespace game