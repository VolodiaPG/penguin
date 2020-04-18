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

        bool ret = from == move.from ||
                   (from != nullptr && move.from != nullptr && *move.from == *from);
        ret = ret &&
              (target == move.target || (target != nullptr && move.target != nullptr && *move.target == *target));
        ret = ret &&
              (pawn == move.pawn || (pawn != nullptr && move.pawn != nullptr && *move.target == *target));

        return ret;
    }
};

} // namespace game

#endif