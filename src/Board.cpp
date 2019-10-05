#include "Board.hpp"

namespace mcts
{
Board::Board()
{
}

void Board::performMove(int player, Position pos)
{
    ++totalMoves;
    boardValues[pos.x][pos.y] = player;
}

int Board::checkForWin(boardLine &line)
{
    int previous = IN_PROGRESS;
    for (int &value : line)
    {
        if (value != previous)
        {
            //line is not full of the same values
            return 0;
        }
    }

    //it has been the same value all along from the beginning
    return previous;
}

game_status Board::checkStatus()
{
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

        //row
        win = checkForWin(row);
        if (win)
        {
            return (game_status)win;
        }

        //col
        win = checkForWin(col);
        if (win)
        {
            return (game_status)win;
        }

        //2 big diagonals
        diag1[ii] = boardValues[ii][ii];
        diag2[ii] = boardValues[ii][BOARD_SIZE - 1 - ii];
    }

    //diag1
    win = checkForWin(diag1);
    if (win)
    {
        return (game_status)win;
    }

    //diag2
    win = checkForWin(diag2);
    if (win)
    {
        return (game_status)win;
    }

    return getEmptyPositions()->size() > 0 ? IN_PROGRESS : DRAW;
}

std::unique_ptr<std::list<Position>> Board::getEmptyPositions()
{
}

} // namespace mcts