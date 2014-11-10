/*
  Bruce A. Maxwell
  fall 2013
  Test of the image library functions
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"

int main(int argc, char *argv[]) {
  printf("HI\n");
  Image *src;
  FPixel p = { {0.2, 1.0, 1.0}, 0.0, 1.0};
  int rows = 300;
  int cols = 400;
  int i, j;
  printf("start of code\n");
  // initialize an image

  src = image_create(rows, cols);

  printf("put in colors\n");
  // fill it with colors
  for(i=0;i<rows;i++) {
    for(j=0;j<cols;j++) {
      image_setc( src, i, j, 0, fabs( ((float)(i-rows/2)) / (rows/2) ) );
      image_setc( src, i, j, 1, fabs( ((float)(j-cols/2)) / (cols/2) ) );
      image_setc( src, i, j, 2, ((float)(i+j)) / (rows + cols) );
    }
  }

  // write it out
  printf("write out file\n");
  image_write( src, "colors.ppm");

  // free it
  printf("free image\n");
  image_free( src );
  if (src == NULL)
    printf("it made it null\n");
  else
    printf("it did not make it null\n");

  printf("create image\n");
  src = image_create(0, 0);
  rows = 712;
  cols = 1072;

  printf("allocate image\n");
  printf("%d\n", src->rows);
  printf("%d\n", src->cols);
  image_alloc( src, rows, cols );

  printf("%d\n", src->rows);
  printf("%d\n", src->cols);

  printf("reset image\n");
  image_reset( src );
  printf("%d\n", src->rows);
  printf("%d\n", src->cols);

  printf("write out image\n");
  image_write( src, "black.ppm");

  printf("set f\n");
  printf("%d\n", rows);
  printf("%d\n", cols);
  for(i=0;i<rows;i++) {
    for(j=0;j<cols;j++) {
      image_setf( src, i, j, p );
    }
  }
  printf("%d\n", src->rows);
  printf("%d\n", src->cols);
  printf("write image\n");
  image_write( src, "skyblue.ppm" );
  
  printf("deallocate image\n");
  image_dealloc(src);

  printf("free image\n");
  image_free( src );
  printf("DONE\n");

  return(0);
}
