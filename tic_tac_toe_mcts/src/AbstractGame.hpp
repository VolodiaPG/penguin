#ifndef ABSTRACT_GAME_HPP_
#define ABSTRACT_GAME_HPP_

#include "AbstractInterface.hpp"
#include "AbstractBoard.hpp"

namespace game
{
class AbstractGame : public AbstractInterface
{
protected:
    /**
     * @brief Constant pointer to the board used
     * 
     */
    AbstractBoard *board;

public:
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
     * @brief Encapsulation of the play method with an argument, must be details on how to use the one wioth arguments 
     * 
     */
    virtual void play() = 0;

    /**
     * @brief Loop while the game is not finished, told by the `isFinished` method
     * 
     */
    virtual void loop();
};
} // namespace game

#endif