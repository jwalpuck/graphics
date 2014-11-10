/*
  This is a library of functions for a line

  September 25, 2014
  Graphics CS 351
 -----------------------------------------------------------------------------*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "image.h"
#include "color.h"
#include "point.h"
#include "line.h"

void line_set2D(Line *l, double x0, double y0, double x1, double y1) {
/* Initialize a 2D line */
  Point p0; 
  Point p1; 
  
  /*all of these are static, no mallocing :)*/
  point_set2D(&p0, x0, y0);
  point_set2D(&p1, x1, y1);
  l->a = p0;
  l->b = p1;
  l->zBuffer = 1;
}


void line_set(Line *l, Point ta, Point tb) {
/* Initialize a line to points ta and tb */
  l->a = ta;
  l->b = tb;
  l->zBuffer = 1;
}

void line_zBuffer(Line *l, int flag) {
/* Set the z-buffer flag to the given value */
  l->zBuffer = flag;
}

void line_copy(Line *to, Line *from) {
/* Copy the line data structure */
/*you need to have * because you want to be able to cope the data
  at the pointer to and not just have two pointers pointing to the
  same space in memory*/
  *to = *from;
}

void line_draw(Line *l, Image *src, Color c) {
/* Draw the line into src using color c */
  int i;
  /*getting the (x,y) (w,h) point values from the line from the line*/
  int x = (int)l->a.val[0];
  int y = (int)l->a.val[1];
  int w = (int)l->b.val[0] - x;
  int h = (int)l->b.val[1] - y;
  
  /*set dx1, dy1, dx2, dy2: these values will help put us in the correct
    octant, begin by initalizing all values to 0*/
  int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;
  /*now check where the second point is positioned and change the dx, dy 
    values accordingly*/
  if(w < 0) dx1 = -1; else if(w > 0) dx1 = 1;
  if(h < 0) dy1 = -1; else if(h > 0) dy1 = 1;
  if(w < 0) dx2 = -1; else if(w > 0) dx2 = 1;
  
  /*assume that w is larger than h(or the x axis value is larger than the y
   axis value*/
  int longest = abs(w);
  int shortest = abs(h);

  /*check your assumption, if it does not hold then correct the values (if 
   y axis value is longer than x axis value*/
  if(!(longest > shortest)) {
    longest = abs(h);
    shortest = abs(w);
    if(h < 0) dy2 = -1; else if(h > 0) dy2 = 1;
    dx2 = 0;
  }

  /* apply a bit shift to longest, this essentially divides it by 2(small 
   increments)*/
  int numerator = longest >> 1;
  
  /*loop through the value longest, increment x and y appropriatley(using
   your determined dx, dy values from above to find the octant you are
   in and color the pixel*/
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

void line_normalize(Line *l){
  /*normalize the x and y values of both points a and b by the homegenous coordinate*/
  //Point A
  l->a.val[0] = l->a.val[0]/l->a.val[3];
  l->a.val[1] = l->a.val[1]/l->a.val[3];
  l->a.val[3] = l->a.val[3]/l->a.val[3];

  //Point B
  l->b.val[0] = l->b.val[0]/l->b.val[3];
  l->b.val[1] = l->b.val[1]/l->b.val[3];
  l->b.val[3] = l->b.val[3]/l->b.val[3];
}
