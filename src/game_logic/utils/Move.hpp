#ifndef MOVE_HPP_
#define MOVE_HPP_

#include "Iequals.hpp"

namespace game
{

template <class CellT, class PawnT>
struct Move : IEquals_Base<Move<CellT, PawnT>>
{
    CellT *from = nullptr;
    CellT *target = nullptr;
    PawnT *pawn = nullptr;

protected:
    bool equals_to(const Move &move) const override
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
};

} // namespace game

#endif