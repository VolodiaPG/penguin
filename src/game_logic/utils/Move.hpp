#ifndef MOVE_HPP_
#define MOVE_HPP_
namespace game
{
class AbstractBoardCell;
class AbstractPlayer;
template <class, class>
class AbstractPawn;

struct Move
{
    AbstractBoardCell *from;
    AbstractBoardCell *target;
    AbstractPawn<AbstractPlayer, AbstractBoardCell> *pawn;
};

} // namespace game

#endif