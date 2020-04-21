#include <array>
#include <assert.h>

#include "../AbstractBoard.hpp"
#include "BoardCell.hpp"
#include "Player.hpp"

#include "Board.hpp"

#include "dbg.h"

namespace game
{
namespace tic_tac_toe
{

Board::Board()
    : AbstractBoard(),
      player1(1),
      player2(2)
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

bool Board::performMove(Player *player, BoardCell *cell)
{
    bool ret = AbstractBoard<BoardCell, Player, Player>::performMove(player, cell);
    cell->setValue(player->getId());

    return ret;
}

const Move<BoardCell, Player> Board::revertMove()
{
    auto &move = AbstractBoard<BoardCell, Player, Player>::revertMove();
    move.target->setValue(0);
    // if (move.from)
    // {
    //     move.from->setValue(42);
    // }
    return move;
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

int Board::checkStatus()
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

    // dummy parameter, here there is no use for IT!
    return getAvailableCells(nullptr).size() > 0 ? IN_PROGRESS : DRAW;
}

std::vector<BoardCell *> Board::getAvailableCells(Player *)
{
    std::vector<BoardCell *> ret;

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

std::vector<BoardCell *> Board::getBoardCells()
{
    std::vector<BoardCell *> ret;

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

BoardCell *Board::getCell(int line, int col)
{
    return boardValues[line][col];
}

std::vector<Player *> Board::getPawnsOnBoard()
{
    std::vector<Player *> players;
    players.push_back(&player1);
    players.push_back(&player2);
    return players;
}

Player *Board::getPawnById(const unsigned int id)
{
    assert(id != 0);
    assert(id <= 2);
    switch (id)
    {
    case 1:
        return &player1;
    case 2:
        return &player2;
    default:
        return nullptr;
    }
}

AbstractBoard<BoardCell, Player, Player> *Board::clone() const
{
    Board *nb = new Board();
    for (size_t ii = 0; ii < boardValues.size(); ++ii)
    {
        for (size_t jj = 0; jj < boardValues[0].size(); ++jj)
        {
            BoardCell *cell = boardValues[ii][jj];
            nb->boardValues[ii][jj] = new BoardCell(*cell);
            dbg(cell->getValue());
            dbg(nb->boardValues[ii][jj]->getValue());
        }
    }

    const BoardCell *cell;
    if ((cell = player1.getCurrentCell()) != nullptr)
    {
        const Position &pos = cell->getPosition();
        nb->player1.setCurrentCell(nb->getCell(pos.x, pos.y));
    }
    if ((cell = player2.getCurrentCell()) != nullptr)
    {
        const Position &pos = cell->getPosition();
        nb->player2.setCurrentCell(nb->getCell(pos.x, pos.y));
    }
    return nb;
}

} // namespace tic_tac_toe
} // namespace game