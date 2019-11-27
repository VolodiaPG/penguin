#ifndef ABSTRACT_GAME_HPP_
#define ABSTRACT_GAME_HPP_

#include "AbstractInterface.hpp"
#include "AbstractBoard.hpp"
#include "AbstractPlayer.hpp"

namespace game
{
class AbstractGame
{
public:
    /**
     * @brief Constant pointer to the board used
     * 
     */
    AbstractBoard *board;

    /**
     * @brief First player to play
     * 
     */
    AbstractPlayer *player1 = nullptr;

    /**
     * @brief Second player
     * 
     */
    AbstractPlayer *player2 = nullptr;

    explicit AbstractGame(AbstractBoard *board);

    virtual ~AbstractGame(){};

    /** 
     * @brief Tells if the game is finished yet
     * 
     * @return true 
     * @return false 
     */
    virtual bool isFinished() const = 0;

    /**
     * @brief play one round of the game
     * 
     * @return the played cell
     */
    virtual AbstractBoardCell *play(AbstractPlayer *p1, AbstractPlayer *p2) = 0;

    virtual void revertPlay(AbstractBoardCell *move) = 0;

    /**
     * @brief Get the Next Player
     * 
     * @param player the curretnt playing player
     * @return AbstractPlayer* the complementary player
     */
    AbstractPlayer *getNextPlayer(AbstractPlayer const *player) { return player->getId() == player1->getId() ? player2 : player1; };
};
} // namespace game

#endif