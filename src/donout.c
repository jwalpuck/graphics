/*
This is an image of a donout or nucleus but really it is just me really 
really happy that my ellipse rotates!! 


September 25, 2014
Graphics CS 351
 -----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"


int main(int argc, char *argv[]){
  Image *src;
  Ellipse elip;
  Color color;
  Point p;
  double alpha;
  int i;

  src = image_create( 400,400); 

  for(i = 0; i<360; i=i+45){
    alpha = sin(i);
    printf("%f\n", alpha);
    color_set(&color, 1.0*(1.0-alpha), 1.0*alpha, 1.0);
    point_set2D( &p, 200, 200 );
    ellipse_set(&elip, p, 150, 70,1+i);
    ellipse_draw(&elip, src, color);
  }

  image_write(src, "donout3.ppm");
  image_free(src);
  return(0);

}
