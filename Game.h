#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Struct.h"

char is_alive( int i, int j, char ** ptr, symbols_t * syms );
void generation( int n, int writeOpt, char *fileOut, dimension_t *dim, grid_t *main_grid, grid_t *util_grid, symbols_t * syms );
void to_clear( grid_t *toclear, dimension_t *dim, symbols_t * syms );
void change( grid_t *first, grid_t *second, dimension_t *dim );
int check( grid_t *check_1, grid_t *check_2, dimension_t *dim );
void innit_grid( grid_t * grid, dimension_t * dim, symbols_t * syms );
void free_grid( grid_t grid, dimension_t dim);

#endif // GAME_H_INCLUDED
