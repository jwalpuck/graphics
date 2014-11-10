#ifndef IMAGE_H

#include "color.h"

#define IMAGE_H

typedef struct{
  float rgb[3];
  float a;
  float z;
}FPixel;

typedef struct{
  FPixel **data;
  int rows;
  int cols;
}Image;

/*CONSTRUCTORS AND DESTRUCTORS*/
Image *image_create(int rows, int cols);

void image_free(Image *src);

void image_init(Image *src);

int image_alloc(Image *src, int rows, int cols);

void image_dealloc(Image *src);

/*I/O FUNCTIONS*/

Image *image_read(char *filenam);

int image_write(Image *src, char *filename);

/*ACCESS*/

FPixel image_getf(Image *src, int r, int c);

float image_getc(Image *src, int r, int c, int b);

float image_geta(Image *src, int r, int c);

float image_getz(Image *src, int r, int c);

Color image_getColor(Image *src, int r, int c);

void image_setf(Image *src, int r, int c, FPixel val);

void image_setc(Image *src, int r, int c, int b, float val);
 
void image_seta(Image *src, int r, int c, float val);

void image_setz(Image *src, int r, int c, float val);

void image_setColor(Image *src, int r, int c, Color val);

/*UTILITY*/
void image_reset(Image *src);

void image_fill(Image *src, FPixel val);

void image_fillrgb(Image *src, float r, float g, float b);

void image_filla(Image *src, float a);

void image_fillz(Image *src, float z);

/*FRACTLES!*/
void mandelbrot( Image *dst, float x0, float y0, float dx, int r, int g, int b);

void julia(Image *dst, float x0, float y0, float dx, float c1, float c2, int r, int g, int b);

void noise(Image *src, float theta, int type);

void speckle(Image *src, int density);

#endif
