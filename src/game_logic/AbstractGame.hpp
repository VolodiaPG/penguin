#ifndef ABSTRACT_GAME_HPP_
#define ABSTRACT_GAME_HPP_

#include "AbstractInterface.hpp"
#include "AbstractBoard.hpp"

#include "tic_tac_toe/Player.hpp" // needed for template instanciation in .cpp
#include "tic_tac_toe/BoardCell.hpp" // needed for template instanciation in .cpp

#include "penguin/PenguinPlayer.hpp" // needed for template instanciation in .cpp
#include "penguin/BoardCell.hpp" // needed for template instanciation in .cpp

namespace game
{
template<class PlayerT, class CellT>
class AbstractBoard;

template<class PlayerT, class CellT>
class AbstractGame
{
public:
    AbstractBoard<PlayerT, CellT> *board;

    explicit AbstractGame(AbstractBoard<PlayerT, CellT> *board);

    virtual ~AbstractGame(){};

    /** 
     * @brief Tells if the game is finished yet
     * 
     * @return true 
     * @return false 
     */
    virtual bool isFinished() const = 0;

    // /**
    //  * @brief play one round of the game
    //  *
    //  * @return the played cell
    //  */
    // virtual AbstractBoardCell *play(AbstractPlayer *p1, AbstractPlayer *p2) = 0;

    virtual bool play(const int player_id, CellT *cell) = 0;

    virtual void revertPlay(CellT *cell) = 0;

   /**
     * @brief Get the player who hadn't play yet
     * 
     * @return const int the player id 
     */
    virtual int getPlayerToPlay() const = 0;

    /**
     * @brief Checks the status of the game, if won, draw
     * 
     * @return int when won : the id of the winner, -1 if draw, 0 otherwise
     */
    virtual int checkStatus() const = 0;
};
} // namespace game

#endif