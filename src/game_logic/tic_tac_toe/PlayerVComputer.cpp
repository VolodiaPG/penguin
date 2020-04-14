#include "PlayerVComputer.hpp"

namespace game
{
namespace tic_tac_toe
{
PlayerVComputer::PlayerVComputer()
    : TicTacToe()
{
}

PlayerVComputer::~PlayerVComputer()
{
}

bool PlayerVComputer::play(int row, int col)
{
    return play(board->getPlayerById(getPlayerToPlay()), board->getCell(row, col));
}

Move PlayerVComputer::mctsResult()
{
    mcts::MCTSConstraints constraints;
    constraints.time = 250;
    auto game = dynamic_cast<AbstractGame<AbstractBoardCell, AbstractPlayer, AbstractPawn<AbstractPlayer, AbstractBoardCell>> *>(this);
    mcts::Tree tree(game, board->getPlayerById(getPlayerToPlay()), constraints);
    tree.begin();
    return tree.bestMove();
}
} // namespace tic_tac_toe
} // namespace game

// EMSCRIPTEN_BINDINGS(module_player_v_computer)
// {
//     // function("playPlayer1", &playPlayer1);
//     // function("playPlayer2", &playPlayer2);
//     class_<game::PlayerVComputer>("PlayerVComputer")
//         .constructor<>()
//         .function("playPlayer1", &game::PlayerVComputer::playPlayer1)
//         .function("playPlayer2", &game::PlayerVComputer::playPlayer2)
//         .function("isFinished", &game::PlayerVComputer::isFinished);
// }
