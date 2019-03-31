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
void change(grid_t *first, grid_t *second, dimension_t *dim)
{
    for(int i = 0; i<(dim->rows); i++)
    {
        for(int j = 0; j<(dim->columns); j++)
            first->cells[i][j] = second->cells[i][j];
    }
}
