#include "PenguinPawn.hpp"

namespace game
{
namespace penguin
{
PenguinPawn::PenguinPawn(unsigned int id, HumanPlayer *owner)
    : AbstractPawn(id, *owner)
{
}
} // namespace penguin
} // namespace game