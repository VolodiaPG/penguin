#ifndef PENGUIN_PENGUIN_GAME_HPP_
#define PENGUIN_PENGUIN_GAME_HPP_

#include <iostream>
#include "../AbstractGame.hpp"
#include "Board.hpp"

// #include <emscripten/bind.h>

namespace game
{
namespace penguin
{
class PenguinGame : public AbstractGame<PenguinPlayer, BoardCell>
{
protected:
    /**
     * @brief The cound of the moves done
     * 
     */
    int numberMoves = 0;

public:
    explicit PenguinGame(const size_t dimension, const size_t number_of_penguins_per_team);
    ~PenguinGame();

    bool isFinished() const override;
    bool play(const int player_id, BoardCell *cell) override;
    void revertPlay(BoardCell *move) override;
    int getPlayerToPlay() const override;
    int checkStatus() const override { return board->checkStatus(); };
    Board *getBoard() { return (Board *)board; };
};
} // namespace penguin
} // namespace game

#endif