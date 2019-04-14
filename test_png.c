#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <png.h>

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


int x, y;

int width, height;
png_byte color_type;
png_byte bit_depth;

png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep * row_pointers;

void make_png(char* file_name) {
  FILE *fp = fopen(file_name, "wb");
  if (!fp)
    printf("[write_png_file] File %s could not be opened for writing", file_name);

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr)
    printf("[write_png_file] png_create_write_struct failed");

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
    printf("[write_png_file] png_create_info_struct failed");

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during init_io");

  png_init_io(png_ptr, fp);

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during writing header");

  png_set_IHDR(png_ptr, info_ptr, width, height,
   bit_depth, color_type, PNG_INTERLACE_NONE,
   PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_write_info(png_ptr, info_ptr);

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during writing bytes");

  png_write_image(png_ptr, row_pointers);

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during end of write");

  png_write_end(png_ptr, NULL);

  png_destroy_write_struct(&png_ptr, &info_ptr);

  for (int i = 0; i < height - 9; i +=10)
    free(row_pointers[i]);
  free(row_pointers);

  fclose(fp);
}
void describe_png(grid_t *util_grid, dimension_t *dim, symbols_t *syms)
{
  width = (dim->columns - 2)  * 10;
  height = (dim->rows - 2) * 10;
  bit_depth = 8;
  color_type = PNG_COLOR_TYPE_GRAY;
  number_of_passes = 7;
  row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
  for (y=0; y<height - 9; y += 10)
  {
    row_pointers[y] = (png_byte*) malloc(sizeof(png_byte) * width);
    if(row_pointers[y] == NULL)
    {
	printf("Blad przy alokacji pamieci");
    	return;
    }
  }
  if(row_pointers == NULL)
  {
    printf("Blad przy alokacji pamieci");
    return;
  }
  int i = 1;
  int j = 1;
  for(y=0; y<height - 9; y += 10)
  {
    png_byte* row = row_pointers[y];
    j = 1;
    for (x = 0; x < width - 9; x += 10)
    {
       if( util_grid->cells[i][j] == syms->alive)
       {
	  row[x] = 255;
       }
       else
       {
	  row[x] = 0;
       }
       for(int a = 1; a < 10; a++)
       {
	  row[x + a] = row[x];
       }
       j++;
    }
    for(int a = 1; a < 10; a++)
    {
       row_pointers[y + a] = row_pointers[y];
    }
    i++;
  }
}


void  png(grid_t *util_grid, dimension_t *dim, symbols_t *syms, int n)
{
  char numberOfFile[100];
  sprintf(numberOfFile, "./Obrazy_PNG/Obraz%d_TEST.png", n);
  describe_png(util_grid, dim, syms);
  make_png(numberOfFile);
}
int main()
{
	grid_t table;
	dimension_t dim;
	symbols_t syms;

	int n = 1;

	dim.rows = 42;
	dim.columns = 62;

	syms.alive = '1';
	syms.dead = '0';

	table.cells = (char**)malloc(dim.rows * sizeof(char*));
   	for(int i = 0; i < dim.rows; i++)
        	table.cells[i] = (char*)malloc(dim.columns * sizeof(char));
	
	
	for(int i = 1; i < dim.rows-1; i++)
	{
		for(int j =1; j < dim.columns-1; j++)
		{
			if((i + j) % 2 == 0)
				table.cells[i][j] = '1';
			else
				table.cells[i][j] = '0';
		}
	}

	png(&table, &dim, &syms, n);

	for( int i = 0;  i < dim.rows; i++ )
        	free( table.cells[i] );
	free( table.cells );
    	table.cells = NULL;
	
	printf("Jeżeli w folderze Obrazy_PNG powstał plik Obraz1_TEST.png\no wymiarach 600x400 pikseli i przedstawia szachownice\nto test możemy uznać za pomyslny!\n");

	return 0;
}
