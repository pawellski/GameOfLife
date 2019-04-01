#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Struct.h"
char is_alive(int i, int j, char **main_ptr);
int check(grid_t *check_1, grid_t *check_2, dimension_t *dim);
void change(grid_t *first, grid_t *second, dimension_t *dim);
void generation(int n, int write, char *write_file, dimension_t *dim, grid_t *main_grid, grid_t *util_grid);
void to_clear(grid_t *toclear, dimension_t *dim);


#endif // GAME_H_INCLUDED
