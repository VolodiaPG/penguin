#ifndef ABSTRACT_BOARD_HPP_
#define ABSTRACT_BOARD_HPP_

#include <vector>
#include <memory>

#include "AbstractBoardCell.hpp"
#include "AbstractPlayer.hpp"

namespace game
{

class AbstractPlayer;

/**
 * @brief Describe the basics of a Board
 * 
 * @tparam PlayerT The type of player linked to the board itself (the player that moves directly on the board)
 * @tparam CellT The type of the cell composing the board
 */
template<class PlayerT = AbstractPlayer, class CellT = AbstractBoardCell>
class AbstractBoard
{
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
    virtual bool performMove(const int player_id, CellT *cell) = 0;

    virtual void revertMove(const int player_id, CellT *cell) = 0;

    /**
     * @brief Status of the game
     * 
     * @return game_status 
     */
    virtual int checkStatus() const = 0;

    /**
     * @brief Get the Empty AbstractBoardCell Left
     * 
     * @return std::list<CellT> 
     */
    virtual std::vector<CellT *> getAvailableCells(const int player_id) const = 0;

    /**
     * @brief Get all of the AbstractBoardCell
     * 
     * @return std::list<AbstractBoardCell> 
     */
    virtual std::vector<CellT *> getBoardCells() const = 0;

    /**
     * @brief Get the Cell
     * 
     * @param line line coord
     * @param col col coord
     * @return the targeted cell
     */
    virtual CellT *getCell(int line, int col) const = 0;

    /**
     * @brief Get the Players that are presently palying on the board
     * 
     * @return std::vector<PlayerT *> a vector of the players
     */
    virtual std::vector<PlayerT *> getPlayersOnBoard() = 0;

    /**
     * @brief Get a player by it's id
     * 
     * @param id the id of the player wanted
     * @return PlayerT* the player wanted, or null if it doesn't exists
     */
    virtual PlayerT * getPlayerById(const int id) = 0;

    virtual size_t size() const = 0;
};

} // namespace game

#endif
