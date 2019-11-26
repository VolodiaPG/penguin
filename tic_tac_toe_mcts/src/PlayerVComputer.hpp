#ifndef PLAYER_V_COMPUTER_HPP_
#define PLAYER_V_COMPUTER_HPP_

#include <iostream>
#include "AbstractGame.hpp"
#include "Board.hpp"
#include "JSPlayer.hpp"
#include "MCTSPlayer.hpp"

namespace game
{
class PlayerVComputer : public AbstractGame
{
public:
    explicit PlayerVComputer(JSPlayer::action_callback humanActionCallback);
    ~PlayerVComputer();

    void draw() const override;
    bool isFinished() const override;
    AbstractBoardCell *play(AbstractPlayer *player1, AbstractPlayer *player2) override;
    void revertPlay(AbstractBoardCell *move) override;
    void loop() override;
};
} // namespace game

#endif