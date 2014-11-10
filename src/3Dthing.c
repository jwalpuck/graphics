/*
This is my 3D shape. I am hoping it will look like a cupcake.

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
  Circle circ;
  Color color, red, pink, yellow;
  Color blue; 
  Line l;
  Point p;
  Point pt[5];
  Polygon *poly;
  int i;

  /*set the colors*/
  color_set(&color, 1.0, 1.0, 1.0);
  color_set(&red, 1.0, 0.0,0.0);
  color_set(&blue, 0.4,1.0,1.0);
  color_set(&pink, 1.0, 0.6, 0.8);
  color_set(&yellow, 1.0, 1.0, 0.4);

  /*build an image*/
  src = image_create( 700,700); 

  /*build the cupcake like I was using turtle graphics*/
  line_set2D(&l, 100,300,200,600);
  line_draw( &l, src, pink );

  line_set2D(&l, 600,300,500,600);
  line_draw( &l, src, pink );

  point_set2D( &p, 600, 350 );
  ellipse_set(&elip, p, 40, 150,0);
  ellipse_draw(&elip, src, pink);

  point_set2D( &p, 300,350 );
  ellipse_set(&elip, p, 80, 250,0);
  ellipse_draw(&elip, src, pink);

  point_set2D( &p, 275,350 );
  ellipse_set(&elip, p, 75, 225,0);
  ellipse_draw(&elip, src, blue);

  point_set2D( &p, 250,350 );
  ellipse_set(&elip, p, 50, 200,0);
  ellipse_draw(&elip, src, blue);

  point_set2D( &p, 225,350 );
  ellipse_set(&elip, p, 25, 175,0);
  ellipse_draw(&elip, src, blue);

  point_set2D( &p, 200,350 );
  ellipse_set(&elip, p, 20, 150,0);
  ellipse_draw(&elip, src, blue);

  point_set2D( &p, 175,350 );
  ellipse_set(&elip, p, 15, 125,0);
  ellipse_draw(&elip, src, blue);

  point_set2D( &p, 150,350 );
  ellipse_set(&elip, p, 5, 75,0);
  ellipse_draw(&elip, src, blue);

  point_set2D( &p, 350, 100 );
  circle_set( &circ, p, 25 );
  circle_draw( &circ, src, red);

  /*write image*/
  image_write( src, "3Dimage.ppm" );

  /*free image*/
  image_free( src );

  /*this time fill the cupcake*/

  src = image_create( 700,700); 

  color_set(&pink, 1.0, 0.6, 0.8);
  point_set2D( &p, 600, 350 );
  ellipse_set(&elip, p, 40, 150,0);
  ellipse_drawFill(&elip, src, pink);
  
  point_set2D(&(pt[0]),100 ,300);
  point_set2D(&(pt[1]),600 ,300);
  point_set2D(&(pt[2]),505 ,600);
  point_set2D(&(pt[3]),198, 600);
  
  poly = polygon_createp(4, pt);
  polygon_drawFill(poly,src, pink);

  color_set(&pink, 1.0, 0.4, 0.8);
  point_set2D( &p, 300,350 );
  ellipse_set(&elip, p, 80, 250,0);
  ellipse_drawFill(&elip, src, pink);

  color_set(&pink, 1.0, 0., 0.8);
  for(i=0; i<10; i++){
    line_set2D(&l, 100-i,300-i,200,600);
    line_draw( &l, src, pink );

    line_set2D(&l, 600-i,300-i,500,600);
    line_draw( &l, src, pink );

    line_set2D(&l, 175-i, 300-i, 225, 623);
    line_draw(&l, src, pink);

    line_set2D(&l, 275-i, 280-i, 305, 636);
    line_draw(&l, src, pink);

    line_set2D(&l, 385-i, 280-i, 385, 640);
    line_draw(&l, src, pink);

    line_set2D(&l, 510-i, 300-i, 450, 630);
    line_draw(&l, src, pink);

  }


  point_set2D( &p, 295,350 );
  ellipse_set(&elip, p, 70, 230,0);
  ellipse_drawFill(&elip, src, yellow);

  color_set(&blue, 0.0,0.8,0.8);

  point_set2D( &p, 275,350 );
  ellipse_set(&elip, p, 75, 220,0);
  ellipse_drawFill(&elip, src, blue);

  color_set(&blue, 0.0,1.0,1.0);

  point_set2D( &p, 250,350 );
  ellipse_set(&elip, p, 50, 200,0);
  ellipse_drawFill(&elip, src, blue);

  color_set(&blue, 0.4,1.0,1.0);

  point_set2D( &p, 225,350 );
  ellipse_set(&elip, p, 25, 175,0);
  ellipse_drawFill(&elip, src, blue);

  color_set(&blue, 0.6,1.0,1.0);

  point_set2D( &p, 200,350 );
  ellipse_set(&elip, p, 20, 150,0);
  ellipse_drawFill(&elip, src, blue);

  color_set(&blue, 0.7,1.0,1.0);

  point_set2D( &p, 175,350 );
  ellipse_set(&elip, p, 15, 125,0);
  ellipse_drawFill(&elip, src, blue);

  color_set(&blue, 0.8,1.0,1.0);

  point_set2D( &p, 150,350 );
  ellipse_set(&elip, p, 5, 75,0);
  ellipse_drawFill(&elip, src, blue);

  point_set2D( &p, 350, 100 );
  circle_set( &circ, p, 25 );
  circle_drawFill( &circ, src, red);

  image_write( src, "3DimageFill.ppm" );

  polygon_free(poly);
  image_free( src );

  return(0);

}
