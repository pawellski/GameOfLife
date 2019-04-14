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

void read_dimension(char *filename, dimension_t *dim, symbols_t * syms )
{
    FILE *fp = fopen(filename, "r");
    int wiersze = 1;
    int kolumny = 0;
    int kolumny_ref = 0;
    char ch;

    if(fp == NULL){
        printf("Podano niewlasciwa nazwe pliku\n");
        exit(EXIT_FAILURE);
    }

    while(( ch = getc( fp )) != EOF ){
        if(ch == '\n')
            break;
        if( ch == syms->dead || ch == syms->alive )
            kolumny_ref++;
    }

    while(( ch = getc( fp )) != EOF ){
        if( ch == '\n'){
            wiersze++;
                    if( kolumny == kolumny_ref)
                            kolumny = 0;
                    else{
                            printf("Plik ma zly format\n");
                            exit(EXIT_FAILURE);
                }
            }
        if( ch == syms->dead || ch == syms->alive)
            kolumny++;
    }
    dim->columns = kolumny_ref + 2;
    dim->rows = wiersze + 2;
    fclose( fp );
}

void fill_in_grid(char *filename, grid_t *grid_pointer, symbols_t * syms )
{
    FILE *fp = fopen(filename, "r");
    char ch;
    int i = 1, j = 1;

    if(fp == NULL)
    {
        printf("Podano niewlasciwa nazwe pliku\n");
        exit(EXIT_FAILURE);
    }

    while(( ch = getc( fp )) != EOF )
    {
        if( ch == syms->dead || ch == syms->alive )
        {
            (grid_pointer->cells[i][j]) = ch;
            j++;
        }
        else if(ch == '\n')
        {
            j = 1;
            i++;
        }
    }
    fclose( fp );
}

int main()
{
    grid_t first_grid;
    dimension_t static_dimension;
    symbols_t sym;

    char *filename = "file_test_rf.txt";
    char table[4][6] = {{'0','0','0','0','0','0'},{'0','1','0','1','0','0'},{'0','1','0','1','0','0'},{'0','0','0','0','0','0'}};
    int count = 0;

    sym.alive = '1';
    sym.dead = '0';

    read_dimension(filename, &static_dimension, &sym);

    first_grid.cells = (char**)malloc(static_dimension.rows * sizeof(char*));
    for(int i = 0; i < static_dimension.rows; i++)
        first_grid.cells[i] = (char*)malloc(static_dimension.columns * sizeof(char));

    for(int i = 0; i < static_dimension.rows; i++)
    {
        for(int j = 0; j < static_dimension.columns; j++)
            first_grid.cells[i][j] = sym.dead;
    }

    fill_in_grid(filename, &first_grid, &sym);    

    printf("Plansza zadeklarowana w programie:\n");
    for( int i = 0; i < ( sizeof(table) / sizeof(table[i])); i++ ){
	    for( int j = 0; j < sizeof( table[i] ); j++ ){
		    printf("%c ", table[i][j]);
	    }
	    printf("\n");
    }
    printf("Plansza wypelniona przez funkcje:\n");
    for( int i = 0; i < static_dimension.rows; i++ ){
            for( int j = 0; j < static_dimension.columns; j++ ){
                    printf("%c ", first_grid.cells[i][j]);
            }
            printf("\n");
    }

    for(int i=1; i<static_dimension.rows-1; i++)
    {
        for(int j=1; j<static_dimension.columns-1; j++)
        {
            if(first_grid.cells[i][j] == table[i][j])
                count++;
        }
    }

    for(int i=0; i<static_dimension.rows; i++)
        free(first_grid.cells[i]);
    free(first_grid.cells);
    first_grid.cells = NULL;

    if(count == ((static_dimension.rows-2)*(static_dimension.columns-2)))
    {
        printf("Przy porownaniu 2 plansz (jedna zapelniona poprzez funkcje,\ndruga przygotowana do porownania) otrzymalismy %d elementow\n", count);
        printf("takich samych na tych samych pozycjach w macierzy 2 x 4.\n");
        printf("Test zakonczony pomyslnie!\n");
        return 0;
    }
    else
    {
        printf("Test zakonczony niepowodzeniem!");
        return 1;
    }
}
