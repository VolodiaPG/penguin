#ifndef ABSTRACT_GAME_HPP_
#define ABSTRACT_GAME_HPP_

#include "AbstractInterface.hpp"
#include "AbstractBoard.hpp"
#include "AbstractPlayer.hpp"

namespace game
{
class AbstractPlayer;

class AbstractGame
{
public:
    AbstractBoard *board;

    explicit AbstractGame(AbstractBoard *board);

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

    virtual bool play(AbstractPlayer *player, AbstractBoardCell *cell) = 0;

    virtual void revertPlay(AbstractBoardCell *cell) = 0;

   /**
     * @brief Get the player who hadn't play yet
     * 
     * @return AbstractPlayer* 
     */
    virtual AbstractPlayer *getPlayerToPlay() const = 0;

    /**
     * @brief Checks the status of the game, if won, draw
     * 
     * @return int when won : the id of the winner, -1 if draw, 0 otherwise
     */
    virtual int checkStatus() const = 0;

    /**
     * @brief Clone function for clonning games
     * 
     * @return AbstractGame* 
     */
    virtual AbstractGame* clone() const = 0;
};
} // namespace game

#endif