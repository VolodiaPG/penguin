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

using board_line_t = std::array<BoardCell *, BOARD_SIZE>;
using board_matrix_t = std::array<board_line_t, BOARD_SIZE>;

class Board : public AbstractBoard
{
protected:
    /**
     * @brief Array of the cell const pointers to  variable element indexed in boardValues
     * 
     */
    board_matrix_t boardValues;

    /**
     * @brief keep track of the total amout of moves already accomplished
     * 
     */
    int totalMoves = 0;

    /**
    * @brief Check a line (col or row) for a win
    * 
    * @param line array: col or row or diag
    * @return int the player who won, 0 if nobody has won at the call  
    */
    int checkForWin(const board_line_t &line) const;

    /**
     * @brief Check if the pos is allowed to move to
     * 
     * @param pos the requested position
     * @return true if correct
     * @return false otherwise
     */
    bool checkForCorrectness(const Position &pos) const;

public:
    /**
     * @brief Construct a new Board object
     * 
     */
    Board();

    /**
     * @brief Destroy the Board object
     * 
     */
    ~Board();

    //inherited from AbstractBoard
    /**
     * @brief Performs a particular move
     * 
     * @param player the player who moves
     * @param pos the destination position
     */
    bool performMove(int player, AbstractBoardCell *cell) override;

    int checkStatus() const override;

    /**
     * @brief Get a list of empty cells, ie player not passed yet
     * 
     * @return the list of empty cells
     */
    std::vector<AbstractBoardCell *> getEmptyCells() const override;

    /**
     * @brief Get a list of all cells
     * 
     * @return the list of all cells 
     */
    std::vector<AbstractBoardCell *> getBoardCells() const override;

    size_t size() const override { return BOARD_SIZE; };

    int getTotalMoves() const { return totalMoves; };

    // Position begin();
};

} // namespace game

#endif