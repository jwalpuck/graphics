#ifndef POLYGON_H

#include "image.h"
#include "color.h"
#include "point.h"

#define POLYGON_H

typedef struct{
  int nVertex; // number of vertices
  Point *vertex; // vertex info
  int zBuffer; // whether to use zBuffer should default to true
}Polygon;

Polygon *polygon_create(void);

Polygon *polygon_createp(int numV, Point *vlist);

void polygon_free(Polygon *p);

void polygon_init(Polygon *p);

void polygon_set(Polygon *p, int numV, Point *vlist);

void polygon_clear(Polygon *p);

void polygon_zBuffer(Polygon *p, int flag);

void polygon_copy(Polygon *to, Polygon *from);

void polygon_print(Polygon *p, FILE *fp);

void polygon_normalize(Polygon *p);

void polygon_draw(Polygon *p, Image *src, Color c);

void polygon_drawFill(Polygon *p, Image *src, Color c);

void polygon_drawFillB(Polygon *p, Image *src, Color c);


#endif
