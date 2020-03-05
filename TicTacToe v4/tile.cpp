#include "tile.hpp"

Tile::Tile()
{
    player = NO_PLAYER;
}

Tile::Tile(int p)
{
    player = p;
}

Tile::~Tile()
{

}

bool Tile::isFree()
{
    return player == NO_PLAYER;
}

int Tile::getPlayer()
{
    return player;
}

void Tile::setPlayer(int p)
{
    player = p;
}

bool Tile::isPlayer(int p)
{
    return player == p;
}

void Tile::show()
{
    if(player == PLAYER_X)
        std::cout << "x";
    else if(player == PLAYER_O)
        std::cout << "o";
    else if(player == NO_PLAYER)
        std::cout << " ";
    else
          std::cout << " ";
}
