/*
  Bruce A. Maxwell
  Fall 2014

  Test function 1 for the graphics primitives assignment
  Enterpoop
 */

// edit the include files as necessary
#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

// draw a box
static int box( Image *src, Color color, int x, int y, int dx, int dy );
static int box( Image *src, Color color, int x, int y, int dx, int dy ) {
  Line l;
  
  line_set2D( &l, x, y, x, y+dy );
  line_draw( &l, src, color );

  line_set2D( &l, x, y+dy, x + dx, y+dy );
  line_draw( &l, src, color );

  line_set2D( &l, x+dx, y+dy, x+dx, y );
  line_draw( &l, src, color );

  line_set2D( &l, x+dx, y, x, y );
  line_draw( &l, src, color );

  return(0);
}

// draw a few boxes, a circle, and some lines.
int main(int argc, char *argv[]) {
  Image *src;
  Color White;
  Color Red;
  Color Blue;
  Point p1, p2,p3;
  Circle circ;
  Ellipse elip;
  Line line;

  color_set( &White, 1.0, 1.0, 1.0 );
  color_set( &Red, 0.9, 0.05, 0.05 );
  color_set( &Blue, 0.0,0.0,1.0);

  src = image_create( 600, 600 );

  box( src, White, 100, 100, 100, 20 );
  box( src, White, 100, 200, 100, 20 );
  box( src, White, 150, 140, 70, 40 );
  box( src, White, 160, 120, 10, 20 );
  box( src, White, 160, 180, 10, 20 );

  point_set2D( &p1, 260, 160 );
  circle_set( &circ, p1, 60 );
  //circle_draw( &circ, src, White );
  circle_drawFill(&circ, src, White);

  printf("Drawing ellipse\n");
  point_set2D( &p2, 300, 300 );
  ellipse_set(&elip, p2, 75, 100, 0);
  ellipse_draw(&elip, src,White );
  //ellipse_drawFill(&elip, src, White);

  point_set2D( &p3, 300, 300 );
  ellipse_set(&elip, p3, 75, 100,1);
  ellipse_draw(&elip, src, White);

  point_set2D( &p3, 300, 300 );
  ellipse_set(&elip, p3, 150,100 ,120);
  ellipse_draw(&elip, src, Blue);
  //ellipse_drawFill(&elip, src, Blue);

  point_set2D( &p3, 300, 300 );
  ellipse_set(&elip, p3, 150,100 ,45);
  ellipse_draw(&elip, src, Red);


  line_set2D( &line, 290, 210, 470, 300);
  line_draw( &line, src, Red );

  line_set2D( &line, 295, 205, 475, 280);
  line_draw( &line, src, Red );
  
  image_write( src, "test3aEllipse.ppm" );

  image_free( src );

  return(0);
}
