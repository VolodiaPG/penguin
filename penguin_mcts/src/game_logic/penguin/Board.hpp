#ifndef PENGUIN_BOARD_HPP_
#define PENGUIN_BOARD_HPP_

#include <iterator>
#include <array>
#include <unordered_map>

#include "../../log.hpp"

#include "../AbstractBoard.hpp"
#include "BoardCell.hpp"
#include "PenguinPlayer.hpp"

// TODO Command pattern pour le reverse

namespace game
{
namespace penguin
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
    DRAW = -1,
    /**
     * @brief P1's won
     * 
     */
    P1_WON = 1,
    /**
     * @brief P2's won
     * 
     */
    P2_WON = 2
} GameStatus;

// Here we'll be using an unodered_map in order to achieve an average of O(1)
using penguin_board_map_t = std::unordered_map<const Position, BoardCell*, position_hash_function>;

/**
 * @brief Describes the hexagonal board of the game, based on an axial coordinate system
 * 
 */
class Board : public AbstractBoard
{
private:
    size_t _dimension;

protected:
    /**
     * @brief Array of the cell const pointers to  variable element indexed in boardValues
     * 
     */
    penguin_board_map_t boardValues;

    /**
    * @brief Check a line (col or row) for a win
    * 
    * @param line array: col or row or diag
    * @return int the player who won, 0 if nobody has won at the call  
    */
    // int checkForWin(const board_line_t &line) const;

    /**
     * @brief Checks wether or not the move is allowed to be performed
     * 
     * @param start the starting position
     * @param destination the destination position
     * @return true the move can be performed
     * @return false the move is illegal
     */
    bool checkForCorrectness(const Position &start, const Position &destination) const;

public:
    /**
     * @brief Construct a new Board object
     * 
     * @param dimension the board dimensions
     */
    Board(size_t dimension);

    /**
     * @brief Destroy the Board object
     * 
     */
    ~Board();

    // TODO create an action wrapper to wrap both the cell and player informations (in our case because there are multiples penguins)
    /**
     * @brief Performs a particular move
     * 
     * @param player the player who moves
     * @param pos the destination position
     */
    bool performMove(AbstractPlayer& player, AbstractBoardCell *cell) override;

    void revertMove(AbstractPlayer& player, AbstractBoardCell *cell) override;

    /**
     * @brief Chek wether or not the game is finished.
     * 
     * @return If not finised it will return 0, otherwise the id of the winning player or -1 if a draw
     */
    int checkStatus() const override;

    /**
     * @brief Get a list of empty cells, ie player not passed yet
     * 
     * @return the list of empty cells
     */
    std::vector<AbstractBoardCell *> getAvailableCells() const override;

    /**
     * @brief Get a list of all cells
     * 
     * @return the list of all cells 
     */
    std::vector<AbstractBoardCell *> getBoardCells() const override;

    size_t size() const override { return _dimension; };

    AbstractBoardCell *getCell(int line, int col) const override;

    // Position begin();
};

} // namespace penguin
} // namespace game

#endif