#include "HelloWorld.hpp"

HelloWorld::HelloWorld(const std::string hello_world)
: _hello_world(hello_world)
{
    static size_t _instance_number = 0;
    _instance_id = _instance_number++;
}

HelloWorld::~HelloWorld()
{
}

std::string HelloWorld::getContent() const
{
    return _hello_world;
}

size_t HelloWorld::getIdOfInstance() const
{
    return _instance_id;
}