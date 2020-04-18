#include <assert.h>

#include "tic_tac_toe/BoardCell.hpp"
#include "tic_tac_toe/Player.hpp"
#include "penguin/BoardCell.hpp"
#include "penguin/HumanPlayer.hpp"
#include "penguin/PenguinPawn.hpp"

#include "History.hpp"

namespace game
{

template <class CellT, class PawnT>
History<CellT, PawnT>::History()
{
}

template <class CellT, class PawnT>
void History<CellT, PawnT>::enqueue(const Move<CellT, PawnT>& move)
{
    _stack.push(move);
}

template <class CellT, class PawnT>
const Move<CellT, PawnT> History<CellT, PawnT>::dequeue()
{
    assert("No elements in the stack" && size() > 0);
    const Move<CellT, PawnT> move = _stack.top();
    _stack.pop();
    return move;
}

template <class CellT, class PawnT>
const Move<CellT, PawnT> &History<CellT, PawnT>::top() const
{
    assert("No elements in the stack" && size() > 0);
    return _stack.top();
}

template <class CellT, class PawnT>
size_t History<CellT, PawnT>::size() const
{
    return _stack.size();
}

template class History<tic_tac_toe::BoardCell, tic_tac_toe::Player>;
template class History<penguin::BoardCell, penguin::PenguinPawn>;

} // namespace game
