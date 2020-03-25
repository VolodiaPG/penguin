#include "Board.hpp"

namespace game
{
namespace penguin
{
Board::Board(const size_t dimension, const int number_of_penguins)
    : AbstractBoard(),
      _dimension(dimension)
{
    // generate the 2 players &
    // Generate the penguins for each team (x2)
    for (int ii = 0; ii < 2; ++ii)
    {
        _players.push_back(HumanPlayer(ii));
        HumanPlayer &player = _players[ii]; // make sure to get the copy inside the vector and not the local one...
        for (int jj = 0; jj < number_of_penguins; ++jj)
        {
            _penguins_on_board.push_back(PenguinPlayer(ii * number_of_penguins + jj, player)); //TODO verify no crashing because doing shadowy things with references
        }
    }

    //TODO découpler la génération et le parcours de la structure elle même (pattern visiteur)
    int offset = 0;
    for (int ii = 0; ii < (int)_dimension; ++ii) // ii for the rows
    {
        for (int jj = offset; jj < (int)_dimension + offset; ++jj) // jj for the cols
        {

            // cols in x and rows in y
            const Position pos = Position{jj, ii};

            boardValues.insert_or_assign(pos,
                                         new BoardCell(pos,
                                                       rand() % 3 + 1 // random number of fish between 1 and 3 (included)
                                                       ));
        }

        if (ii % 2 == 1)
        {
            --offset;
        }
    }
}

Board::~Board()
{
    for (const auto &entry : boardValues)
    {
        delete entry.second;
    }
}

bool Board::checkForCorrectness(const Position &start_axial, const Position &destination_axial) const
{
    const Position3D start = hex_axial_to_cube(start_axial);
    const Position3D destination = hex_axial_to_cube(destination_axial);

    // checking if the move is allowed <=> checking if the hex cell is on a direct line from one of the side of the start one
    // <=> in a cube coordinate system, it is the same as looking if one of the coordinate is the same
    return !boardValues.at(destination_axial)->isOwned() && (start.x == destination.x ||
                                                             start.y == destination.y ||
                                                             start.z == destination.z);
}

bool Board::performMove(const int penguin_id, BoardCell *cell)
{
    PenguinPlayer *penguin_player = getPlayerById(penguin_id);
    bool isCorrect = checkForCorrectness(penguin_player->getStandingOn()->getPosition(), cell->getPosition());

    if (isCorrect)
    {
        BoardCell *previousCell = penguin_player->getStandingOn();
        previousCell->clearOwner(); // clear the owner and create a hole in the board
        previousCell->setGone(true);

        cell->setOwner(*penguin_player);
        penguin_player->getOwner().addScore(cell->getFish());
        penguin_player->setStandingOn(cell);
    }

    return isCorrect;
}

void Board::revertMove(const int penguin_id, BoardCell *cell)
{
    PenguinPlayer *penguin_player = getPlayerById(penguin_id);
    BoardCell *previousCell = penguin_player->getPreviousStandingOn();
    cell->clearOwner(); // clear the owner of the current cell

    previousCell->setOwner(*penguin_player);                    // set the penguin as the owner of the previous cell
    penguin_player->getOwner().substractScore(cell->getFish()); // update the score
    penguin_player->setStandingOn(previousCell);
}

//TODO check for win
// int Board::checkForWin(const board_line_t &line) const
// {
//     int previous = line[0]->getValue();
//     // check if this is the same value all along the line
//     for (const BoardCell *cell : line)
//     {
//         int value = cell->getValue();
//         if (value != previous)
//         {
//             // line is not full of the same values
//             return 0;
//         }
//     }

//     // it has been the same value all along from the beginning,
//     // return the id of the line's owner
//     return previous;
// }

// TODO which player is the winner ?
int Board::checkStatus()
{
    // TODO FIX LOGIC 
    return getAvailableCells(0).size() > 0 ? IN_PROGRESS : DRAW;
}

// TODO get cells available from the penguin player perspective
std::vector<BoardCell *> Board::getAvailableCells(const int penguin_id)
{
    PenguinPlayer* penguin = getPlayerById(penguin_id);
    Position penguin_current_pos = penguin->getStandingOn()->getPosition();

    std::vector<BoardCell *> ret;
    
    int inc_val = -1;
    int ii, jj;
    BoardCell* ptr_cell;
    while (inc_val == -1 || inc_val == 1)
    {
        ii = penguin_current_pos.x;
        jj = penguin_current_pos.y;
        // check first diag, jj is varying
        while((ptr_cell = boardValues[Position{ii, jj+=inc_val}]) != nullptr && !ptr_cell->isGone())
        {
            ret.push_back(ptr_cell);
        }

        jj = penguin_current_pos.y;

        // check second diag, ii is varying
        while((ptr_cell = boardValues[Position{ii+=inc_val, jj}]) != nullptr && !ptr_cell->isGone())
        {
            ret.push_back(ptr_cell);
        }

        ii = penguin_current_pos.x;

        // check row, both varying
        while((ptr_cell = boardValues[Position{ii+=inc_val, jj+=inc_val}]) != nullptr && !ptr_cell->isGone())
        {
            ret.push_back(ptr_cell);
        }

        inc_val += 2; // -1; 1; out of scope, while is over
    }

    // return a copy
    return ret;
}

// TODO check if we want all the cells or just the ones that aren't gone yet
std::vector<BoardCell *> Board::getBoardCells()
{
    std::vector<BoardCell *> ret;

    for (const auto &entry : boardValues)
    {
        ret.push_back(entry.second);
    }

    // copy return
    return ret;
}

BoardCell *Board::getCell(int line, int col)
{
    const Position pos = Position{line, col};
    return boardValues.at(pos);
}

std::vector<PenguinPlayer *> Board::getPlayersOnBoard()
{
    std::vector<PenguinPlayer *> ret;
    for (PenguinPlayer &penguin : _penguins_on_board)
    {
        ret.push_back(&penguin);
    }

    return ret;
}
} // namespace penguin
} // namespace game