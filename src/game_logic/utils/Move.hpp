#ifndef MOVE_HPP_
#define MOVE_HPP_
namespace game
{
template <class, class>
class AbstractPawn;

template <class CellT, class PawnT>
struct Move
{
    CellT *from = nullptr;
    CellT *target = nullptr;
    PawnT *pawn = nullptr;

    bool operator==(const Move &move) const
    {
        bool ret = true;
        if (move.from != from)
            ret = from != nullptr && move.from != nullptr && *move.from == *from;

        if (ret && move.target != target)
            ret = target != nullptr && move.target != nullptr && *move.target == *target;

        if (ret && move.pawn != pawn)
            ret = pawn != nullptr && move.pawn != nullptr && *move.target == *target;

        return ret;
    }
};

} // namespace game

#endif