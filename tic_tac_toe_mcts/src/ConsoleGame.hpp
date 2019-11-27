#ifndef CONSOLE_GAME_HPP_
#define CONSOLE_GAME_HPP_

#include <iostream>
#include "AbstractGame.hpp"
#include "Board.hpp"
#include "HumanPlayer.hpp"
#include "JSPlayer.hpp"
#include "MCTSPlayer.hpp"

namespace game
{
class ConsoleGame : public AbstractGame, public AbstractInterface
{
public:
    ConsoleGame();
    ~ConsoleGame();

    void draw() const override;
    bool isFinished() const override;
    AbstractBoardCell *play(AbstractPlayer *player1, AbstractPlayer *player2) override;
    void revertPlay(AbstractBoardCell *move) override;
    
    /**
     * @brief Loop while the game is not finished, told by the `isFinished` method
     * 
     */
    virtual void loop();
};
} // namespace game

#endif