/*
  This is the library of functions for a circle!

September 25, 2014
Graphics CS 351
----------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "color.h"
#include "point.h"
#include "line.h"
#include "circle.h"

void circle_set(Circle *c, Point tc, double tr){
  /* initalize to center to tc and radius to  tr*/
  c->r = tr;
  c->c = tc;
}


void circle_draw(Circle *c, Image *src, Color p){
  /* draw the circle into src using color p*/
  /*Algorithm comes from circleMidpoint, Chapter 3, pg. 102*/

  double xCenter, yCenter, pz, x,y;
  xCenter = c->c.val[1];
  yCenter = c->c.val[0];
  x =-1;
  y = c->r*-1;
  pz = 1-(c->r); /*the very first "error" term simplified from 5/4-r*/

  /*Check*/
  printf("CenterX: %f, CenterY: %f\n", xCenter, yCenter);
  printf("Error term: %f\n", pz);

  /* the algorithm: 
        start at x = 0 and y = r;
	we are going to loop through 1/8th of a circle to find the points
	  and the rest of the points we will use the circles symmetry to 
	  plot
	compare x,y:
	   we will always decrement x
	   if p<0 (increment means point is in circle) :
	      go across increment p accordingly
	   else (p>0) (means point is not in circle)
	      increment y
	      go down a point increment p accordingly

	   use x and y while in loop to color in the appropriate pixels 
	     in all 8 sections
     Corrections: we will draw the circle in the third quadrant to help with the
     pixel shifting problem. 
*/
  
  /*set the initial color of the first 4 pixels and the first 8 reflected pixels*/
  image_setColor(src, xCenter+x, yCenter+y, p);
  image_setColor(src, xCenter-x, yCenter-y, p);
  image_setColor(src, xCenter-y, yCenter-x, p);
  image_setColor(src, xCenter+y, yCenter+x, p);

  image_setColor(src,xCenter+x, yCenter+y, p);
  image_setColor(src, xCenter-x-1, yCenter+y, p);
  image_setColor(src, xCenter+x, yCenter-y-1, p);
  image_setColor(src, xCenter-x-1, yCenter-y-1, p);

  image_setColor(src, xCenter+y, yCenter+x, p);
  image_setColor(src, xCenter-y-1, yCenter+x, p);
  image_setColor(src, xCenter+y, yCenter-x-1, p);
  image_setColor(src, xCenter-y-1, yCenter-x-1, p);
 
  printf("Drawing a Circle\n");
  while(x>=y){
    x--; // flipping orientation around so always decrementing x
    if (pz<0){
      pz+= 1-2*x;
    }else{
      y++; // if going up increase y...
      pz+= 1-2*(x-y-0.5);
    }

    /*COLOR PIXEL*/
    /*set the color in the opposite 4 quadrants of original findings*/
    image_setColor(src,xCenter+x, yCenter+y, p);
    image_setColor(src, xCenter-x-1, yCenter+y, p);
    image_setColor(src, xCenter+x, yCenter-y-1, p);
    image_setColor(src, xCenter-x-1, yCenter-y-1, p);

    /*set the color of the other half of the quadrant in all 4 quadrants*/
    image_setColor(src, xCenter+y, yCenter+x, p);
    image_setColor(src, xCenter-y-1, yCenter+x, p);
    image_setColor(src, xCenter+y, yCenter-x-1, p);
    image_setColor(src, xCenter-y-1, yCenter-x-1, p);
  }
  printf("YAY circle is drawn\n");
}


void circle_drawFill(Circle *c, Image *src, Color p){
  /* draw a filled circle into src using color p*/
  /*This is the same algorithm used above except for instead of drawing
    the points I am drawing lines between the corresponding quadrant points*/
  double xCenter, yCenter, pz, x,y, left;
  xCenter = c->c.val[0];
  yCenter = c->c.val[1];
  x =-1;
  y = c->r*-1;
  pz = 1-(c->r); /*the very first "error" term simplified from 5/4-r*/

  /*Check*/
  printf("CenterX: %f, CenterY: %f\n", xCenter+x, yCenter+y);
    left = x;
    while(left<-x){
      image_setColor(src,yCenter, xCenter+left,p);
      image_setColor(src,yCenter+y, xCenter+left,p);
      image_setColor(src,yCenter-y, xCenter+left,p);
      left++;
    }
    left =y;
    while(left<-y){
      image_setColor(src, yCenter, xCenter+left,p);
      image_setColor(src,yCenter+x, xCenter+left,p);
      image_setColor(src,yCenter-x, xCenter+left,p);
      left++;
    }  

  printf("Error term: %f\n", pz);
  printf("Drawing a Circle\n");
  /* this is the same algorithm as above with lines added to fill the circle*/
  while(x>y){
    x--; // flipping orientation around so always decrementing x
    if (pz<0){
      pz+= 1-2*x;
    }else{
      y++; // if going up increase y...
      pz+= 1-2*(x-y-0.5);
    }
    /*COLOR PIXEL*/
    /*draw lines between the points on opposite sides of the circle there
      will be 4*/				
    left = x;
    while(left<-x){
      image_setColor(src,yCenter+y, xCenter+left,p);
      image_setColor(src,yCenter-y, xCenter+left,p);
      left++;
    }
    left =y;
    while(left<-y){
      image_setColor(src,yCenter+x, xCenter+left,p);
      image_setColor(src,yCenter-x, xCenter+left,p);
      left++;
    }
  }
  printf("YAY circle is drawn\n");
}


