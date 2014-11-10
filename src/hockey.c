/*
 * hockey.c
 * Jack Walpuck
 *
 * Draws a 3D scene of a hockey stick and puck
 */

#include "math.h"
#include "image.h" 
#include "point.h"
#include "color.h"
#include "line.h"
#include "polyline.h"
#include "circle.h"
#include "ellipse.h"

int main(int argc, char *argv[]) {
  int i, j;
  Image *src;
  Color White;
  Color Black;
  Color Red;
  Point p;
  Point vlist[7];
  Point vlist2[9];
  Polyline *poly;
  Line l, l2;
  Ellipse e;

  color_set(&Black, 0.0, 0.0, 0.0);
  color_set(&White, 1.0, 1.0, 1.0);
  color_set(&Red, 1.0, 0.0, 0.0);

  src = image_create(400, 600);

  // Initialize the image to all white
  for(i=0;i<src->rows;i++) {
    for(j=0;j<src->cols;j++) {
      image_setColor(src, i, j, White );
    }
  }

  poly = polyline_createp(9, vlist);

  //Draw the net
  point_set2D(&(vlist2[0]), 310, 100);
  point_set2D(&(vlist2[1]), 300, 100);
  point_set2D(&(vlist2[2]), 300, 40);
  point_set2D(&(vlist2[3]), 400, 40);
  point_set2D(&(vlist2[4]), 400, 100);
  point_set2D(&(vlist2[5]), 390, 100);
  point_set2D(&(vlist2[6]), 390, 50);
  point_set2D(&(vlist2[7]), 310, 50);  
  point_set2D(&(vlist2[8]), 310, 100); 

  polyline_set(poly, 9, vlist2);
  polyline_draw(poly, src, Red); 

  //Draw the goal line
  for(i = 0; i < 10; i++) {
    line_set2D(&l, 0, 100 + i, 75 + i, 100 + i);
    line_set2D(&l2, 100 + i, 100 + i, 600, 100 + i);
    line_draw(&l, src, Red);
    line_draw(&l2, src, Red);
  }

  //Draw the stick
  point_set2D(&(vlist[0]), 40, 40);
  point_set2D(&(vlist[1]), 210, 330);
  point_set2D(&(vlist[2]), 270, 330);
  point_set2D(&(vlist[3]), 270, 310);
  point_set2D(&(vlist[4]), 225, 310);
  point_set2D(&(vlist[5]), 60, 35);
  point_set2D(&(vlist[6]), 40, 40);

  polyline_draw(poly, src, Black);

  for(i = 0; i < 7; i++) {
    for (j = 0; j < 7; j++) {
      point_set2D(&(vlist[j]), vlist[j].val[0] + 1, vlist[j].val[1]);
    }
    polyline_set(poly, 7, vlist);
    polyline_draw(poly, src, Black);
  }

  Color Fill;

  //Draw the puck
  for(i = 0; i < 7; i++) {
    for(j = 0; j < 10; j++) {
      point_set2D(&p, 290 - i * 35, 260 + j + ( i * 10));
      color_set(&Fill, 1.0 - i / 6.0, 1.0 - i / 6.0, 1.0 - i / 6.0); 
      ellipse_set(&e, p, 10 - i * 1.5, 20 - i * 2.5, 0);
      ellipse_drawFill(&e, src, Fill);
    }
  }

  image_write(src, "hockey.ppm");

  image_free(src);

  printf("Goal!\n");

  return (0);
}
