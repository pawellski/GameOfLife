#include <stdio.h>
#include <stdlib.h>

#include "Game.h"

void generation(int n, dimension_t *dim, grid_t *main_grid, grid_t *util_grid)
{
    char **ptr = (char*)malloc((dim->rows)*sizeof(char*));
    for(int i = 0; i<(dim->rows); i++)
        ptr[i] = &(main_grid->cells[i][0]);

    for(int it=1; it<n+1; it++)
    {
        for(int i=1; i<dim->rows-1; i++)
        {
            for(int j=1; j<dim->columns-1; j++)
                util_grid->cells[i][j] = is_alive(i, j, ptr);
        }

   	printf("PLANSZA PO %d ITERACJI\n", it);
    	for(int i=1; i<(dim->rows)-1; ++i)
    	{
       	    for(int j=1; j<(dim->columns)-1; ++j)
            {
            	printf("%c ",util_grid->cells[i][j]);
       	    }
            printf("\n");
    	}
	to_clear(main_grid, dim);
        change(main_grid, util_grid, dim);
        to_clear(util_grid, dim);
    }
}

char is_alive(int i, int j, char **main_ptr)
{
    int alive_number = 0;
    for(int a=-1; a<2; a++)
    {
        for(int b=-1; b<2; b++)
            if(main_ptr[i+a][j+b] == '1')
                alive_number++;
    }

    if(main_ptr[i][j] == '1')
    {
        alive_number--;
        if(alive_number == 2 || alive_number == 3)
            return '1';
        else
            return '0';
    }
    else
    {
        if(alive_number == 3)
            return '1';
        else
            return '0';
    }
}

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
