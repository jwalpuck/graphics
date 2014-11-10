/* 

This is the library of functions for a polygon!

October 2, 2014
Graphics CS351
------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"
#include "color.h"
#include "point.h"
#include "polygon.h"

Polygon *polygon_create(void){
/*return an allocated Polygon pointer initalized so that numBertex is
  0 and vertex is Null*/
   Polygon *ret = malloc(sizeof(Polygon));
   ret->nVertex = 0;
   ret->zBuffer = 1;
   ret->vertex = NULL;

   return ret;
}

Polygon *polygon_createp(int numV, Point *vlist){
  /*returns an allocated Polygon pointer with the vertex list initalized 
   to a copy of the points in vlist*/
  int i; 
  Polygon *newPolygon = malloc(sizeof(Polygon));
  newPolygon->nVertex = numV;
  newPolygon->zBuffer = 1;
  newPolygon->vertex = malloc(sizeof(Point)*numV);

  for(i=0; i<numV; i++){
    newPolygon->vertex[i] = vlist[i];
  }
  return newPolygon;
}

void polygon_free(Polygon *p){
  /*frees the internal data for a Polygon and the Polygon Pointer*/
  if (p)
    if(p->vertex)
      free(p->vertex);
    free(p);
}

void polygon_init(Polygon *p){
/*initializes the existing Polygon to an empty Polygon*/
  p->vertex = NULL;
  p->nVertex = 0;
  p->zBuffer = 1.0;
}

void polygon_set(Polygon *p, int numV, Point *vlist){
  /*initializes the vertex array to the points in vlist*/
  int i;
  if(p->vertex){
    free(p->vertex);
  }
  p->vertex = malloc(sizeof(Point)*numV);
  for(i=0; i<numV; i++){
    p->vertex[i] =vlist[i]; 
  } 
  p->nVertex = numV;
}

void polygon_clear(Polygon *p){
  /*frees the internal data and resets the fields*/
  if(p->vertex){
    free(p->vertex);
  }
  p->vertex=NULL;
  p->nVertex = 0;
}

void polygon_zBuffer(Polygon *p, int flag){
  /*sets the z-buffer flag to the given value*/
  p->zBuffer = flag;
}

void polygon_copy(Polygon *to, Polygon *from){
  /*De-allocates/allocates space and copies the vertex and color data 
  from one polygon to another*/
  int i;
  int numVertex = from->nVertex;
  if(!(to->nVertex == numVertex)){
    if(to->vertex) {
      free(to->vertex); 
    }
    to->vertex = malloc(sizeof(Point)*numVertex);
    to->nVertex = numVertex;
  }

  for(i=0;i<numVertex; i++){
    to->vertex[i] = from->vertex[i];
  }

  to->zBuffer = from->zBuffer;
}

void polygon_print(Polygon *p, FILE *fp){
  /*prints polygon data to the stream designated by the FILE pointer*/
  int i;
  if(fp){
    fprintf(fp, "numVertex: %d    zBuffer: %d \n",p->nVertex,p->zBuffer);
    for( i =0; i< p->nVertex; i++){
      fprintf(fp, "| %.2f,  %.2f, %.2f | \n", p->vertex[i].val[0], p->vertex[i].val[1], p->vertex[i].val[2]);
    }
  }
}

void polygon_normalize(Polygon *p){
  /*normalize the x and y values of each vertex by the homogeneous coordinates*/
  int i; 
  for(i = 0; i<p->nVertex; i++){
    p->vertex[i].val[0] = p->vertex[i].val[0]/p->vertex[i].val[3];
    p->vertex[i].val[1] = p->vertex[i].val[1]/p->vertex[i].val[3];
  }
}

void polygon_draw(Polygon *p, Image *src, Color c){
  /*draw the outline of the polygon using color c*/
  int j;

  /* This is using the exact same algorithm that was used in line_draw. The 
     only difference is now we are looping through a list of verticies and we 
     are drawing a series of connected lines. But how we draw them is the same
     as the pervious function*/
  for(j = 0; j+1< p->nVertex; j++){
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
  int i;
    
  /*set the points (x,y) and (w,h) from the vertex list*/
  int x = (int)p->vertex[p->nVertex-1].val[0];
  int y = (int)p->vertex[p->nVertex-1].val[1];
  int w = (int)p->vertex[0].val[0] - x;
  int h = (int)p->vertex[0].val[1] - y;

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

/* void polygon_drawFill(Polygon *p, Image *src, Color c){ */
  //This method is actually in scanlineSkeleton this is the basic outline 
  // of the algorithm! 
  /*Algorithm
    - process points -> edges {ymax, yend, dxPerScan(slope, x1-x0/y1-y0),
        x-intersectt} 
        - only include non-horizontal edges (dx != 0)
    - get all the edges in an ordered edge list, ordered based on y-start val
    - LOOP through the scanlines (j = yStart; j< yMax; j++)
       - update the Active Edge List(AEL), resort by x-intercept
         (What lines have y vales on current j line)
       - Fill the current scalline( for( c = start (x0); c< end (x1); c++)
          - fill in the right pixels
       - update the AEL           
           --> if yend == j then remove it from AEL
           --> update x-intercept ((int)x+(0.5*dxPerScan))
  */

void polygon_drawFillB(Polygon *p, Image *src, Color c){
/* draw the filled polygon using color c with the Barycentric coordinates algorithm*/
/*find max and min x and y values to define the bounding box*/
/*Loop through all the pixels in the bounding box*/
/*do the math to determine alpha, beta, and gamma*/
/*if any of alpha beta or gamma are less than 0 outside of the image*/
/*else if greater than or equal to 0*/
/*draw the pixel (you can use alpha beta and gamma as blend values in color)*/
/*NOTE: with floating points you cannot say == 0.0, instead you need to 
  define a constant ie: epillson = 0.000001*/
  
  const float epsilon = 0.00001;
  float ymax,yMax, yMin, ymin, xmax, xMax, xMin, xmin;
  float alpha, beta, gamma;
  float ax, ay, bx, by, gx, gy;
  int j,k;

  /*you will need each of these in the below calculations!!*/
  ax = p->vertex[0].val[0];
  ay = p->vertex[0].val[1];
  
  bx = p->vertex[1].val[0];
  by = p->vertex[1].val[1];
  
  gx =p->vertex[2].val[0];
  gy = p->vertex[2].val[1];

  /*find the min and max x and y values*/
  xMin = fmin(ax, bx);
  xmin = fmin(xMin,gx);
  yMin = fmin(ay, by);
  ymin = fmin(yMin, gy);

  xMax = fmax(ax, bx);
  xmax = fmax(xMax,gx);
  yMax = fmax(ay, by);
  ymax = fmax(yMax, gy);

  /*IF YOU NEED TO CHECK UNCOMMENT THESE*/
  /* printf("Point 1:%f %f\n", p->vertex[0].val[0], p->vertex[0].val[1]); */
  /* printf("Point 2:%f %f\n", p->vertex[1].val[0], p->vertex[1].val[1]); */
  /* printf("Point 3:%f %f\n", p->vertex[2].val[0], p->vertex[2].val[1]); */
  /* printf("xmax: %f xmin: %f\n", xmax, xmin); */
  /* printf("ymax: %f ymin: %f\n", ymax, ymin); */

  /*loop over the bonding box and determine which points are in the triangle*/
  for(j = ymin; j<ymax; j++){
    for(k = xmin; k<xmax; k++){
      float x = (float)k;
      float y = (float)j;
      beta = ((ay-gy)*x + (gx-ax)*y+ ax*gy - gx*ay)/ ((ay-gy)*bx + (gx-ax)*by+ax*gy - gx*ay);
      gamma = ((ay-by)*x + (bx-ax)*y+ ax*by - bx*ay)/ ((ay-by)*gx + (bx-ax)*gy+ax*by - bx*ay);
      alpha = 1 - beta - gamma; 
      if (alpha >= -epsilon &&  beta >= -epsilon && gamma >= -epsilon){
	/*set pixel*/    
	image_setColor(src, j,k, c);
      }
    }
  }
} 
