#include "PenguinPawn.hpp"

namespace game
{
namespace penguin
{
PenguinPawn::PenguinPawn(unsigned int id, HumanPlayer *owner)
    : AbstractPawn(id, *owner)
{
    static unsigned int _count_penguins;
    _penguin_id_from_counter = _count_penguins++;
}
} // namespace penguin
} // namespace game