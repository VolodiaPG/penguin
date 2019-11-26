#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <stdlib.h>

#include <emscripten/bind.h>

using namespace emscripten;

namespace game
{
typedef struct
{
     unsigned int x = 0;
     unsigned int y = 0;
} Position;


} // namespace game

#endif

// EMSCRIPTEN_BINDINGS(struct_position)
// {
     
// }
