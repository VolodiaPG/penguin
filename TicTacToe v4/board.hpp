#ifndef BOARD_HPP
#define BOARD_HPP

#include "tile.hpp"
#include <vector>
#define GRID_SIZE 3
#define IN_PROGRESS -1
#define FINISHED -2
#define FULL -3


class Board
{
public:
    /**
        Constructs a board of size GRID_SIZE*GRID_SIZE
    **/
    Board();
    ~Board();
    /**
        Puts the player p in position pos
    **/
    void play(int p, int pos);
    /**
        Checks is the position pos is free
    **/
    bool isFree(int pos);
    bool isPosValid(int pos);
    std::vector<int> getPossiblePositions();
    void show();
    bool checkWin(int p);
    bool isFull();
    void printTiles(int d);
    void printEmpty();
    void printLine();
    void removePlayer(int pos);
    void play(int pos);
    int getCurrentPlayer();
    void setCurrentPlayer(int p);
    int status();
    int getResult();
    bool inGrid(int pos);
    void clearBoard();

private:
    Tile * tiles[GRID_SIZE*GRID_SIZE];
    int currentPlayer;
};

#endif
