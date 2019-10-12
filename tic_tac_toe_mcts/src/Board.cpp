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
            boardValues[ii][jj] = 0;
        }
    }
}

void Board::performMove(int player, Position pos)
{
    ++totalMoves;
    boardValues[pos.x][pos.y] = player;
}

int Board::checkForWin(boardLine &line)
{
    int previous = line[0].getValue();

    // check if this is the same value all along the line
    for (BoardCell &cell : line)
    {
        int value = cell.getValue();
        if (value != previous)
        {
            // line is not full of the same values
            return 0;
        }
    }

    // it has been the same value all along from the beginning
    return previous;
}

GameStatus Board::checkStatus()
{
    // declare the two diags
    boardLine diag1; //= std::array<BoardCell, BOARD_SIZE>();
    boardLine diag2; //= boardLine();

    int win = 0;

    for (int ii = 0; ii < BOARD_SIZE; ++ii)
    {
        boardLine row = boardValues[ii];
        boardLine col; // = boardLine();

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

    return getEmptyPositions()->size() > 0 ? IN_PROGRESS : DRAW;
}

std::shared_ptr<std::list<Position>> Board::getEmptyPositions()
{
    std::shared_ptr<std::list<Position>> ret = std::make_shared<std::list<Position>>();

    for (int ii = 0; ii < (int)boardValues.size(); ++ii)
    {
        for (int jj = 0; jj < (int)boardValues[ii].size(); ++jj)
        {
            BoardCell cell = boardValues[ii][jj];
            if (cell.isClaimed())
            {
                ret->push_back(*cell.position);
            }
        }
    }

    return ret;
}

} // namespace game