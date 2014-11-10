/* 
  This is a library of functions for a point

  September 25, 2014
  Graphics CS 351
 -----------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include "point.h"
#include "image.h"
#include "color.h"


/* Sets values of the vector to [x, y, 0.0, 1.0] */
void point_set2D(Point *p, double x, double y) {
  p->val[0] = x;
  p->val[1] = y;
  p->val[2] = 0.0;
  p->val[3] = 1.0;
}
/* Sets values of the vector to [x, y, z, 1.0] */
void point_set3D(Point *p, double x, double y, double z) {
  p->val[0] = x;
  p->val[1] = y;
  p->val[2] = z;
  p->val[3] = 1.0;
}


/* Sets values of vector to [x, y, z, h] */
void point_set(Point *p, double x, double y, double z, double h) {
  p->val[0] = x;
  p->val[1] = y;
  p->val[2] = z;
  p->val[3] = h;
}

/* Copy the point data structure */
void point_copy(Point *to, Point *from) {
  *to = *from;
}
/* Draw the point into src using color c */
void point_draw(Point *p, Image *src, Color c) {
  image_setColor(src, p->val[1], p->val[0], c);
}
/* Draw the point into src using FPixel c */
void point_drawf(Point *p, Image *src, FPixel c) {
  image_setf(src, p->val[1], p->val[0], c);
}

/*normalize a point by its homeogenous coordinate*/
void point_normalize(Point *p){
  p->val[0] = p->val[0]/p->val[3];
  p->val[1] = p->val[1]/p->val[3]; 
}

/*print out the point data*/
void point_print(Point *p, FILE *fp){
  fprintf(fp, "[%.3f, %.3f, %.3f, %.3f]\n", p->val[0], p->val[1], p->val[2], p->val[3]);
}
