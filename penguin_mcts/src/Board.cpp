#include "Board.hpp"
#include <array>

namespace game
{
Board::Board()
    : AbstractBoard()
{
    for (int ii = 0; ii < BOARD_SIZE; ++ii)
    {
        for (int jj = 0; jj < BOARD_SIZE; ++jj)
        {
            Position pos;
            pos.x = ii;
            pos.y = jj;

            boardValues[ii][jj] = new BoardCell(pos);
        }
    }
}

Board::~Board()
{
    for (int ii = 0; ii < BOARD_SIZE; ++ii)
    {
        for (int jj = 0; jj < BOARD_SIZE; ++jj)
        {
            delete boardValues[ii][jj];
        }
    }
}

bool Board::checkForCorrectness(const Position &pos) const
{
    return !boardValues[pos.x][pos.y]->isClaimed();
}

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

int Board::checkForWin(const board_line_t &line) const
{
    int previous = line[0]->getValue();
    // check if this is the same value all along the line
    for (const BoardCell *cell : line)
    {
        int value = cell->getValue();
        if (value != previous)
        {
            // line is not full of the same values
            return 0;
        }
    }

    // it has been the same value all along from the beginning,
    // return the id of the line's owner
    return previous;
}

int Board::checkStatus() const
{
    // declare the two diags
    board_line_t diag1; //= std::array<BoardCell, BOARD_SIZE>();
    board_line_t diag2; //= boardLine();

    int win = 0;

    for (int ii = 0; ii < BOARD_SIZE; ++ii)
    {
        const board_line_t &row = boardValues[ii];
        board_line_t col; // = boardLine();

        for (int jj = 0; jj < BOARD_SIZE; ++jj)
        {
            col[jj] = boardValues[jj][ii];
        }

        // row
        if ((win = checkForWin(row)))
        {
            return win;
        }

        // col
        if ((win = checkForWin(col)))
        {
            return win;
        }

        // filling the 2 big diagonals
        diag1[ii] = boardValues[ii][ii];
        diag2[ii] = boardValues[ii][BOARD_SIZE - 1 - ii];
    }

    // diag1
    if ((win = checkForWin(diag1)))
    {
        return win;
    }

    // diag2
    if ((win = checkForWin(diag2)))
    {
        return win;
    }

    return getAvailableCells().size() > 0 ? IN_PROGRESS : DRAW;
}

std::vector<AbstractBoardCell *> Board::getAvailableCells() const
{
    std::vector<AbstractBoardCell *> ret;

    for (size_t ii = 0; ii < boardValues.size(); ++ii)
    {
        for (size_t jj = 0; jj < boardValues[0].size(); ++jj)
        {
            BoardCell *cell = boardValues[ii][jj];
            if (!cell->isClaimed())
            {
                ret.push_back(cell);
            }
        }
    }

    // return a copy
    return ret;
}

std::vector<AbstractBoardCell *> Board::getBoardCells() const
{
    std::vector<AbstractBoardCell *> ret;

    for (const board_line_t &line : boardValues)
    {
        for (BoardCell *cell : line)
        {
            ret.push_back(cell);
        }
    }

    // copy return
    return ret;
}

AbstractBoardCell *Board::getCell(int line, int col) const
{
    return boardValues[line][col];
}

} // namespace game