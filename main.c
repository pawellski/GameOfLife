#include <stdio.h>
#include <stdlib.h>

#include "Struct.h"

int main(int argc, char **argv)
{
    grid_t first_grid;
    grid_t second_grid;
    dimension_t static_dimension;

    int count_generation = atoi(argv[2]);

    read_dimension(argv[1], &static_dimension);

    printf("Bez bufora\nWiersze: %d\nKolumny: %d\n", (static_dimension.rows)-2, (static_dimension.columns)-2);
    printf("Z buforem\nWiersze: %d\nKolumny: %d\n", static_dimension.rows, static_dimension.columns);

    //ALOKACJA PAMIECI
    first_grid.cells = (char**)malloc(static_dimension.rows * sizeof(char*));
    second_grid.cells = (char**)malloc(static_dimension.rows * sizeof(char*));
    for(int i = 0; i < static_dimension.rows; i++)
    {
        first_grid.cells[i] = (char*)malloc(static_dimension.columns * sizeof(char));
        second_grid.cells[i] = (char*)malloc(static_dimension.columns * sizeof(char));
    }


    //WCZYTANIE PLIKU
    fill_in_grid(argv[1], &first_grid);

    //WYSWIETLENIE WCZYTANEJ PLANSZY
    print(&first_grid, &static_dimension);
	
    //WYCZYSZCZENIE PLANSZY
    to_clear(&second_grid, &static_dimension);
	
    // WYŒWIETLENIE PLANSZY
    printf("Wyczyszczony plik\n");
   
   //WYSWIETLENIE WCZYTANEJ PLANSZY
    print(&second_grid, &static_dimension);

    //URUCHOMIENIE GRY
    generation(count_generation, &static_dimension, &first_grid, &second_grid);

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
