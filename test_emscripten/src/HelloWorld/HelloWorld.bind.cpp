#include <emscripten/bind.h>
#include "HelloWorld.hpp"
using namespace emscripten;

// Binding code

EMSCRIPTEN_BINDINGS(hello_world_bind)
{
    class_<HelloWorld>("HelloWorld")
        .constructor<std::string>()
        .function("getIdOfInstance", &HelloWorld::getIdOfInstance);
}