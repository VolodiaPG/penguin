#ifndef ABSTRACT_BOARD_HPP_
#define ABSTRACT_BOARD_HPP_

#include <vector>

#include "History.hpp"

namespace game
{

/**
 * @brief Describe the basics of a Board
 * 
 * @tparam CellT The type of the cell composing the board
 * @tparam PlayerT The type of player linked to the board itself (the player that moves directly on the board)*
 * @tparam PawnT the type of the pawn playing on the bord
 */
template <class CellT, class PlayerT, class PawnT>
class AbstractBoard
{
private:
    History<CellT, PawnT> _history;

public:
    virtual ~AbstractBoard(){};

    /**
    * @brief perform a movement on the board
    * 
    * @param player the player that realizes the movement
    * @param cell the cell targeted
    * 
    * @return true if the move is allowed, false otherwise
    */
    virtual bool performMove(PawnT *pawn, CellT *cell);

    virtual const Move<CellT, PawnT> revertMove();

    /**
     * @brief Status of the game
     * 
     * @return game_status 
     */
    virtual int checkStatus() = 0;

    /**
     * @brief Get the Empty AbstractBoardCell Left
     * 
     * @return std::list<CellT> 
     */
    virtual std::vector<CellT *> getAvailableCells(PawnT *pawn) = 0;

    /**
     * @brief Get all of the AbstractBoardCell
     * 
     * @return std::list<AbstractBoardCell> 
     */
    virtual std::vector<CellT *> getBoardCells() = 0;

    /**
     * @brief Get the Cell
     * 
     * @param line line coord
     * @param col col coord
     * @return the targeted cell
     */
    virtual CellT *getCell(int line, int col) = 0;

    /**
     * @brief Get the Players that are presently palying on the board
     * 
     * @return std::vector<PlayerT *> a vector of the players
     */
    virtual std::vector<PawnT *> getPawnsOnBoard() = 0;

    /**
     * @brief Get a player by it's id
     * 
     * @param id the id of the player wanted
     * @return PawnT* the pawn wanted, or null if it doesn't exists
     */
    virtual PawnT *getPawnById(const unsigned int id) = 0;

    /**
     * @brief Gets the player corresponding to a certain id
     * 
     * @param id the id of the player
     * @return PlayerT* the player wanted
     */
    virtual PlayerT *getPlayerById(const unsigned int id) = 0;

    virtual size_t size() const = 0;
};

} // namespace game

#endif
