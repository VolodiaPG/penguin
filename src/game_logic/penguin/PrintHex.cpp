#include "PrintHex.hpp"

namespace game
{
namespace penguin
{
PrintHex::PrintHex(Board *board)
    : _board(board)
{
    _dimension = _board->size();
    _size_line = _dimension * (WIDTH - BORDERS_LENGTH) + WIDTH + 1;
    _size_char_map = _size_line * (_dimension - 2) * HEIGHT + 1;
    _char_map = (char *)malloc(_size_char_map * sizeof(char)); // create the map containing all the characters
    _buffer_template = (char *)malloc(sizeof(char) * (strlen(TEMPLATE) + 1));
}

PrintHex::~PrintHex()
{
    if (_char_map)
        free(_char_map);

    if (_buffer_template)
        free(_buffer_template);
}

void PrintHex::clear_map()
{
    for (size_t ii = 0; ii < _size_char_map; ++ii)
    { // fill with spaces
        _char_map[ii] = ii % _size_line == _size_line - 1 ? '\n' : ' ';
    }
    _char_map[strlen(_char_map)] = '\0';
}

void PrintHex::print()
{
    clear_map();

    int offset = 0;
    for (int yy = 0; yy < (int)_dimension; ++yy) // ii for the rows
    {
        for (int xx = offset; xx < (int)_dimension + offset; ++xx) // jj for the cols
        {
            BoardCell *cell = _board->getCell(xx, yy);

            if (!cell->isGone())
            {
                const Position pos = {xx, yy};
                char line1[MAX_TEXT_LENGTH + 1], line2[MAX_TEXT_LENGTH + 1];
                PenguinPlayer *owner = cell->getOwner();
                if (owner)
                    sprintf(line1, "p:%d", (int)owner->getId());
                else
                    sprintf(line1, " ");

                sprintf(line2, "f:%u", cell->getFish());

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

    std::cout << _char_map << std::endl;
}

void PrintHex::printHex(
    const Position &coords_axial,
    const char *line_top,
    const char *line_bottom)
{
    int xx, yy;
    char *ptr, *ptr1;
    char delim[] = {'\n'};

    mapHexCoordsToCharCoords(coords_axial, &xx, &yy);

    memcpy(_buffer_template, TEMPLATE, strlen(TEMPLATE) + 1);
    ptr = strstr(_buffer_template, "X  "); // to make sure we have the position before inserting new characters
    ptr1 = strstr(_buffer_template, "Y  ");
    const size_t len = MAX_TEXT_LENGTH;
    memcpy(ptr, line_top, std::min(strlen(line_top), len));
    memcpy(ptr1, line_bottom, std::min(strlen(line_bottom), len));

    ptr = strtok(_buffer_template, delim); // split string over '\n'
    while (ptr != nullptr)
    {
        memcpy(_char_map + xx + yy, ptr, strlen(ptr));

        ptr = strtok(nullptr, delim);
        yy += _size_line; // go to next line
    }
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