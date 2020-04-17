#ifndef MOVE_HPP_
#define MOVE_HPP_
namespace game
{
template <class, class>
class AbstractPawn;

template <class CellT, class PawnT>
struct Move
{
    CellT *from;
    CellT *target;
    PawnT *pawn;
};

} // namespace game

#endif