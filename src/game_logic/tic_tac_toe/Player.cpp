#include "../AbstractPawn.hpp"
#include "BoardCell.hpp"

#include "Player.hpp"
namespace game
{
namespace tic_tac_toe
{
Player::Player(unsigned int id)
    : AbstractPlayer(id),
      AbstractPawn(id, *this)
{
}
} // namespace tic_tac_toe
} // namespace game