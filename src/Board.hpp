#ifndef BOARD_HPP_
#define BOARD_HPP_

#define BOARD_SIZE 3

#include <iterator>
#include <array>

#include "AbstractBoard.hpp"

namespace mcts
{

/**
 * @brief Describe possibles states of the game
 * 
 */
typedef enum
{
    /**
     * @brief Game in progress
     * 
     */
    IN_PROGRESS = 0,
    /**
     * @brief Draw
     * 
     */
    DRAW,
    /**
     * @brief P1's turn
     * 
     */
    P1,
    /**
     * @brief P2's turn
     * 
     */
    P2
} GameStatus;

using boardLine = std::array<int, BOARD_SIZE>;
using boardMatrix = std::array<boardLine, BOARD_SIZE>;

class Board : AbstractBoard<GameStatus>
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
    /**
    * @brief Construct a new Board object
    * 
    */
    Board();

    //inherited from AbstractBoard
    void performMove(int player, Position pos) override;
    GameStatus checkStatus() override;
    std::shared_ptr<std::list<Position>> getEmptyPositions() override;
};

} // namespace mcts

#endif