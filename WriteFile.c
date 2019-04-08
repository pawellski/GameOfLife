#include <stdio.h>
#include <stdlib.h>

#include "WriteFile.h"

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
