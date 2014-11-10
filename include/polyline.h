#ifndef POLYLINE_H

#include "image.h"
#include "color.h"
#include "point.h"
#include "line.h"

#define POLYLINE_H

typedef struct {
  int zBuffer;
  int numVertex;
  Point *vertex;
} Polyline;

/* Returns an allocated Polyline pointer initialized so that numVertex is 0
   and vertex is NULL */
Polyline *polyline_create(void);

/* Returns an allocated Polyline pointer with the vertex list initialized to
   the points in vlist */
Polyline *polyline_createp(int numV, Point *vlist);

/* Frees the internal data and the Polyline pointer */
void polyline_free(Polyline *p);

/* Initialized the pre-existing Polyline to an empty Polyline */
void polyline_init(Polyline *p);

/* Initializes the vertex list to the points in vlist. De-allocates/allocates
   the vertex list for p, as necessary */
void polyline_set(Polyline *p, int numV, Point *vlist);

/* Frees the internal data for a Polyline, if necessary, and sets numVertex to
   0 and vertex to NULL */
void polyline_clear(Polyline *p);

/* Sets the z-buffer flag to the given value */
void polyline_zBuffer(Polyline *p, int flag);

/* De-allocates/allocates space as necessary in the destination Polyline data
   structure and copies the vertex data from the source polyline (from) to the
   destination (to) */
void polyline_copy(Polyline *to, Polyline *from);

/*normalize the x and y values of each vertex by the homogenous coordinate*/
void polyline_normalize( Polyline *p);

/* Prints Polyline data to the stream designated by the FILE pointer */
void polyline_print(Polyline *p, FILE *fp);

/* Draw the polyline using color c */
void polyline_draw(Polyline *p, Image *src, Color c);


#endif
