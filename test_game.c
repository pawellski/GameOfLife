#include <stdio.h>
#include <stdlib.h>

#define ROWS 5
#define COLUMNS 5

typedef struct grid
{
    char **cells;
} grid_t;

typedef struct dimension
{
    int rows;
    int columns;
} dimension_t;

typedef struct symbols
{
    char alive;
    char dead;
} symbols_t;

char is_alive(int i, int j, char **main_ptr, symbols_t * syms)
{
    int alive_number = 0;
    for(int a=-1; a<2; a++)
    {
        for(int b=-1; b<2; b++)
            if(main_ptr[i+a][j+b] == syms->alive)
                alive_number++;
    }

    if(main_ptr[i][j] == syms->alive)
    {
        alive_number--;
        if(alive_number == 2 || alive_number == 3)
            return syms->alive;
        else
            return syms->dead;
    }
    else
    {
        if(alive_number == 3)
            return syms->alive;
        else
            return syms->dead;
    }
}

int main( void )
{
    symbols_t syms;
    syms.alive = '1';
    syms.dead = '0';

    char main_grid[5][5] = { {'0', '0', '0', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '0', '0', '0'} };
    char util_grid[5][5] = { {'0', '0', '0', '0', '0'}, {'0', '0', '0', '0', '0'}, {'0', '0', '0', '0', '0'}, {'0', '0', '0', '0', '0'}, {'0', '0', '0', '0', '0'} };
    char expected[5][5] = { {'0', '0', '0', '0', '0'}, {'0', '0', '0', '0', '0'}, {'0', '1', '1', '1', '0'}, {'0', '0', '0', '0', '0'}, {'0', '0', '0', '0', '0'} }; ;
    char **ptr = (char*)malloc( ROWS * sizeof(char*));
    for(int i = 0; i < ROWS; i++)
        ptr[i] = &(main_grid[i][0]);

    for(int i = 1; i < ROWS - 1; i++)
        {
            for(int j = 1; j < COLUMNS - 1; j++)
                util_grid[i][j] = is_alive(i, j, ptr, &syms );
        }

    printf("Wprowadzona plansza (z buforem): \n");
    for(int i=0; i<ROWS; ++i)
    {
        for(int j=0; j<COLUMNS; ++j)
        {
            printf("%c ",main_grid[i][j]);
        }
        printf("\n");
    }

    printf("Oczekiwana plansza (z buforem):\n");
    for(int i=0; i<ROWS; ++i)
    {
        for(int j=0; j<COLUMNS; ++j)
        {
            printf("%c ",expected[i][j]);
        }
        printf("\n");
    }

    printf("Plansza wygenerowana przez funkcje (z buforem): \n");
    for(int i=0; i<ROWS; ++i)
    {
        for(int j=0; j<COLUMNS; ++j)
        {
            printf("%c ",util_grid[i][j]);
        }
        printf("\n");
    }

    printf("Porownanie znakow z oczekiwanej planszy i wygenerowanej planszy...\n");
    printf("\n");

    for( int i = 0; i < ROWS; i++){
        for( int j = 0; j < COLUMNS; j++){
            if( util_grid[i][j] != expected[i][j] ){
                printf("Blad, plansze roznia sie od siebie!\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    printf("Znaki w obu planszach sa takie same. Test zakonczono pomyslnie!\n");

    return 0;
}

