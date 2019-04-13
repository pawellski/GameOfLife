#include <stdio.h>
#include <stdlib.h>

#define ROWS 2
#define COLUMNS 4

typedef struct dimension{
    int rows;
    int columns;
} dimension_t;

typedef struct symbols
{
    char alive;
    char dead;
} symbols_t;

void read_dimension(char *filename, dimension_t *dim, symbols_t * syms)
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

int main()
{
    dimension_t static_dimension;
    symbols_t sym;

    char *filename = "file_test_rf.txt";

    sym.alive = '1';
    sym.dead = '0';

    read_dimension(filename, &static_dimension, &sym);

    if(static_dimension.rows == ROWS + 2 && static_dimension.columns == COLUMNS + 2)
    {
        printf("Dimension with buffer:\nRows = %d\nColumns = %d\n", static_dimension.rows, static_dimension.columns);
        printf("Test zakonczony pomyslnie!\n");
        return 0;
    }
    else
    {
        printf("Test zakonczony niepowodzeniem!");
        return 1;
    }
}
