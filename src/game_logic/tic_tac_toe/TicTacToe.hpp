#ifndef TIC_TAC_TOE_TIC_TAC_TOE_HPP_
#define TIC_TAC_TOE_TIC_TAC_TOE_HPP_

#include <iostream>
#include <algorithm>
#include "../AbstractGame.hpp"
#include "Board.hpp"


namespace game
{
namespace tic_tac_toe
{
class TicTacToe : public AbstractGame<BoardCell, Player, Player>
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
    bool play(Player *player, BoardCell *cell) override;
    void revertPlay() override;
    unsigned int getPlayerToPlay() const override;
    int checkStatus() const override { return board->checkStatus(); };
    std::vector<Move> getAvailableMoves(Player* player) override;
};
} // namespace tic_tac_toe
} // namespace game

#endif