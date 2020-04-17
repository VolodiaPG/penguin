#include <iostream>

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

#endif