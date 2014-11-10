#ifndef LINE_H

#include "image.h"
#include "color.h"
#include "point.h"

#define LINE_H

typedef struct {
  int zBuffer;
  Point a;
  Point b;
} Line;

/* Initialize a 2D line */
void line_set2D(Line *l, double x0, double y0, double x1, double y1);

/* Initialize a line to ta and tb */
void line_set(Line *l, Point ta, Point tb);

/* Set the z-buffer flag to the given value */
void line_zBuffer(Line *l, int flag);

/* Copy the line data structure */
void line_copy(Line *to, Line *from);

/* Draw the line into src using color c */
void line_draw(Line *l, Image *src, Color c);

/*normalize the line*/
void line_normalize(Line *l);

#endif
