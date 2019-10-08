#include "Board.hpp"

namespace mcts
{
Board::Board()
{
    for (int ii = 0; ii < (int)boardValues.size(); ++ii)
    {
        for (int jj = 0; jj < (int)boardValues[ii].size(); ++jj)
        {
            boardValues[ii][jj] = 0;
        }
    }
}

void Board::performMove(GameStatus player, Position pos)
{
    ++totalMoves;
    boardValues[pos.x][pos.y] = player;
}

int Board::checkForWin(boardLine &line)
{
    int previous = line[0];

    // check if this is the same value all along the line
    for (int &value : line)
    {
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
    boardLine diag1 = boardLine();
    boardLine diag2 = boardLine();

    int win = 0;

    for (int ii = 0; ii < BOARD_SIZE; ++ii)
    {
        boardLine row = boardValues[ii];
        boardLine col = boardLine();

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
            if (boardValues[ii][jj])
            {
               ret->push_back(Position(ii, jj));
            }
        }
    }

    return ret;
}

} // namespace mcts