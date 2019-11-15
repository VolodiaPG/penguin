#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <iterator>
#include <array>

#include "AbstractBoard.hpp"
#include "BoardCell.hpp"

namespace game
{

#define BOARD_SIZE 3

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
     * @brief P1's won
     * 
     */
    P1_WON,
    /**
     * @brief P2's won
     * 
     */
    P2_WON
} GameStatus;

using boardLine = std::array<BoardCell, BOARD_SIZE>;
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

    Position begin();
};

} // namespace game

#endif