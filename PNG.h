#ifndef PNG_H
#define PNG_H
#include "Game.h"

int png(grid_t *util_grid, dimension_t *dim, symbols_t *syms, int n);
void describe_png(grid_t *util_grid, dimension_t *dim, symbols_t *syms);
void make_png(char *file_name);
void free_pixels(void);

#endif

