#include <stdio.h>
#include <stdlib.h>

#include "Game.h"

void to_clear(grid_t *toclear, dimension_t *dim)
{
    for(int i = 0; i < dim->rows; i++)
    {
        for(int j = 0; j < dim->columns; j++)
            toclear->cells[i][j] = '0';
    }
}
