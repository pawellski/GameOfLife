#include <stdio.h>
#include <stdlib.h>

typedef struct grid
{
    char **cells;
} grid_t;

typedef struct dimension{
    int rows;
    int columns;
} dimension_t;

typedef struct symbols
{
    char alive;
    char dead;
} symbols_t;

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


int main()
{
    grid_t first_grid;
    dimension_t static_dimension;

    static_dimension.rows = 4;
    static_dimension.columns = 6;

    char *filename = "file_test_wf.txt";
    int n = 0;

    first_grid.cells = (char**)malloc(static_dimension.rows * sizeof(char*));
    for(int i = 0; i < static_dimension.rows; i++)
        first_grid.cells[i] = (char*)malloc(static_dimension.columns * sizeof(char));

    for(int i = 0; i < static_dimension.rows; i++)
    {
        for(int j = 0; j < static_dimension.columns; j++)
            first_grid.cells[i][j] = '0';
    }

    fill_in_file(n, filename, &first_grid, &static_dimension);

    for(int i=0; i<static_dimension.rows; i++)
        free(first_grid.cells[i]);
    free(first_grid.cells);
    first_grid.cells = NULL;

    printf("Jezeli w pliku o nazwie 'file_test_wf.txt' zostala zapisana macierz 2 x 4 wypelniona zerami.\nTest przeprowadzono pomyslnie!\n");
        return 0;
}
