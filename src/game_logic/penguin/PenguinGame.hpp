#ifndef PENGUIN_PENGUIN_GAME_HPP_
#define PENGUIN_PENGUIN_GAME_HPP_

#include "../AbstractGame.hpp"

namespace game
{
namespace penguin
{
class PenguinPawn;
class BoardCell;
class HumanPlayer;
class Board;

class PenguinGame : public AbstractGame<BoardCell, HumanPlayer, PenguinPawn>
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
    bool play(PenguinPawn *pawn, BoardCell *cell) override;
    const Move<BoardCell, PenguinPawn> revertPlay() override;
    /**
     * @brief Get the Human player to play, not the penguin one
     * 
     * @return unsigned int the id of the human player to play
     */
    unsigned int getPlayerToPlay() const override;
    int checkStatus() const override;
    Board *getBoard() const;
    std::vector<Move<BoardCell, PenguinPawn>> getAvailableMoves(HumanPlayer *player) override;
};
} // namespace penguin
} // namespace game

#endif