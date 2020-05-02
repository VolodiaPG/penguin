#include "../tic_tac_toe/Player.hpp"
#include "../tic_tac_toe/BoardCell.hpp"

#include "../penguin/PenguinPawn.hpp"
#include "../penguin/BoardCell.hpp"

#include "Move.hpp"

namespace game
{

template <class CellT, class PawnT>
bool Move<CellT, PawnT>::equals_to(const Move &move) const
{
    bool ret = true;
    if (move.from != from)
        ret = from != nullptr && move.from != nullptr && *move.from == *from;

    if (ret && move.target != target)
        ret = target != nullptr && move.target != nullptr && *move.target == *target;

    if (ret && move.pawn != pawn)
        ret = pawn != nullptr && move.pawn != nullptr && *move.pawn == *pawn;

    return ret;
}

template struct Move<tic_tac_toe::BoardCell, tic_tac_toe::Player>;
template struct Move<penguin::BoardCell, penguin::PenguinPawn>;
} // namespace game
