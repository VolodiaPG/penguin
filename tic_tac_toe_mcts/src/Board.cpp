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

    const Position &pos = cell->getPosition();

    // if (!checkForCorrectness(pos))
    // {
    //     return false;
    // }
    // TODO bug with these lines

    ++totalMoves;
    cell->setValue(player);
    // boardValues[pos.x][pos.y]->setValue(player);

    return true;
}

void Board::revertMove(AbstractBoardCell *absCell)
{
    BoardCell *cell;
    if ((cell = dynamic_cast<BoardCell *>(absCell)))
    {
        --totalMoves;
        const Position &pos = cell->getPosition();
        boardValues[pos.x][pos.y]->setValue(0);
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

    // it has been the same value all along from the beginning
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

    return getEmptyCells().size() > 0 ? IN_PROGRESS : DRAW;
}

std::vector<AbstractBoardCell *> Board::getEmptyCells() const
{
    std::vector<AbstractBoardCell *> ret;

    for (int ii = 0; ii < (int)boardValues.size(); ++ii)
    {
        for (int jj = 0; jj < (int)boardValues[0].size(); ++jj)
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