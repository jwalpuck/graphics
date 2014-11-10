/*
I am going to try and draw a minion!! 

October 2, 2014
Graphics CS 351 
 -----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

int main(int argc, char *argv[]){
  Image *src; 
  const int rows = 700; 
  const int cols = 500; 
  Ellipse elip;
  Circle circ; 
  Color white, yellow, blue,red, brown, gray, black, sky, green;
  Point p;
  Point pt[5];
  Polygon *poly;
  Polyline *pline;
  Line l;
  int i,j;

  color_set(&yellow, 1.0, 1.0, 0.2);
  color_set(&blue, 0.0, 0.2, 0.4);
  color_set(&red, 1.0,0.0, 0.0);
  color_set(&brown, 0.2, 0.1, 0.0);
  color_set(&white, 1.0, 1.0, 1.0);
  color_set(&gray, 0.17, 0.17, 0.17);
  color_set(&black, 0.0, 0.0, 0.0);
  color_set(&sky,0.4 ,0.6 , 1.0);


  color_set(&green, 0.0, 0.4, 0.0);

  src = image_create(rows, cols);

  for(i = 0; i< rows; i++) {
    for(j = 0; j<cols; j++){
      image_setColor(src, i, j, sky);
    }
  }

  point_set2D(&(pt[0]), 0, rows-1);
  point_set2D(&(pt[1]), 200, 600 );
  point_set2D(&(pt[2]),300, 600  );

  point_set2D(&(pt[3]),rows-1, rows-1 );

  poly = polygon_createp(4, pt);
  polygon_drawFill(poly,src, green);

  point_set2D(&p, 650, 250);
  ellipse_set(&elip, p, 10, 45, 0);
  ellipse_drawFill(&elip, src, gray);

  color_set(&gray, 0.37, 0.37, 0.37);
  
  /*body*/
  point_set2D(&p, 450, 250);
  ellipse_set(&elip, p, 130, 95,0);
  ellipse_drawFill(&elip, src, yellow);

  point_set2D(&p, 250, 490);
  circle_set(&circ, p, 10);
  circle_drawFill(&circ, src, black);

  /*arms*/
  point_set2D(&(pt[0]), 337, 505);
  point_set2D(&(pt[1]), 352, 435 );
  point_set2D(&(pt[2]), 357, 435 );
  point_set2D(&(pt[3]), 352, 505 );

  poly = polygon_createp(4, pt);
  polygon_drawFill(poly,src, yellow);

  point_set2D(&(pt[0]), 148, 505);
  point_set2D(&(pt[1]), 163, 545 );
  point_set2D(&(pt[2]), 168, 545 );
  point_set2D(&(pt[3]), 163, 505 );

  poly = polygon_createp(4, pt);
  polygon_drawFill(poly,src, yellow);

  /*legs*/
  point_set2D(&(pt[0]), 285, 620);
  point_set2D(&(pt[1]), 265, 620);
  point_set2D(&(pt[2]), 265, 570);
  point_set2D(&(pt[3]), 285, 570);

  poly = polygon_createp(4, pt);
  polygon_drawFill(poly,src, yellow);

  point_set2D(&(pt[0]), 235, 610);
  point_set2D(&(pt[1]), 215, 610);
  point_set2D(&(pt[2]), 215, 570);
  point_set2D(&(pt[3]), 235, 570);

  poly = polygon_createp(4, pt);
  polygon_drawFill(poly,src, yellow);

  point_set2D(&p, 225, 620);
  circle_set(&circ, p, 15);
  circle_drawFill(&circ, src, brown);

  point_set2D(&p, 275, 610);
  circle_set(&circ, p, 15);
  circle_drawFill(&circ, src, brown);

  point_set2D(&(pt[0]), 165, 505);
  point_set2D(&(pt[1]), 335, 505);
  point_set2D(&(pt[2]), 340, 550);
  point_set2D(&(pt[3]), 275, 590);
  point_set2D(&(pt[4]), 215, 590);
  point_set2D(&(pt[5]), 165, 550);

  poly = polygon_createp(6, pt);
  polygon_drawFill(poly,src, blue);

  /*eye*/
  point_set2D(&(pt[0]),345, 425 );
  point_set2D(&(pt[1]), 155, 425);
  point_set2D(&(pt[2]), 155, 410 );
  point_set2D(&(pt[3]), 345, 410 );

  poly = polygon_createp(4, pt);
  polygon_drawFill(poly,src,gray);

  point_set2D(&p, 250, 420);
  circle_set(&circ, p, 25);
  circle_drawFill(&circ, src, gray);

  circle_set(&circ, p, 20);
  circle_drawFill(&circ, src, white);

  point_set2D(&p, 250, 425);
  circle_set(&circ, p, 8);
  circle_drawFill(&circ, src, blue);

  point_set2D(&p, 250, 427);
  circle_set(&circ, p, 3);
  circle_drawFill(&circ, src, black);

  /*hair*/
  
  line_set2D(&l, 250,320, 230, 308);
  line_draw(&l,src, black);
  line_set2D(&l, 250, 320, 250, 310);
  line_draw(&l,src, black);
  line_set2D(&l, 250, 320, 260, 290);
  line_draw(&l,src, black);

  /*balloon*/
  point_set2D(&(pt[0]), 357, 435 );
  point_set2D(&(pt[1]), 400 , 395);
  point_set2D(&(pt[2]), 295, 234);
  point_set2D(&(pt[3]), 327, 196);
  pline = polyline_createp(10, &(pt));
  polyline_set(pline, 4, &(pt));
  polyline_draw(pline, src, white);


  point_set2D(&(pt[0]),285, 160 );
  point_set2D(&(pt[1]), 285, 240);
  point_set2D(&(pt[2]), 330, 205 );

  poly = polygon_createp(3, pt);
  polygon_drawFillB(poly,src, red);

  point_set2D(&p, 327,170);
  circle_set(&circ, p, 65);
  circle_drawFill(&circ, src, red);

  printf("writing output\n");
  image_write(src, "minion.ppm");
  polyline_free(pline);
  polygon_free(poly);
  image_free(src);

  return(0);
}
