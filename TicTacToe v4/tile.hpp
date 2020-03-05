#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>

#define NO_PLAYER -1
#define PLAYER_X 0
#define PLAYER_O 1

class Tile
{
public:
    ~Tile();
    /**
    * @brief Constructs a Tile with player NO_PLAYER
    */
    Tile();
    Tile(int p);
    int getPlayer();
    void setPlayer(int p);
    bool isFree();
    bool isPlayer(int p);
    void show();

private:
    int player;
};

#endif // TILE_HPP
