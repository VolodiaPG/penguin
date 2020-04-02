#include "PrintHex.hpp"

namespace game
{
namespace penguin
{
PrintHex::PrintHex(size_t dimension)
{
    _dimension = dimension;
    _size_line = dimension * (WIDTH - BORDERS_LENGTH) + WIDTH + 1;
    size_t char_size = _size_line * (dimension - 2) * HEIGHT + 1;
    _char_map = (char *)malloc(char_size * sizeof(char)); // create the map containing all the characters

    for (size_t ii = 0; ii < char_size; ++ii)
    { // fill with spaces
        _char_map[ii] = ii % _size_line == _size_line - 1 ? '\n' : ' ';
    }
    _char_map[strlen(_char_map)] = '\0';
}

PrintHex::~PrintHex()
{
    if (_char_map)
        free(_char_map);
}

void PrintHex::print(Board &board)
{
    int offset = 0;
    for (int yy = 0; yy < (int)_dimension; ++yy) // ii for the rows
    {
        for (int xx = offset; xx < (int)_dimension + offset; ++xx) // jj for the cols
        {
            BoardCell *cell = board.getCell(xx, yy);

            if (!cell->isGone())
            {
                const Position &pos = {xx, yy};
                char line1[4], line2[4];
                PenguinPlayer *owner = cell->getOwner();
                if (owner)
                    sprintf(line1, "P:%d", owner->getId());
                else
                    sprintf(line1, " ");
                    
                sprintf(line2, "F:%d", cell->getFish());

                printHex(
                    pos,
                    line1,
                    line2);
            }
        }

        if (yy % 2 == 1)
        {
            --offset;
        }
    }

    std::cout << _char_map;
}

void PrintHex::printHex(
    const Position &coords_axial,
    char *line_top,
    char *line_bottom)
{
    int xx, yy;
    const size_t buf_length = strlen(TEMPLATE) + 1;
    char *buff = (char *)malloc(sizeof(char) * buf_length);
    char *ptr;
    char delim[] = {'\n'};

    mapHexCoordsToCharCoords(coords_axial, &xx, &yy);

    memcpy(buff, TEMPLATE, strlen(TEMPLATE) + 1);
    memcpy(strstr(buff, "X  "), line_top, std::min(strlen(line_top), MAX_TEXT_LENGTH));
    memcpy(strstr(buff, "Y  "), line_bottom, std::min(strlen(line_bottom), MAX_TEXT_LENGTH));

    ptr = strtok(buff, delim); // split string over '\n'
    while (ptr != nullptr)
    {
        memcpy(_char_map + xx + yy, ptr, strlen(ptr));

        ptr = strtok(nullptr, delim);
        yy += _size_line; // go to next line
    }

    free(buff);
}

void PrintHex::mapHexCoordsToCharCoords(
    const Position &coords_axial,
    int *res_xx,
    int *res_yy)
{
    const Position &coords_offset = hex_cube_to_offset(hex_axial_to_cube(coords_axial));
    const int xx = coords_offset.x;
    const int yy = coords_offset.y;
    
    *res_xx = (WIDTH - BORDERS_LENGTH) * xx + ((yy % 2) * (HEIGHT - SIDE_HEIGHT));
    *res_yy = (HEIGHT - SIDE_HEIGHT) * yy * _size_line;
}
} // namespace penguin
} // namespace game