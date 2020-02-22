#include "Board.hpp"

namespace game
{
namespace penguin
{
Board::Board(size_t dimension)
    : AbstractBoard(),
      _dimension(dimension)
{
    //TODO découpler la génération et le parcours de la structure elle même (pattern visiteur)
    int offset = 0;
    for (int ii = 0; ii < (int)_dimension; ++ii) // ii for the rows
    {
        for (int jj = offset; jj < (int)_dimension + offset; ++jj) // jj for the cols
        {

            // cols in x and rows in y
            const Position pos = Position{jj, ii};

            boardValues.insert_or_assign(pos,
                                         new BoardCell(pos,
                                                       rand() % 3 + 1 // random number of fish between 1 and 3 (included)
                                                       ));
        }

        if (ii % 2 == 1)
        {
            --offset;
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

// TODO maybe find a better solution to cast ?
bool Board::performMove(AbstractPlayer &abs_player, AbstractBoardCell *absCell)
{
    PenguinPlayer& player = static_cast<PenguinPlayer&>(abs_player);
 
    //TODO perform move logic
    BoardCell *cell = nullptr;
    if (!(cell = dynamic_cast<BoardCell *>(absCell)))
    {
        return false;
    }

    // cell->setGone(true);

    return true;
}

void Board::revertMove(AbstractBoardCell *absCell)
{
    BoardCell *cell;
    if ((cell = dynamic_cast<BoardCell *>(absCell)))
    {
        cell->setGone(false);
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
        if (!cell->isGone())
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
    const Position pos = Position{line, col};
    return boardValues.at(pos);
}
} // namespace penguin
} // namespace game