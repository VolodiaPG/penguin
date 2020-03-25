#ifndef TIC_TAC_TOE_TIC_TAC_TOE_HPP_
#define TIC_TAC_TOE_TIC_TAC_TOE_HPP_

#include <iostream>
#include "../AbstractGame.hpp"
#include "Board.hpp"

// #include <emscripten/bind.h>

namespace game
{
namespace tic_tac_toe
{
class TicTacToe : public AbstractGame<Player, BoardCell>
{
protected:
    /**
     * @brief The cound of the moves done
     * 
     */
    int numberMoves = 0;

public:
    explicit TicTacToe();
    ~TicTacToe();

    bool isFinished() const override;
    bool play(const int player_id, BoardCell *cell) override;
    void revertPlay(BoardCell *move) override;
    int getPlayerToPlay() const override;
    int checkStatus() const override { return board->checkStatus(); };
};
} // namespace tic_tac_toe
} // namespace game

// EMSCRIPTEN_BINDINGS(module_playervcomputer)
// {
//     emscripten::class_<game::PlayerVComputer>("PlayerVComputer")
//         .constructor<game::JSPlayer::action_callback>()
//         .function("playGame", &game::PlayerVComputer::playGame)
//         .function("isFinished", &game::PlayerVComputer::isFinished);
// }

#endif