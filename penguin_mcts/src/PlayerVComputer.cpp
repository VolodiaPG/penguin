#include "PlayerVComputer.hpp"

namespace game
{
PlayerVComputer::PlayerVComputer()
    : TicTacToe(nullptr, nullptr) // instanciate these variables in the body of the constructor
{
    player1 = new Player(1);
    player2 = new Player(2);
}

PlayerVComputer::~PlayerVComputer()
{
    delete player1;
    delete player2;
}

bool PlayerVComputer::play(int row, int col)
{
    return play(getPlayerToPlay(), board->getCell(row, col));
}

AbstractBoardCell *PlayerVComputer::mctsResult()
{
    mcts::MCTSConstraints constraints;
    constraints.time = 250;
    mcts::Tree tree(this, getPlayerToPlay(), constraints);
    tree.begin();
    AbstractBoardCell *bestMove = tree.bestMove();

    return bestMove;
}

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
