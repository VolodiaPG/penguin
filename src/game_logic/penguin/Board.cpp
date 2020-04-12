#include "Board.hpp"

namespace game
{
namespace penguin
{
Board::Board(const size_t dimension, const size_t number_of_penguins)
    : AbstractBoard(),
      _dimension(dimension)
{
    // generate the 2 players (1 & 2, 0 is forbidden) &
    // Generate the penguins for each team (x2)
    for (int ii = 1; ii <= 2; ++ii)
    {
        HumanPlayer *player = new HumanPlayer(ii);
        _players.push_back(player);
        for (size_t jj = 0; jj < number_of_penguins; ++jj)
        {
            const unsigned int penguin_id = ii * number_of_penguins + jj;
            _penguins_on_board.push_back(new PenguinPlayer(penguin_id, player)); //TODO verify no crashing because doing shadowy things with references
            player->addPenguin(penguin_id);
        }
    }

    //TODO découpler la génération et le parcours de la structure elle même (pattern visiteur)
    int offset = 0;
    for (int yy = 0; yy < (int)_dimension; ++yy) // ii for the rows
    {
        for (int xx = offset; xx < (int)_dimension + offset; ++xx) // jj for the cols
        {
            // rows in x and cols in y
            Position pos;
            pos.x = xx;
            pos.y = yy;

            boardValues.insert_or_assign(pos,
                                         new BoardCell(pos,
                                                       rand() % 3 + 1 // random number of fish between 1 and 3 (included)
                                                       ));
        }

        if (yy % 2 == 1)
        {
            --offset;
        }
    }
}

Board::~Board()
{
    for (auto entry : boardValues)
    {
        if (entry.second)
            delete entry.second;
    }

    for (auto player : _players)
    {
        if (player)
            delete player;
    }

    for (auto player : _penguins_on_board)
    {
        if (player)
            delete player;
    }
}

bool Board::checkForCorrectness(const Position &start_axial, const Position &destination_axial)
{
    bool ret;
    const Position3D start = hex_axial_to_cube(start_axial);
    const Position3D destination = hex_axial_to_cube(destination_axial);

    // check if the move is on a diagonal
    // checking if the move is allowed <=> checking if the hex cell is on a direct line from one of the side of the start one
    // <=> in a cube coordinate system, it is the same as looking if one of the coordinate is the same
    ret = !boardValues.at(destination_axial)->isOwned() && (start.x == destination.x ||
                                                            start.y == destination.y ||
                                                            start.z == destination.z);

    if (ret)
    {
        int xx = start_axial.x, yy = start_axial.y, inc_xx = 0, inc_yy = 0;
        BoardCell *ptr_cell = nullptr;
        // check is a cell is owned or gone between the target and the origin
        if (start.x == destination.x || start.y == destination.y)
        {
            inc_yy = (destination_axial.y - start_axial.y < 0) ? -1 : 1;
        }

        if (start.z == destination.z || start.y == destination.y)
        {
            inc_xx = (destination_axial.x - start_axial.x < 0) ? -1 : 1;
        }
        //TODO check if we are not creating new values (nullptr ones)
        while ((ptr_cell = boardValues[Position{xx += inc_xx, yy += inc_yy}]) != nullptr &&
               (ret = (!ptr_cell->isGone() && !ptr_cell->isOwned())) &&
               destination_axial.x != xx && destination_axial.y != yy)
            ;
    }

    return ret;
}

bool Board::performMove(const int penguin_id, BoardCell *cell)
{
    PenguinPlayer *penguin_player = getPlayerById(penguin_id);
    HumanPlayer *human_player = penguin_player->getOwner();
    BoardCell *cell_standing_on = penguin_player->getStandingOn();
    bool isCorrect = true;

    if (cell_standing_on)
    {
        isCorrect = checkForCorrectness(cell_standing_on->getPosition(), cell->getPosition());
    }

    if (isCorrect)
    {
        if (cell_standing_on)
        {
            // clear the owner and create a hole in the board
            cell_standing_on->clearOwner();
            cell_standing_on->setGone(true);
        }

        cell->setOwner(penguin_player);
        human_player->addScore(cell->getFish());
        human_player->addMoveDone(cell);
        penguin_player->setStandingOn(cell);
    }

    return isCorrect;
}

void Board::revertMove(const int human_player_id)
{
    HumanPlayer *human_player = _players[human_player_id];
    BoardCell *current_cell = (BoardCell *)human_player->dequeueLastMove();

    PenguinPlayer *penguin_player = current_cell->getOwner();

    current_cell->clearOwner();
    current_cell->setGone(false);

    if (human_player->getNumberMovesDone() != 0)
    {
        BoardCell *previous_cell = (BoardCell *)human_player->getCurrentCell();
        previous_cell->setGone(false);
        previous_cell->setOwner(penguin_player);
        penguin_player->setStandingOn(previous_cell);
    }
    else
    {
        penguin_player->setStandingOn(nullptr);
    }
}

int Board::checkStatus()
{
    bool all_zero = true;
    int winner_id = IN_PROGRESS;

    //TODO Optimize, we can just look at the cells around
    for (auto &penguin : getPlayersOnBoard())
    {
        if (getAvailableCells(penguin->getId()).size() > 0)
        {
            all_zero = false;
            break;
        }
    }

    if (all_zero)
    {
        winner_id = _players[1]->getId();
        int score_player_0 = _players[0]->getScore();
        int score_player_1 = _players[1]->getScore();
        if (score_player_0 > score_player_1)
        {
            winner_id = _players[0]->getId();
        }
        else if (score_player_0 == score_player_1)
        {
            winner_id = DRAW;
        }
    }

    return winner_id;
}

std::vector<BoardCell *> Board::getAvailableCells(const int penguin_id)
{
    // dbg(penguin_id);
    PenguinPlayer *penguin = getPlayerById(penguin_id);
    HumanPlayer *human_player = penguin->getOwner();
    // dbg(penguin->getStandingOn());
    Position penguin_current_pos = ((BoardCell *)human_player->getCurrentCell())->getPosition();

    // dbg(penguin_current_pos.x);dbg(penguin_current_pos.y);

    std::vector<BoardCell *> ret;

    int inc_val = -1;
    while (inc_val == -1 || inc_val == 1)
    {
        int ii = penguin_current_pos.x;
        int jj = penguin_current_pos.y;
        BoardCell *ptr_cell;
        // check first diag, jj is varying
        while ((ptr_cell = boardValues[Position{ii, jj += inc_val}]) != nullptr &&
               !ptr_cell->isGone() &&
               !ptr_cell->isOwned())
        {
            ret.push_back(ptr_cell);
        }

        jj = penguin_current_pos.y;

        // check second diag, ii is varying
        while ((ptr_cell = boardValues[Position{ii += inc_val, jj}]) != nullptr &&
               !ptr_cell->isGone() &&
               !ptr_cell->isOwned())
        {
            ret.push_back(ptr_cell);
        }

        ii = penguin_current_pos.x;

        // check row, both varying
        while ((ptr_cell = boardValues[Position{ii += inc_val, jj -= inc_val}]) != nullptr &&
               !ptr_cell->isGone() &&
               !ptr_cell->isOwned())
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

    for (const auto &entry : boardValues) // iterate over the "map"
    {
        ret.push_back(entry.second);
    }

    // copy return
    return ret;
}

BoardCell *Board::getCell(int xx, int yy)
{
    const Position pos = Position{xx, yy};
    return boardValues.at(pos);
}

std::vector<PenguinPlayer *> Board::getPlayersOnBoard()
{
    std::vector<PenguinPlayer *> ret;
    for (PenguinPlayer *penguin : _penguins_on_board)
    {
        ret.push_back(penguin);
    }

    return ret;
}
} // namespace penguin
} // namespace game