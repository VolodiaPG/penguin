#include <iostream>
#include <cstring>
#include <emscripten/bind.h>

#ifndef _HELLO_WORLD_HPP_
#define _HELLO_WORLD_HPP_

class HelloWorld
{
public:
    explicit HelloWorld(const std::string hello_world);
    ~HelloWorld();
    std::string getContent() const;
    size_t getIdOfInstance() const;

private:
    size_t _instance_id;
    std::string _hello_world;
};

using namespace emscripten;

// Binding code

EMSCRIPTEN_BINDINGS(hello_world_example)
{
    class_<HelloWorld>("HelloWorld")
        .constructor<std::string>()
        .function("getIdOfInstance", &HelloWorld::getIdOfInstance);
}

#endif