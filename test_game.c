#include <stdio.h>
#include <stdlib.h>

 char is_alive( int i, int j, char **ptr, )
{
    int alive_number = 0;
    for(int a=-1; a<2; a++)
    {
        for(int b=-1; b<2; b++)
            if(ptr[i+a][j+b] == '1')
                alive_number++;
    }

    if(ptr[i][j] == '1')
    {
        alive_number--;
        if(alive_number == 2 || alive_number == 3)
            return '1';
        else
            return '0';
    }
    else
    {
        if(alive_number == 3)
            return '1';
        else
            return '0';
    }
}

int main( void )
{
    grid_t main_grid = { {'0', '0', '0', '0', '0'}; {'0', '0', '1', '0', '0'}; {'0', '0', '1', '0', '0'}; {'0', '0', '1', '0', '0'}; {'0', '0', '0', '0', '0'} }
    grid_t util_grid = { {'0', '0', '0', '0', '0'}; {'0', '0', '0', '0', '0'}; {'0', '0', '0', '0', '0'}; {'0', '0', '0', '0', '0'}; {'0', '0', '0', '0', '0'} }
    char **ptr = (char*)malloc( 5 * sizeof(char*));
    for(int i = 0; i < 5; i++)
        ptr[i] = &(main_grid->cells[i][0]);

    for(int i = 1; i < 4; i++)
        {
            for(int j = 1; j < 4; j++)
                util_grid->cells[i][j] = is_alive(i, j, ptr );
        }

    return 0;
}
