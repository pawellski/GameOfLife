#include <stdio.h>
#include <stdlib.h>

#include "WriteFile.h"

#define MAX_STR_SIZE 200

void print_to_screen(int n, grid_t *to_write, dimension_t *dim)
{
    printf("PLANSZA PO %d ITERACJI\n", n);
    for(int i=1; i<(dim->rows)-1; ++i)
    {
        for(int j=1; j<(dim->columns)-1; ++j)
        {
            printf("%c ",to_write->cells[i][j]);
        }
        printf("\n");
    }
}

void fill_in_file(int n, char *filename, grid_t *to_write, dimension_t *dim)
{
    FILE *fp = fopen(filename, "a");

    fprintf (fp, "PLANSZA PO %d ITERACJI\n", n);
    for(int i=1; i<(dim->rows)-1; ++i)
    {
        for(int j=1; j<(dim->columns)-1; ++j)
        {
            fprintf (fp, "%c ", to_write->cells[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose( fp );

}

void
make_gif_command( double delay, int gen_num, char *gifFilename)
{
	char str[MAX_STR_SIZE];
	sprintf(str, "convert -delay %g -loop 0 $(for i in $(seq 1 1 %d); do echo ~/GameOfLife/Obrazy_PNG/Obraz${i}.png; done) %s", delay, gen_num, gifFilename);
	const char * command = str;
	system(command);
}

void
delete_png_from_dir( void )
{
	system("mkdir Obrazy_PNG");
	system("cd Obrazy_PNG");
   	system("rm -rf ~/GameOfLife/Obrazy_PNG/*");
    	system("cd ..");
}
