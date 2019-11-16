#include "Board.hpp"
#include <array>

namespace game
{
Board::Board()
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

void Board::performMove(int player, const Position &pos)
{
    ++totalMoves;
    boardValues[pos.x][pos.y]->setValue(player);
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

    // it has been the same value all along from the beginning
    return previous;
}

GameStatus Board::checkStatus() const
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
            col[ii] = boardValues[jj][ii];
        }

        // row
        win = checkForWin(row);
        if (win)
        {
            return (GameStatus)win;
        }

        // col
        win = checkForWin(col);
        if (win)
        {
            return (GameStatus)win;
        }

        // filling the 2 big diagonals
        diag1[ii] = boardValues[ii][ii];
        diag2[ii] = boardValues[ii][BOARD_SIZE - 1 - ii];
    }

    // diag1
    win = checkForWin(diag1);
    if (win)
    {
        return (GameStatus)win;
    }

    // diag2
    win = checkForWin(diag2);
    if (win)
    {
        return (GameStatus)win;
    }

    return getEmptyPositions().size() > 0 ? IN_PROGRESS : DRAW;
}

std::list<Position> Board::getEmptyPositions() const
{
    std::list<Position> ret;

    for (int ii = 0; ii < (int)boardValues.size(); ++ii)
    {
        for (int jj = 0; jj < (int)boardValues[0].size(); ++jj)
        {
            const BoardCell *cell = boardValues[ii][jj];
            if (!cell->isClaimed())
            {
                ret.push_back(cell->getPosition());
            }
        }
    }

    // return a copy
    return ret;
}

} // namespace game