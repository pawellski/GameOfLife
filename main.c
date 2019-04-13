#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ReadFile.h"
#include "Game.h"


int main(int argc, char *argv[])
{
    symbols_t syms;
    syms.alive = '1';
    syms.dead = '0';
    int opt;
    int count_generation = 30;
    char *fileIn = "in.txt";
    char *fileOut = "out.txt";
    int writeOpt = 0;

        while((opt = getopt(argc, argv, ":n:i:o:a:d:w:")) != -1 ){
        switch(opt){
        case 'n':
            count_generation = atoi(optarg);
	    if( count_generation <= 0){
	    	printf("Ilosc generacji musi byc liczba calkowita wieksza od 0\n");
		exit(EXIT_FAILURE);
	    }
            break;
        case 'i':
            fileIn = optarg;
            break;
        case 'o':
            fileOut = optarg;
            break;
        case 'a':
            syms.alive = *optarg;
            break;
        case 'd':
            syms.dead = *optarg;
            break;
        case 'w':
            writeOpt = atoi(optarg);
            if(writeOpt < 0 || writeOpt > 2){
                printf("Opcja --w musi byc liczba calkowita z przedzialu <0 ; 2>");
                exit(EXIT_FAILURE);
            } else 
                break;
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

    innit_grid( &first_grid, &static_dimension, &syms );
    innit_grid( &second_grid, &static_dimension, &syms );
    //WCZYTANIE PLIKU
    fill_in_grid(fileIn, &first_grid, &syms);

    //URUCHOMIENIE GRY
    generate_all(count_generation, writeOpt, fileOut, &static_dimension, &first_grid, &second_grid, &syms);

    free_grid( first_grid, static_dimension );
    free_grid( second_grid, static_dimension );

    return 0;
}
