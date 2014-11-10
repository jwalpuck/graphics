/*
This is an image with inspiration from picasso.

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
  const int cols = 350; 
  Ellipse elip;
  Circle circ; 
  Color white, yellow, red, blue, pink,green;
  Point pt[10];
  Point p;
  Polygon *poly;
  int i;

  color_set(&yellow, 1.0, 1.0, 0.2 );
  color_set(&red, 0.8, 0.0, 0.0);
  color_set(&blue, 0.0, 0.5, 1.0);
  color_set(&green, 0.3,0.6, 0.0);
  color_set(&pink,1.0, 0.4, 0.69 );
  color_set(&white, 1.0, 1.0, 1.0);

  src = image_create(rows, cols);

  point_set2D(&(pt[0]), 10, 10);
  point_set2D(&(pt[1]), 233, 10);
  point_set2D(&(pt[2]), 97, 255);
  point_set2D(&(pt[3]), 187, 345);
  point_set2D(&(pt[4]), 82, 455);
  point_set2D(&(pt[5]), 233, 490);
  point_set2D(&(pt[6]), 10, 490);

  poly = polygon_createp(7,pt);
  polygon_drawFill(poly, src, blue);

  point_set2D(&p, 136, 270);
  ellipse_set(&elip, p, 25, 35,0);
  ellipse_drawFill(&elip, src, white);

  color_set(&blue, 0.0, 0.0, 1.0);
  point_set2D(&p, 270, 136);
  circle_set(&circ, p, 15);
  circle_drawFill(&circ, src, blue);

  point_set2D(&p, 295, 74);
  ellipse_set(&elip, p, 40, 30,0);
  ellipse_drawFill(&elip, src, white);

  color_set(&blue, 0.0, 0.0, 1.0);
  point_set2D(&p, 74, 295);
  circle_set(&circ, p, 15);
  circle_drawFill(&circ, src, green);

  point_set2D(&p, 430, 260);
  ellipse_set(&elip, p, 20, 70,0);
  ellipse_drawFill(&elip, src, red);

  point_set2D(&(pt[0]), 150, 125);
  point_set2D(&(pt[1]), 160, 125);
  point_set2D(&(pt[2]), 160, 300);
  point_set2D(&(pt[3]), 150, 300);
  
  poly = polygon_createp(4,pt);
  polygon_drawFill(poly, src, yellow);

  point_set2D(&(pt[0]), 150, 290);
  point_set2D(&(pt[1]), 150, 300);
  point_set2D(&(pt[2]), 200, 300);
  point_set2D(&(pt[3]), 200, 290);
  
  poly = polygon_createp(4,pt);
  polygon_drawFill(poly, src, yellow);
  
  for(i= 0; i<150; i= i+50){
    point_set2D(&(pt[0]), 50+i, 100);
    point_set2D(&(pt[1]), 100+i, 20);
    point_set2D(&(pt[2]), 150+i, 25);

    poly = polygon_createp(3,pt);
    polygon_drawFillB(poly, src, pink);
  }

  printf("writing output\n");
  image_write(src, "face.ppm");
  polygon_free(poly);
  image_free(src);

  return(0);


}
