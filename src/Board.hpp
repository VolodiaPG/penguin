#ifndef BOARD_HPP_
#define BOARD_HPP_

#define BOARD_SIZE 3

#include <iterator>
#include <array>

#include "AbstractBoard.hpp"

namespace mcts
{

using boardLine = std::array<int, BOARD_SIZE>;
using boardMatrix = std::array<boardLine, BOARD_SIZE>;

class Board : AbstractBoard
{
protected:
    boardMatrix boardValues = boardMatrix();
    int totalMoves = 0;

    /**
 * @brief Check a line (col or row) for a win
 * 
 * @param line array: col or row or diag
 * @return int the player who won, 0 if nobody has won at the call
 */
    int checkForWin(boardLine &line);

public:
    Board();
    void performMove(int player, Position pos);
    game_status checkStatus();
    std::unique_ptr<std::list<Position>> getEmptyPositions();
};
} // namespace mcts

#endif