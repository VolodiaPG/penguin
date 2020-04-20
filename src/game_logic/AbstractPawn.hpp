#ifndef ABSTRACT_PAWN_HPP_
#define ABSTRACT_PAWN_HPP_

#include "utils/Iequals.hpp"

namespace game
{

template <class PlayerT, class CellT>
class AbstractPawn : public IEquals_Base<AbstractPawn<PlayerT, CellT>>
{

private:
    unsigned int _id;
    CellT *_current_cell = nullptr;
    PlayerT *_owner;

protected:
    bool equals_to(const AbstractPawn<PlayerT, CellT> &pawn) const override;

public:
    explicit AbstractPawn(unsigned int id, PlayerT &owner);

    explicit AbstractPawn(const AbstractPawn<PlayerT, CellT>&) = delete;

    virtual ~AbstractPawn(){};

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
};

} // namespace game

#endif