#include "../tic_tac_toe/Player.hpp"
#include "../tic_tac_toe/BoardCell.hpp"

#include "../penguin/PenguinPawn.hpp"
#include "../penguin/BoardCell.hpp"

#include "Move.hpp"

namespace game
{
template struct Move<tic_tac_toe::BoardCell, tic_tac_toe::Player>;
template struct Move<penguin::BoardCell, penguin::PenguinPawn>;
} // namespace game
