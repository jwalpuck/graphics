/*
  This is is the library file for all functions dealing with polyline
 
  September 25, 2014
  CS 351 Graphics
 -----------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include "image.h"
#include "color.h"
#include "point.h"
#include "line.h"
#include "polyline.h"


Polyline *polyline_create(void) {
/* Returns an allocated Polyline pointer initialized so that numVertex is 0
   and vertex is NULL */
  Polyline *ret = malloc(sizeof(Polyline));
  ret->zBuffer = 1;
  ret->numVertex = 0;
  ret->vertex = NULL;

  return ret;
}


Polyline *polyline_createp(int numV, Point *vlist) {
/* Returns an allocated Polyline pointer with the vertex list initialized to
   the points in vlist */
  int i;
  Polyline *newPoly = malloc(sizeof(Polyline));
  newPoly->zBuffer = 1;
  newPoly->numVertex = numV;
  newPoly->vertex = malloc(sizeof(Point) * numV);

  for(i = 0; i < numV; i++) {
    newPoly->vertex[i] = vlist[i];
  }
  return newPoly;
}

void polyline_free(Polyline *p) {
/* Frees the internal data and the Polyline pointer */
  if(p)
    if(p->vertex)
      free(p->vertex);
    free(p);
}

void polyline_init(Polyline *p) {
/* Initialized the pre-existing Polyline to an empty Polyline */
  p->vertex = NULL;
  p->numVertex = 0;
  p->zBuffer = 1;
}

void polyline_set(Polyline *p, int numV, Point *vlist) {
/* Initializes the vertex list to the points in vlist. De-allocates/allocates
   the vertex list for p, as necessary */
  int i;
  if(p->vertex) {
    free(p->vertex);
  }
  p->vertex = malloc(sizeof(Point) * numV);
  for(i = 0; i < numV; i++) {
    p->vertex[i] = vlist[i];
  }
  p->numVertex = numV;
}


void polyline_clear(Polyline *p) {
/* Frees the internal data for a Polyline, if necessary, and sets numVertex to
   0 and vertex to NULL */
  if(p->vertex)
    free(p->vertex);
  p->numVertex = 0;
  p->vertex = NULL;
}

void polyline_zBuffer(Polyline *p, int flag) {
/* Sets the z-buffer flag to the given value */
  p->zBuffer = flag;
}

void polyline_copy(Polyline *to, Polyline *from) {
/* De-allocates/allocates space as necessary in the destination Polyline data
   structure and copies the vertex data from the source polyline (from) to the
   destination (to) */
  int i;
  int cpyV = from->numVertex;
  //If they do not have the same space allocated for vertex, make it so
  if(!(to->numVertex == cpyV)) {
    if(!to->vertex)
      free(to->vertex);
    to->vertex = malloc(sizeof(Point) * cpyV);
  }
  for(i = 0; i < cpyV; i++) {
    to->vertex[i] = from->vertex[i];
  }
  to->numVertex = from->numVertex;
}


/*normalize the x and y values of each vertex by the homogenous coordinate*/
void polyline_normalize( Polyline *p){
  int i; 
  for(i = 0; i<p->numVertex; i++){
    p->vertex[i].val[0] = p->vertex[i].val[0]/p->vertex[i].val[3];
    p->vertex[i].val[1] = p->vertex[i].val[1]/p->vertex[i].val[3];
  }
}

void polyline_print(Polyline *p, FILE *fp) { 
/* Prints Polyline data to the stream designated by the FILE pointer */
  int i;
  if(fp){
    fprintf(fp, "numVertex: %d    zBuffer: %d \n",p->numVertex,p->zBuffer);
    for( i =0; i< p->numVertex; i++){
      fprintf(fp, "| %.2f, %.2f, %.2f|\n", p->vertex[i].val[0], p->vertex[i].val[1], p->vertex[i].val[2]);
    }
  }
}


void polyline_draw(Polyline *p, Image *src, Color c) {
/* Draw the polyline using color c */
  int j;

  /* This is using the exact same algorithm that was used in line_draw. The 
     only difference is now we are looping through a list of verticies and we 
     are drawing a series of connected lines. But how we draw them is the same
     as the pervious function*/
  for(j = 0; j+1< p->numVertex; j++){
    int i;
    
    /*set the points (x,y) and (w,h) from the vertex list*/
    int x = (int)p->vertex[j].val[0];
    int y = (int)p->vertex[j].val[1];
    int w = (int)p->vertex[j+1].val[0] - x;
    int h = (int)p->vertex[j+1].val[1] - y;

    /*pick the corresponding dx values depending on the octant the line is in*/
    int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;
    if(w < 0) dx1 = -1; else if(w > 0) dx1 = 1;
    if(h < 0) dy1 = -1; else if(h > 0) dy1 = 1;
    if(w < 0) dx2 = -1; else if(w > 0) dx2 = 1;

    /*assume w is the longest*/
    int longest = abs(w);
    int shortest = abs(h);

    /* if the assumption above is false correct it*/
    if(!(longest > shortest)) {
      longest = abs(h);
      shortest = abs(w);
      if(h < 0) dy2 = -1; else if(h > 0) dy2 = 1;
      dx2 = 0;
    }

    /*bit wise shift of longest*/
    int numerator = longest >> 1;

    /*loop through and draw the points*/
    for(i = 0; i <= longest; i++) {
      image_setColor(src, y, x, c);
      numerator += shortest;
      if(!(numerator < longest)) {
	numerator -= longest;
	x += dx1;
	y += dy1;
      }
      else {
	x += dx2;
	y += dy2;
      }
    }
  }
}
