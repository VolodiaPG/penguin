#ifndef PLAYER_V_COMPUTER_HPP_
#define PLAYER_V_COMPUTER_HPP_

#include <iostream>
#include "AbstractGame.hpp"
#include "Board.hpp"
#include "JSPlayer.hpp"
#include "MCTSPlayer.hpp"

#include <emscripten/bind.h>

namespace game
{
class PlayerVComputer : public AbstractGame
{
public:
    explicit PlayerVComputer(JSPlayer::action_callback humanActionCallback);
    ~PlayerVComputer();

    bool isFinished() const override;
    AbstractBoardCell *play(AbstractPlayer *player1, AbstractPlayer *player2) override;
    void revertPlay(AbstractBoardCell *move) override;

    void playGame() { play(player1, player2); };
};
} // namespace game

EMSCRIPTEN_BINDINGS(module_playervcomputer)
{
    emscripten::class_<game::PlayerVComputer>("PlayerVComputer")
        .constructor<game::JSPlayer::action_callback>()
        .function("playGame", &game::PlayerVComputer::playGame)
        .function("isFinished", &game::PlayerVComputer::isFinished);
}

#endif