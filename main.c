#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ReadFile.h"
#include "Game.h"
#include "PNG.h"
#include "WriteFile.h"


int main(int argc, char *argv[])
{
    symbols_t syms;
    syms.alive = '1';
    syms.dead = '0';
    int opt;
    int count_generation = 30;
    double delay = 1.00;
    char *gifFilename = "out.gif";
    char *fileIn;
    char *fileOut = "out.txt";
    int writeOpt = 2;
    int generations_done;

        while((opt = getopt(argc, argv, ":n:g:l:i:o:a:d:w:h")) != -1 ){
        switch(opt){
        case 'n':
            count_generation = atoi(optarg);
	    if( count_generation <= 0){
	    	printf("Ilosc generacji musi byc liczba calkowita wieksza od 0\n");
		exit(EXIT_FAILURE);
	    }
            break;
	case 'g':
	    gifFilename = optarg;
	    break;
	case 'l':
	    delay = atof(optarg);
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
                printf("Opcja --w musi byc liczba calkowita z przedzialu <0 ; 2>\n");
                exit(EXIT_FAILURE);
            } else 
                break;
        case ':':
            printf("Opcja potrzebuje argumentu. Użyj opcji -h, aby wyswietlic help\n");
            break;
        case '?':
            printf("Nieznana opcja: %c. Uzyj opcji -h, aby wyswietlic help\n", optopt);
            break;
	case 'h':
	    printf("Program mozna wywolac z nastepujacymi opcjami:\n");
	    printf("-n: Okresla liczbe generacji do wytworzenia. Argument jest liczba dodatnia calkowita\n");
	    printf("-g: Okresla nazwe pliku .gif do ktorego zapisany bedzie wynik porgramu. Argument jest ciagiem znakow zakonczonym '.gif'\n");
	    printf("-l: Okresla opoznienie wyswietlania obrazow w pliku .gif. Argument jest liczba zmiennoprzecinkowa\n");
	    printf("-i: Okresla nazwe wjesciowego pliku tekstowego na podstawie ktorego stworzona bedzie pierwsza plansza. Argument jest ciagiem znakow zakonczonym '.txt'\n");
	    printf("-o: Okresla nazwe pliku tekstowego do ktorego beda zapisane generacje. Argument jest ciagiem znakow zakonczonym '.txt'\n");
	    printf("-a: Okresla symbol uzywany do zapisu komorek zywych. Argument jest jednym znakiem\n");
	    printf("-d: Okresla symbol uzywany do zapisu komorek martwych. Argument jest jednym znakiem\n");
	    printf("-w: Okresla jak program zapisze wyniki dzialania. Argument moze byc 0, 1 lub 2.\n");
	    printf("Dla -w 0: Program wypisze wynik dzialania na ekran\n");
	    printf("Dla -w 1: Program wypisze wynik dzialania do pliku tekstowego\n");
	    printf("Dla -w 2: Program zapisze wynik dzialania do pliku .gif");
	    break;
        }
    }

    grid_t first_grid;
    grid_t second_grid;
    dimension_t static_dimension;

    read_dimension( fileIn, &static_dimension, &syms);

    init_grid( &first_grid, &static_dimension, &syms );
    init_grid( &second_grid, &static_dimension, &syms );

    //WCZYTANIE PLIKU
    fill_in_grid(fileIn, &first_grid, &syms);

    delete_png_from_dir();

    //URUCHOMIENIE GRY
    generations_done = generate_all(count_generation, writeOpt, fileOut, &static_dimension, &first_grid, &second_grid, &syms);
    
    if(writeOpt == 2)
	    make_gif_command( delay, generations_done, gifFilename );
	    
    free_grid( first_grid, static_dimension );
    free_grid( second_grid, static_dimension );

    return 0;
}
