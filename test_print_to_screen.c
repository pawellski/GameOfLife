#include <stdio.h>
#include <stdlib.h>

#define ROWS 5
#define COLUMNS 6

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

void print(int n, grid_t *to_write, dimension_t *dim)
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

int main()
{
    grid_t first_grid;
    dimension_t static_dimension;

    static_dimension.rows = ROWS + 2;
    static_dimension.columns = COLUMNS + 2;

    int n = 0;

    first_grid.cells = (char**)malloc(static_dimension.rows * sizeof(char*));
    for(int i = 0; i < static_dimension.rows; i++)
        first_grid.cells[i] = (char*)malloc(static_dimension.columns * sizeof(char));

    for(int i = 0; i < static_dimension.rows; i++)
    {
        for(int j = 0; j < static_dimension.columns; j++)
            first_grid.cells[i][j] = '0';
    }
    print(n, &first_grid, &static_dimension);

    for(int i=0; i<static_dimension.rows; i++)
        free(first_grid.cells[i]);
    free(first_grid.cells);
    first_grid.cells = NULL;

    printf("Jezeli na ekranie zostala wyswietlona macierz %d x %d wypelniona zerami.\nTest przeprowadzono pomyslnie!\n", ROWS, COLUMNS);
        return 0;
}
