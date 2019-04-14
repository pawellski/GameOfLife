#ifndef WRITEFILE_H_INCLUDED
#define WRITEFILE_H_INCLUDED

#include "Game.h"

void fill_in_file(int n, char *filename, grid_t *to_write, dimension_t *dim);
void print_to_screen(int n, grid_t *to_write, dimension_t *dim);
void make_gif_command( double delay, int gen_num, char *gifFilename);
void delete_png_from_dir( void );


#endif // WRITEFILE_H_INCLUDED
