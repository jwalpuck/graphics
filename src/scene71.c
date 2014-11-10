/*
This is graphcis scene 1 for project 7 

CS 351 Graphics
November 8, 2014
Torrie Edwards
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"

int main(int argc, char *argv[]) {
  Color white; 
  Color red;
  Color blue;
  Color black;
  Color dark;
  Color table, wall;
  BezierCurve bc; 
  Point pt[4];
  Module *cyl; 
  Module *curve;
  Module*topper;
  Module *cake;
  Module *scene;
  View3D view; 
  Matrix VTM, GTM;
  DrawState *ds; 
  Image *src; 
  int rows = 500;
  int cols = 500;
  int i, j, k;


  color_set(&white, 0.0, 1.0, 1.0);
  color_set(&red, 0.6, 0.7, 1.0);
  color_set(&blue, 1.0, 0.5, 0.8);
  color_set(&table, 1.0, 0.8, 0.6);
  color_set(&wall, 0.6, 1.0, 0.6);
  color_set(&black, 1.0, 1.0, 0.1);
  color_set(&dark, 0.2, 0.2, 1.0);

  src = image_create(rows, cols);
  for(i = 0; i< rows; i++){
    for(j = 0; j< cols; j++){
      image_setColor(src, i, j, wall);
      if(i > cols/2){
	image_setColor(src, i, j, table);
      }
    }
  }


  //make topper
  curve = module_create();
  point_set3D(&pt[0], 0.0, 0.0, 0.0);
  point_set3D(&pt[1], 0.35, 0.0, 0.2);
  point_set3D(&pt[2], 0.7, 0.7, 0.0);
  point_set3D(&pt[3], 0.2, 0.2, 0.0);
  bezierCurve_set(&bc, pt);
  module_bezierCurve(curve, &bc, 2);
  
  topper = module_create();
  for(i = 0; i< 25; i++){
    module_color(topper, &black);
    module_module(topper, curve);
    module_rotateY( topper, cos(2.0*M_PI/25), sin(2.0*M_PI/25));
  }
  
  //make cylinder
  cyl = module_create();
  module_cylinder(cyl, 100);
  
  //make the cake
  cake = module_create();
  module_translate(cake, 0, -1, 0);
  module_color(cake, &white);
  module_module(cake, cyl);
  module_translate(cake, 0, 1, 0);
  module_scale(cake, 0.7, 0.7, 1);
  module_color(cake, &red);
  module_module(cake, cyl);
  module_translate(cake, 0, 1.25, 0);
  module_scale(cake, 0.6, 0.6, 1);
  module_color(cake, &blue);
  module_module(cake, cyl);
  module_translate(cake, 0, 0.45, 0);
  module_module(cake, topper);

  //put cakes in the scene
  scene = module_create();
  module_translate(scene, 2, 0, 0);
  module_module(scene, cake);
  module_translate(scene, -4, 0, 0);
  module_module(scene, cake);
  module_translate(scene, 2, 0, 0);
  module_module(scene, cake);



  // set up the view
  point_set3D(&(view.vrp), 0.0, 1.0, -5.0 );
  vector_set( &(view.vpn), 0.0, 0.0, 1.0 );
  vector_set( &(view.vup), 0.0, 1.0, 0.0 );
  view.d = 1.0;
  view.du = 1.0;
  view.dv = 1.0*rows/cols;
  view.screeny = rows;
  view.screenx = cols;
  view.f = 0.0;
  view.b = 3.0;

  matrix_setView3D( &VTM, &view );
  matrix_identity( &GTM );

  ds = drawstate_create();
  ds->shade = ShadeFrame; 
  for( k = 0; k< 100; k++){
    char buffer[256];
		
    matrix_rotateY(&GTM, cos(M_PI/100.0), sin(M_PI/100.0) );
    module_draw(scene, &VTM, &GTM, ds, NULL, src);

    sprintf(buffer, "/export/home/vedwards/Desktop/Graphics/images/cake/cake -frame%03d.ppm", k);
     
    image_write(src, buffer);
    for(i = 0; i< rows; i++){
      for(j = 0; j< cols; j++){
	image_setColor(src, i, j, wall);
	if(i > cols/2){
	  image_setColor(src, i, j, table);
	}
      }
    }
  }
  module_delete(cyl);
  module_delete(curve);
  module_delete(topper);
  module_delete(cake);
  module_delete(scene);

  free(ds);
  image_free(src);

  return(0);
}
