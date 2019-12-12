#include "board.hpp"

using namespace std;


Board::Board()
{
    currentPlayer = 0;
    for(int i = 0; i < GRID_SIZE*GRID_SIZE; i++)
    {
        Tile * t = new Tile();
        tiles[i] = t;
    }
}

Board::~Board()
{
    for(int i = 0; i < GRID_SIZE*GRID_SIZE; i++)
    {
        delete tiles[i];
    }
}

void Board::play(int pos)
{
    if(isFree(pos))
    {
       tiles[pos]->setPlayer(currentPlayer);
       currentPlayer = (currentPlayer + 1)%2;
    }
}

void Board::play(int p, int pos)
{
    if(isFree(pos))
    {
        tiles[pos]->setPlayer(p);
    }
}

bool Board::inGrid(int pos)
{
    return pos >=0 && pos < GRID_SIZE*GRID_SIZE;
}

bool Board::isPosValid(int pos)
{
    return pos >=0 && pos < GRID_SIZE*GRID_SIZE && isFree(pos);
}

bool Board::isFree(int pos)
{
    return tiles[pos]->isFree();
}

std::vector<int> Board::getPossiblePositions()
{
    std::vector<int> possible;
    for(int i = 0; i < GRID_SIZE*GRID_SIZE; i++)
    {
        if(Board::isFree(i))
            possible.push_back(i);
    }

    return possible;
}

bool Board::isFull()
{
    for(int i = 0; i < GRID_SIZE*GRID_SIZE; i++)
    {
        if(tiles[i]->isFree())
            return false;
    }
    return true;
}

bool Board::checkWin(int p)
{
    //Checks the columns
    for(int i = 0; i < GRID_SIZE; i++)
    {
        if(tiles[i]->isPlayer(p) && tiles[i + 3]->isPlayer(p) && tiles[i + 6]->isPlayer(p))
            return true;
    }

    //Checks the lignes
    for(int i = 0; i < GRID_SIZE; i++)
    {
        if(tiles[3*i]->isPlayer(p) && tiles[3*i + 1]->isPlayer(p) && tiles[3*i + 2]->isPlayer(p))
            return true;
    }

    if(tiles[0]->isPlayer(p) && tiles[4]->isPlayer(p) && tiles[8]->isPlayer(p))
        return true;
    if(tiles[2]->isPlayer(p) && tiles[4]->isPlayer(p) && tiles[6]->isPlayer(p))
        return true;

    return false;
}

void Board::show()
{
    for(int i = 0; i < 3; i++)
    {
        printEmpty();
        printTiles(i);
        printEmpty();
        if(i != 2)
            printLine();
    }
    std::cout << "\n";
}

void Board::printLine()
{
    for(int i = 0; i < GRID_SIZE; i++)
    {
        std::cout << "----";
    }
    std::cout << "\n";
}

void Board::printEmpty()
{
    for(int i = 0; i < GRID_SIZE - 1; i++)
    {
        std::cout << "   |";
    }
    std::cout << "\n";
}

void Board::printTiles(int d)
{
    for(int j = d * GRID_SIZE; j < d * GRID_SIZE + GRID_SIZE; j++)
    {
        std::cout << " ";
        tiles[j]->show();
        if(j < d * GRID_SIZE + GRID_SIZE - 1)
            std::cout << " |";
    }
    std::cout << "\n";
}

void Board::removePlayer(int pos)
{
    if(inGrid(pos))
    {
        tiles[pos]->setPlayer(NO_PLAYER);
        currentPlayer = (currentPlayer + 1)%2;
    }
}

int Board::getCurrentPlayer()
{
    return currentPlayer;
}

int Board::status()
{
   if(isFull() || checkWin(PLAYER_O) || checkWin(PLAYER_X))
   {
       return FINISHED;
   }else
   {
       return IN_PROGRESS;
   }
}

int Board::getResult()
{
    if(checkWin(PLAYER_O))
        return PLAYER_O;
    if(checkWin(PLAYER_X))
        return PLAYER_X;
    if(isFull())
        return FULL;
    return IN_PROGRESS;
}

void Board::setCurrentPlayer(int p)
{
    currentPlayer = p;
}

void Board::clearBoard()
{
    for(int i = 0; i < GRID_SIZE*GRID_SIZE; i++)
    {
        tiles[i]->setPlayer(NO_PLAYER);
    }
    currentPlayer = PLAYER_X;
}

