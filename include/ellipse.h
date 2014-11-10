#ifndef ELLIPSE_H

#include "image.h"
#include "color.h"
#include "point.h"
#include "line.h"

#define ELLIPSE_H

typedef struct{
  double ra; //major axis radius
  double rb; //minor axis radius
  Point c; //center
  double a; //angle of major axis relative to the X-axis
}Ellipse;

void ellipse_set(Ellipse *e, Point tc, double ta, double tb, double tan);

void ellipse_draw (Ellipse *e, Image *src, Color p);

void ellipse_drawFill(Ellipse *e, Image *src, Color p); 



#endif
