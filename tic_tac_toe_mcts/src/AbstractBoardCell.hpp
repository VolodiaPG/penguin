#ifndef ABSTRACT_BOARD_CELL_HPP_
#define ABSTRACT_BOARD_CELL_HPP_

#include <iostream>
#include <ostream>

namespace game
{
class AbstractBoardCell
{
public:
    virtual std::string to_string() const;
    virtual ~AbstractBoardCell(){};
    virtual bool equals(AbstractBoardCell* cell) const = 0;
};

} // namespace game

#endif
