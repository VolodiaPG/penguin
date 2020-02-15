#ifndef TIC_TAC_TOE_HPP_
#define TIC_TAC_TOE_HPP_

#include <iostream>
#include "../AbstractGame.hpp"
#include "Board.hpp"

// #include <emscripten/bind.h>

namespace game
{
    namespace tic_tac_toe{
class TicTacToe : public AbstractGame
{
protected:
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

    /**
     * @brief The cound of the moves done
     * 
     */
    int numberMoves = 0;

public:
    explicit TicTacToe(AbstractPlayer *player1, AbstractPlayer *player2);
    ~TicTacToe();

    bool isFinished() const override;
    bool play(AbstractPlayer *player, AbstractBoardCell *cell) override;
    void revertPlay(AbstractBoardCell *move) override;
    AbstractPlayer *getPlayerToPlay() const override;
    int checkStatus() const override { return board->checkStatus(); };
};
    }
} // namespace game

// EMSCRIPTEN_BINDINGS(module_playervcomputer)
// {
//     emscripten::class_<game::PlayerVComputer>("PlayerVComputer")
//         .constructor<game::JSPlayer::action_callback>()
//         .function("playGame", &game::PlayerVComputer::playGame)
//         .function("isFinished", &game::PlayerVComputer::isFinished);
// }

#endif