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

bool Board::checkForCorrectness(const Position &start_axial, const Position &destination_axial) const
{
    const Position3D start = hex_axial_to_cube(start_axial);
    const Position3D destination = hex_axial_to_cube(destination_axial);

    // checking if the move is allowed <=> checking if the hex cell is on a direct line from one of the side of the start one
    // <=> in a cube coordinate system, it is the same as looking if one of the coordinate is the same
    return !boardValues.at(destination_axial)->isOwned() && (start.x == destination.x ||
                                                             start.y == destination.y ||
                                                             start.z == destination.z);
}

// TODO maybe find a better solution to cast ?
bool Board::performMove(AbstractPlayer &abs_player, AbstractBoardCell *abs_cell)
{
    PenguinPlayer &player = static_cast<PenguinPlayer &>(abs_player);
    BoardCell *cell = static_cast<BoardCell *>(abs_cell);

    bool isCorrect = checkForCorrectness(player.getStandingOn()->getPosition(), cell->getPosition());

    if (isCorrect)
    {
        BoardCell *previousCell = player.getStandingOn();
        previousCell->clearOwner(); // clear the owner and create a hole in the board
        previousCell->setGone(true);

        cell->setOwner(player);
        player.getOwner().addScore(cell->getFish());
        player.setStandingOn(cell);
    }

    return isCorrect;
}

void Board::revertMove(AbstractPlayer &abs_player, AbstractBoardCell *abs_cell)
{
    PenguinPlayer &player = static_cast<PenguinPlayer &>(abs_player);
    BoardCell *cell = static_cast<BoardCell *>(abs_cell);

    BoardCell *previousCell = player.getPreviousStandingOn();
    cell->clearOwner(); // clear the owner of the current cell

    previousCell->setOwner(player);                    // set the penguin as the owner of the previous cell
    player.getOwner().substractScore(cell->getFish()); // update the score
    player.setStandingOn(previousCell);
}

//TODO check for win
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