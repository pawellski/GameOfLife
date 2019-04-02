#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

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


#endif // STRUCT_H_INCLUDED
