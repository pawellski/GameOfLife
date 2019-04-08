#include <stdio.h>
#include <stdlib.h>

#include "Game.h"


void generate_all(int n, int writeOpt, char *fileOut, dimension_t *dim, grid_t *main_grid, grid_t *util_grid, symbols_t * syms)
{
    symbols_t syms2;
    syms2.alive = syms->alive;
    syms2.dead = syms->dead;
    char **ptr = (char*)malloc((dim->rows)*sizeof(char*));
    for(int i = 0; i<(dim->rows); i++)
        ptr[i] = &(main_grid->cells[i][0]);

    for(int it=1; it<n+1; it++)
    {
        for(int i=1; i<dim->rows-1; i++)
        {
            for(int j=1; j<dim->columns-1; j++)
                util_grid->cells[i][j] = is_alive(i, j, ptr, &syms2);
        }
		switch(writeOpt)
        {
        case 0:
            print(it, util_grid, dim);
            break;
        case 1:
            fill_in_file(it, fileOut, util_grid, dim);
            break;
        case 2:
            print(it, util_grid, dim);
            fill_in_file(it, fileOut, util_grid, dim);
        default:
            break;
        }

        if(check(main_grid, util_grid, dim) == 1)
            ;
        else
        {
            printf("Plansza nie zmienia sie od %d generacji\n", it-1);
            break;
        }
        to_clear( main_grid, dim, &syms2 );
        change( main_grid, util_grid, dim );
        to_clear( util_grid, dim, &syms2 );
    }
    for(int i=0; i<dim->rows; i++)
        free(ptr[i]);
    free(ptr);
    ptr = NULL;
}

char is_alive(int i, int j, char **main_ptr, symbols_t * syms)
{
    int alive_number = 0;
    for(int a=-1; a<2; a++)
    {
        for(int b=-1; b<2; b++)
            if(main_ptr[i+a][j+b] == syms->alive)
                alive_number++;
    }

    if(main_ptr[i][j] == syms->alive)
    {
        alive_number--;
        if(alive_number == 2 || alive_number == 3)
            return syms->alive;
        else
            return syms->dead;
    }
    else
    {
        if(alive_number == 3)
            return syms->alive;
        else
            return syms->dead;
    }
}

void to_clear(grid_t *toclear, dimension_t *dim, symbols_t * syms)
{
    for(int i = 0; i < dim->rows; i++)
    {
        for(int j = 0; j < dim->columns; j++)
            toclear->cells[i][j] = syms->dead;
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

int check(grid_t *check_1, grid_t *check_2, dimension_t *dim)
{
    int count = 0;
    for(int i=1; i<dim->rows-1; i++)
    {
        for(int j=1; j<dim->columns-1; j++)
        {
            if(check_1->cells[i][j] == check_2->cells[i][j])
                count++;
        }
    }
    if(count == ((dim->rows-2)*(dim->columns-2)))
        return 0;
    else
        return 1;
}

void innit_grid( grid_t * grid, dimension_t * dim, symbols_t * syms )
{
    grid->cells = (char**)malloc(dim->rows * sizeof(char*));
    for(int i = 0; i < dim->rows; i++)
        grid->cells[i] = (char*)malloc(dim->columns * sizeof(char));
    to_clear(grid, dim, syms);
}

void free_grid( grid_t grid, dimension_t dim)
{
    for( int i = 0; i < dim.rows; i++ )
        free( grid.cells[i] );
    free( grid.cells );
    grid.cells = NULL;
}

