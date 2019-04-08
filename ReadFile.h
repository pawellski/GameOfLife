#ifndef READFILE_H_INCLUDED
#define READFILE_H_INCLUDED

#include "Game.h"


void read_dimension( char *filename, dimension_t *dim, symbols_t * syms );
void fill_in_grid( char *filename, grid_t *poiv, symbols_t * syms );


#endif // READFILE_H_INCLUDED
