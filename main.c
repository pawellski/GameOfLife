#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ReadFile.h"
#include "Game.h"
#include "Struct.h"


int main(int argc, char *argv[])
{
    symbols_t syms;
    syms.alive = '1';
    syms.dead = '0';
    int opt;
    int count_generation = 30;
    char *fileIn;
    char *fileOut = "out.txt";
    int writeOpt = 0;

        while((opt = getopt(argc, argv, ":n:i:o:a:d:x:")) != -1 ){
        switch(opt){
        case 'n':
            count_generation = atoi(optarg);
            printf("count_generation = %d\n", count_generation);
            break;
        case 'i':
            fileIn = optarg;
            printf("fileIn = %s\n", fileIn);
            break;
        case 'o':
            fileOut = optarg;
            printf("fileOut = %s\n", fileOut);
            break;
        case 'a':
            syms.alive = *optarg;
            printf("syms.alive = %c\n", syms.alive);
            break;
        case 'd':
            syms.dead = *optarg;
            printf("syms.dead = %c\n", syms.dead);
            break;
        case 'x':
            writeOpt = atoi(optarg);
            if(writeOpt < 0 || writeOpt > 2){
                printf("Opcja --x musi byc liczba calkowita z przedzialu <0 ; 2>");
                exit(EXIT_FAILURE);
            } else {
                printf("writeOpt = %d\n", writeOpt);
                break;
            }
        case ':':
            printf("Option needs a value");
            break;
        case '?':
            printf("Unknown option: %c\n", optopt);
            break;
        }
    }

    grid_t first_grid;
    grid_t second_grid;
    dimension_t static_dimension;

    read_dimension( fileIn, &static_dimension, &syms);

    printf("Bez bufora\nWiersze: %d\nKolumny: %d\n", (static_dimension.rows)-2, (static_dimension.columns)-2);
    printf("Z buforem\nWiersze: %d\nKolumny: %d\n", static_dimension.rows, static_dimension.columns);

    //ALOKACJA PAMI�CI
    first_grid.cells = (char**)malloc(static_dimension.rows * sizeof(char*));
    second_grid.cells = (char**)malloc(static_dimension.rows * sizeof(char*));
    for(int i = 0; i < static_dimension.rows; i++)
    {
        first_grid.cells[i] = (char*)malloc(static_dimension.columns * sizeof(char));
        second_grid.cells[i] = (char*)malloc(static_dimension.columns * sizeof(char));
    }

    //CZYSZCZENIE TABLIC + ROBIENIE BUFORA
    to_clear(&first_grid, &static_dimension, &syms);
    to_clear(&second_grid, &static_dimension, &syms);

    //WCZYTANIE PLIKU
    fill_in_grid(fileIn, &first_grid, &syms);

    //URUCHOMIENIE GRY
    generation(count_generation, writeOpt, fileOut, &static_dimension, &first_grid, &second_grid, &syms);

    //ZWOLNIENIE PAMIECI
    for(int i=0; i<static_dimension.rows; i++)
    {
        free(first_grid.cells[i]);
        free(second_grid.cells[i]);
    }

    free(first_grid.cells);
    free(second_grid.cells);
    first_grid.cells = NULL;
    second_grid.cells = NULL;


    return 0;
}
