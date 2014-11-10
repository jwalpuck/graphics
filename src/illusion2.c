/*
This creates an optical illusion!! 

October 16, 2014 
CS 351 Graphics
----------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"


int main(int argc, char *argv[]) {
  int i;
  Image *src;
  Line l[12]; 
  //Point pairs[2];
  Color color[6];

  // create image
  src = image_create( 700, 700 );

  //set up the colors
  color_set( &color[0], 0.0, 1.0, 0.0);
  color_set( &color[1], 1.0, 0.0, 0.0);
  color_set( &color[2], 0.0, 0.0, 1.0);
  color_set( &color[3], 1.0, 1.0, 0.0);
  color_set( &color[4], 1.0, 0.0, 1.0);
  color_set( &color[5], 0.0, 1.0, 1.0);

  /* point_set3D(&pairs[0], 250,10, 1); */
  /* point_set3D(&pairs[1], 250, 310, 1); */
  
  /* line_set(&l[0], (pairs[0]), (pairs[1])); */

  /* point_set3D(&pairs[0], 250,310, 1); */
  /* point_set3D(&pairs[1], 510,460, 1); */
  
  /* line_set(&l[1], (pairs[0]), (pairs[1])); */

  /* point_set3D(&pairs[0], 250,310, 1); */
  /* point_set3D(&pairs[1], 77,400, 1); */
  
  /* line_set(&l[2], (pairs[0]), (pairs[1])); */

  /* point_set3D(&pairs[0], 77,400, 1); */
  /* point_set3D(&pairs[1], 336, 550, 1); */
  
  /* line_set(&l[3], (pairs[0]), (pairs[1])); */

  /* point_set3D(&pairs[0], 336,550, 1); */
  /* point_set3D(&pairs[1], 510, 460, 1); */
  
  /* line_set(&l[4], (pairs[0]), (pairs[1])); */

  /* point_set3D(&pairs[0], 510,460, 1); */
  /* point_set3D(&pairs[1], 510, 160, 1); */
  
  /* line_set(&l[5], (pairs[0]), (pairs[1])); */

  /* point_set3D(&pairs[0], 510,160, 1); */
  /* point_set3D(&pairs[1], 250, 10, 1); */
  
  /* line_set(&l[6], (pairs[0]), pairs[1]); */

  /* point_set3D(&pairs[0], 250,10, 1); */
  /* point_set3D(&pairs[1], 77, 100, 1); */
  
  /* line_set(&l[7], pairs[0], pairs[1]); */
 
  /* point_set3D(&pairs[0], 77,100, 1); */
  /* point_set3D(&pairs[1], 77, 400, 1); */
  
  /* line_set(&l[8], pairs[0], pairs[1]); */

  /* point_set3D(&pairs[0], 77,100, 1); */
  /* point_set3D(&pairs[1], 330, 250, 1); */
  
  /* line_set(&l[9], pairs[0], pairs[1]); */

  /* point_set3D(&pairs[0], 330, 250, 1); */
  /* point_set3D(&pairs[1], 510, 160, 1); */
  
  /* line_set(&l[10], pairs[0], pairs[1]); */

  /* point_set3D(&pairs[0], 330, 250, 1); */
  /* point_set3D(&pairs[1], 336, 550, 1); */
  
  /* line_set(&l[11], pairs[0], pairs[1]); */
  
  /* for(i = 0; i<12; i++){ */
  /*   line_draw(&l[i], src, color[i%6]); */
  /* } */


  for(i= 0; i<12; i++){
  line_set2D(&l[0], 250+i, 10+i, 250+i, 310+i);
  line_draw(&l[0], src, color[0]);
  }
  
  for(i = 0; i<12; i++){
  line_set2D(&l[1],250+i, 310+i, 510+i, 460+i);
  line_draw(&l[1], src, color[1]);
  }

  for(i = 0; i<12; i++){
  line_set2D(&l[2],250+i, 310+i, 77+i, 400+i);
  line_draw(&l[2], src, color[2]);
  
  line_set2D(&l[3],77+i, 400+i, 336+i, 550+i);
  line_draw(&l[3], src, color[3]);
  
  line_set2D(&l[4],336+i, 550+i, 510+i, 460+i);
  line_draw(&l[4], src, color[4]);

  line_set2D(&l[5],510+i, 460+i, 510+i, 160+i);
  line_draw(&l[5], src, color[5]);

  line_set2D(&l[6], 510+i, 160+i, 250+i, 10+i);
  line_draw(&l[6], src, color[0]);
  
  line_set2D(&l[7],250+i, 10+i, 77+i, 100+i);
  line_draw(&l[7], src, color[1]);
  
  line_set2D(&l[8], 77+i, 100+i, 77+i, 400+i);
  line_draw(&l[8], src, color[2]);

  
  line_set2D(&l[9], 77+i, 100+i, 330+i, 250+i);
  line_draw(&l[9], src, color[3]);

  line_set2D(&l[10], 330+i, 250+i, 510+i, 160+i);
  line_draw(&l[10], src, color[4]);
  
  line_set2D(&l[11],330+i, 250+i, 336+i, 550+i);
  line_draw(&l[11], src, color[5]);

  }
  
  printf("writing the image\n");
  image_write(src, "illusion2.ppm");
  
  free(src);
  return(0);
}
