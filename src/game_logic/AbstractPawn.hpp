#ifndef ABSTRACT_PAWN_HPP_
#define ABSTRACT_PAWN_HPP_

namespace game
{

template <class, class>
class AbstractPlayer;

namespace tic_tac_toe
{
class Player;
class BoardCell;
} // namespace tic_tac_toe
namespace penguin
{
class PenguinPawn;
class BoardCell;
} // namespace penguin

template <class PlayerT, class CellT>
class AbstractPawn
{

private:
    unsigned int _id;
    CellT *_current_cell = nullptr;
    PlayerT *_owner;

    // template <class, class>
    // friend class AbstractPlayer;

    friend class AbstractPlayer<tic_tac_toe::BoardCell, tic_tac_toe::Player>;
    friend class AbstractPlayer<penguin::BoardCell, penguin::PenguinPawn>;

public:
    explicit AbstractPawn(unsigned int id, PlayerT *owner);

    PlayerT *getOwner() const { return _owner; };

    /**
     * @brief Get pawn's id
     * 
     * @return constexpr unsigned int the id
     */
    unsigned int getId() const { return _id; };

    /**
     * @brief Queue the move done at the top of the stack
     * 
     * @param move the move to stack
     */
    void makeMove(CellT *cell);

    CellT *getCurrentCell() const;
};

} // namespace game

#endif