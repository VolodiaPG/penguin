#include "AbstractGame.hpp"

namespace game
{

template<class PlayerT, class CellT>
AbstractGame<PlayerT, CellT>::AbstractGame(AbstractBoard<PlayerT, CellT> *board)
    : board(board)
{
}

} // namespace game