#include "Struct.h"

void to_clear(grid_t *toclear, dimension_t *dim);
void change(grid_t *first, grid_t *second, dimension_t *dim);
char is_alive(int i, int j, char **main_ptr);
void generation(int n, dimension_t *dim, grid_t *main_grid, grid_t *util_grid);

