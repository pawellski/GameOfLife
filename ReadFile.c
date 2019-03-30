#include <stdio.h>
#include <stdlib.h>

#include "ReadFile.h"

void read_dimension(char *filename, dimension_t *dim)
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
        if( ch == '0' || ch == '1' )
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
        if( ch == '0' || ch == '1')
            kolumny++;
    }
    dim->columns = kolumny_ref + 2;
    dim->rows = wiersze + 2;
    fclose(fp);

}

void fill_in_grid(char *filename, grid_t *grid_pointer)
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
        if( ch == '0' || ch == '1' )
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
    fclose(fp);
}
