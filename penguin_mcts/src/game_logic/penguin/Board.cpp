#include "Board.hpp"
#include <array>

namespace game
{
namespace penguin
{
Board::Board(size_t dimension)
    : AbstractBoard(),
      _dimension(dimension)
{
    for (int ii = -_dimension / 2; ii < (int)_dimension; ++ii) // the board center is @(0,0) and so the min and max on a line are @ -dimension/2 and +dimension /2
    {
        for (int jj = -_dimension / 2; jj < (int)_dimension; ++jj)
        {
            const Position pos = Position{ii, jj};
            
            boardValues.insert_or_assign(pos, new BoardCell(pos));
        }
    }
}

Board::~Board()
{
    for (const auto &entry : boardValues)
    {
        delete entry.second;
    }
}

// bool Board::checkForCorrectness(const Position &pos) const
// {
//     return !boardValues[pos.x][pos.y]->isClaimed();
// }

bool Board::performMove(int player, AbstractBoardCell *absCell)
{
    BoardCell *cell = nullptr;
    if (!(cell = dynamic_cast<BoardCell *>(absCell)))
    {
        return false;
    }

    cell->setValue(player);

    return true;
}

void Board::revertMove(AbstractBoardCell *absCell)
{
    BoardCell *cell;
    if ((cell = dynamic_cast<BoardCell *>(absCell)))
    {
        cell->setValue(0);
    }
}

// int Board::checkForWin(const board_line_t &line) const
// {
//     int previous = line[0]->getValue();
//     // check if this is the same value all along the line
//     for (const BoardCell *cell : line)
//     {
//         int value = cell->getValue();
//         if (value != previous)
//         {
//             // line is not full of the same values
//             return 0;
//         }
//     }

//     // it has been the same value all along from the beginning,
//     // return the id of the line's owner
//     return previous;
// }

int Board::checkStatus() const
{
    return getAvailableCells().size() > 0 ? IN_PROGRESS : DRAW;
}

std::vector<AbstractBoardCell *> Board::getAvailableCells() const
{
    std::vector<AbstractBoardCell *> ret;

    for (const auto &entry : boardValues)
    {
        BoardCell *cell = entry.second;
        if (!cell->isClaimed())
        {
            ret.push_back(cell);
        }
    }

    // return a copy
    return ret;
}

std::vector<AbstractBoardCell *> Board::getBoardCells() const
{
    std::vector<AbstractBoardCell *> ret;

    for (const auto &entry : boardValues)
    {
        ret.push_back(entry.second);
    }

    // copy return
    return ret;
}

AbstractBoardCell *Board::getCell(int line, int col) const
{
    return boardValues.at(Position{line, col});
}
} // namespace penguin
} // namespace game