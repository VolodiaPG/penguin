#ifndef ABSTRACT_BOARD_CELL_HPP_
#define ABSTRACT_BOARD_CELL_HPP_

namespace game
{
class AbstractBoardCell
{
protected:
    virtual bool equals_to(const AbstractBoardCell &cell) const = 0;

public:
    explicit AbstractBoardCell() = default;

    explicit AbstractBoardCell(const AbstractBoardCell &) = default;

    virtual ~AbstractBoardCell(){};

    bool operator==(const AbstractBoardCell &cell) { return equals_to(cell); };
    bool operator!=(const AbstractBoardCell &cell) { return !equals_to(cell); };
};
} // namespace game

#endif
