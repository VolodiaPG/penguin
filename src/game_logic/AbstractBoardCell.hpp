#ifndef ABSTRACT_BOARD_CELL_HPP_
#define ABSTRACT_BOARD_CELL_HPP_

#include "utils/Iequals.hpp"

namespace game
{
class AbstractBoardCell : public IEquals_Base<AbstractBoardCell>
{
public:
    explicit AbstractBoardCell() = default;

    explicit AbstractBoardCell(const AbstractBoardCell&) = default;

    virtual ~AbstractBoardCell(){};

    bool equals_to(const AbstractBoardCell& cell) const override;
};
} // namespace game

#endif
