/*
This is graphcis scene 2 for project 7 

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

  Module *pyr;
  Module *dia;
  Module *cube;

  Module *curve1;
  Point pt[4];
  BezierCurve bc1;
  Module *spring;

  Module *scene;

  View3D view; 
  Matrix VTM, GTM;
  DrawState *ds; 
  Image *src; 
  int rows = 600;
  int cols = 600;
  int i, j, k;
  char buffer[256];


  color_set(&white, 0.0, 1.0, 1.0);
  color_set(&red, 0.6, 0.7, 1.0);
  color_set(&blue, 1.0, 0.5, 0.8);
  color_set(&black, 0.0, 0.0, 0.0);
  color_set(&dark, 0.2, 0.2, 1.0);
  src = image_create( rows, cols );
  
  //make cube
  cube = module_create();
  module_scale(cube, 0.2, 0.2, 0.2);
  module_translate(cube, 0,0,0);
  module_cube(cube, 1);


  //make pyramid  
  pyr = module_create();
  module_scale(pyr, 0.2, 0.2, 0.2);
  module_translate(pyr, 0, 0, 0);
  module_pyramid(pyr, 0);

  //make diamond
  dia = module_create();
  module_scale(dia, 0.2, 0.2, 0.2);
  module_translate(dia, 0, 0, 0);
  module_diamond(dia, 0);

  //make fake spring
  curve1 = module_create();
  point_set3D(&pt[0], 0.0, 0.0, 0.0);
  point_set3D(&pt[1], 0.35, 0.0, 0.2);
  point_set3D(&pt[2], 0.7, 0.7, 0.0);
  point_set3D(&pt[3], 0.2, 0.2, 0.0);
  bezierCurve_set(&bc1, pt);
  module_bezierCurve(curve1, &bc1, 2);

  for(k = 1; k< 15; k++){
      spring = module_create();
      module_scale(spring, 0.4, 0.4, 0.4);
    for(i = 0; i< 15; i++){
      module_translate(spring, 0, 0.1-(0.04*k), 0);
      module_rotateX(spring,cos(i*(3.14/180)), sin(i*3.14/180));
      module_module(spring, curve1);
      module_rotateX(spring, cos(i*(3.14/2)), sin(i*3.14/2));
      module_module(spring, curve1);
    }

    //make scene
    scene = module_create();
    module_translate(scene, -0.9, 0.5, 0);
    module_module(scene, spring);
    module_translate(scene, 0.1, -0.5, 0);
    module_module(scene, cube);
    module_translate(scene, 0.85, 0.3, 0);
    module_module(scene, spring);
    module_translate(scene, 0.1, -0.3, 0);
    module_module(scene, pyr);
    module_translate(scene, 0.85, 0.3, 0);
    module_module(scene, spring);
    module_translate(scene, 0.1, -0.3,0);
    module_module(scene, dia);

    // set up the view
    point_set3D(&(view.vrp), 0.0, 1.0, -3.0 );
    vector_set( &(view.vpn), 0.0, 0.0, 1.0 );
    vector_set( &(view.vup), 0.0, 1.0, 0.0 );
    view.d = 1;
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
    
    module_draw(scene, &VTM, &GTM, ds, NULL, src);

    sprintf(buffer, "/export/home/vedwards/Desktop/Graphics/images/spring/ -frame%03d.ppm", k);
    image_write(src, buffer);
    for(i = 0; i< rows; i++){
      for(j = 0; j< cols; j++){
	image_setColor(src, i, j, black);
      }
    } 
    module_delete(spring);
  }
    module_delete(pyr);
    module_delete(cube);
    module_delete(dia);
    module_delete(spring);
    module_delete(scene);


    free(ds);
    image_free(src);

    return(0);
  }
