#ifndef TIC_TAC_TOE_TIC_TAC_TOE_HPP_
#define TIC_TAC_TOE_TIC_TAC_TOE_HPP_

#include "../utils/Move.hpp"
#include "../AbstractGame.hpp"

namespace game
{
class BoardCell;
class Player;
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
    const Move<BoardCell, Player> revertPlay() override;
    unsigned int getPlayerToPlay() const override;
    int checkStatus() const override;
    std::vector<Move<BoardCell, Player>> getAvailableMoves(Player *player) override;
    AbstractGame<BoardCell, Player, Player>* clone() const override;
};
} // namespace tic_tac_toe
} // namespace game

#endif