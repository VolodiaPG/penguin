#include "PlayerVComputer.hpp"

namespace game
{
PlayerVComputer::PlayerVComputer()
    : TicTacToe(nullptr, nullptr) // instanciate these variables in the body of the constructor
{
    player1 = new HumanPlayer(1, this);
    player2 = new MCTSPlayer(2, this);
}

PlayerVComputer::~PlayerVComputer()
{
    delete player1;
    delete player2;
}

} // namespace game
