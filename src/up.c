/*
I am going to do an interpretation of the floating house in up from a ground
viewers prespective. 

October 2, 2014
Graphics CS 351
 -----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

int main(int argc, char *argv[]){
  Image *src; 
  const int rows = 500; 
  const int cols = 500; 
  Circle circ; 
  Color white, yellow, blue,red, sky;
  Point p;
  Point pt[50];
  Polygon *poly;
  int i,j;

  color_set(&yellow, 1.0, 1.0, 0.2);
  color_set(&blue, 0.0, 0.2, 0.4);
  color_set(&red, 0.2,0.0, 0.0);
  color_set(&white, 1.0, 1.0, 1.0);
  color_set(&sky,0.4 ,0.6 , 1.0);

  src = image_create(rows, cols);

 for(i = 0; i< rows; i++) {
    for(j = 0; j<cols; j++){
      image_setColor(src, i, j, sky);

    }
  }

  for(i=0;i<50;i++) {
    float dr = rand() % 15;
    
    point_set2D(&(pt[i]), dr, dr+10);
      circle_set(&circ, pt[i] , 10);
      circle_drawFill(&circ, src, white);

  }



 point_set2D(&(pt[0]), 210, 340);
 point_set2D(&(pt[1]), 280, 340 );
 point_set2D(&(pt[2]), 280, 410 );
 point_set2D(&(pt[3]), 210, 410 );

 poly = polygon_createp(4, pt);
 polygon_drawFill(poly,src, red);

 color_set(&yellow, 0.8, 0.8, 0.0);
 point_set2D(&(pt[0]), 215, 345);
 point_set2D(&(pt[1]), 275, 345 );
 point_set2D(&(pt[2]), 275, 405 );
 point_set2D(&(pt[3]), 215, 405 );

  poly = polygon_createp(4, pt);
  polygon_drawFill(poly,src, yellow);

  printf("writing output\n");
  image_write(src, "minion.ppm");

  image_free(src);

  return(0);
}
