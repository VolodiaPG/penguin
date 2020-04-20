#ifndef ABSTRACT_PAWN_HPP_
#define ABSTRACT_PAWN_HPP_

namespace game
{

template <class PlayerT, class CellT>
class AbstractPawn
{

private:
    unsigned int _id;
    CellT *_current_cell = nullptr;
    PlayerT *_owner;

public:
    explicit AbstractPawn(unsigned int id, PlayerT& owner);

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
    void setCurrentCell(CellT *cell);

    CellT *getCurrentCell() const;

    bool operator==(const AbstractPawn& pawn) const;
};

} // namespace game

#endif