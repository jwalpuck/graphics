/*
  Torrie and Jack Blue Cube

  Graphics CS351 
  October 28, 2014
  --------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

/*we are going to draw a cube using our new module hiearchy*/
int main( int argc, char *argv[]){
  Image *src; 
  Module *cube1;
  Module *cube2;
  Module *cube3;
  Module *cube4; 
  Module *cube5;
  Module *cube6;
  Module *cube7;
  Module *cube8;
  Module *manyCubes;
  Color Blue; 
  View3D view;
  Matrix vtm, gtm;
  int rows = 320;
  int cols = 320;
  DrawState *ds;
  int count;
  char filename[256];

  //Set the colors up
  color_set(&Blue, 0.0, 0, 1.0);
  
  // set up the view
  point_set( &(view.vrp), 1, 2, 0,0 );
  vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] ); 
  vector_set( &(view.vup),0, 1.0, 0);
  view.d = 5;
  view.du = 5;
  view.dv = view.du * (float)rows/cols;
  view.f = 0;
  view.b = 5;
  view.screenx = rows;
  view.screeny = cols;
  
  matrix_setView3D( &vtm, &view );
  matrix_identity( &gtm );

  for (count = 0; count< 205; count++){
    //Start first cube
    cube1 = module_create();
    module_color( cube1, &Blue);
    module_translate(cube1, 0, 0, 0-count*0.01);
    module_cube(cube1, 0);

    //Set the colors up
    color_set(&Blue, 0.1, 0.1, 1.0);
    //Start second cube
    cube2 = module_create();
    module_color(cube2, &Blue);
    module_translate(cube2, 0, 0, 0+count*0.01);
    module_cube(cube2, 0);

    //Set the colors up
    color_set(&Blue, 0.2, 0.2, 1.0);
    //start third cube
    cube3 = module_create();
    module_color(cube3, &Blue);
    module_translate(cube3, 0+count*0.01,0, 0);
    module_cube(cube3, 0);

    //Set the colors up
    color_set(&Blue, 0.3, 0.3, 1.0);
    //start fourth cube
    cube4 = module_create();
    module_color(cube4, &Blue);
    module_translate(cube4, 0-count*0.01,0, 0);
    module_cube(cube4, 0);

    //Set the colors up
    color_set(&Blue, 0.4, 0.4, 1.0);
    //start fifth cube
    cube5 = module_create();
    module_color(cube5, &Blue); 
    module_translate(cube5, 0-count*0.01, 0, 0-count*0.01);
    module_cube(cube5, 0);

    //Set the colors up
    color_set(&Blue, 0.5, 0.5, 1.0);
    cube6 = module_create();
    module_color(cube6, &Blue); 
    module_translate(cube6, 0+count*0.01, 0, 0+count*0.01);
    module_cube(cube6, 0);

    //Set the colors up
    color_set(&Blue, 0.6, 0.6, 1.0);
    cube7 = module_create();
    module_color(cube7, &Blue); 
    module_translate(cube7, 0-count*0.01, 0, 0+count*0.01);
    module_cube(cube7, 0);

    //Set the colors up
    color_set(&Blue, 0.7, 0.7, 1.0);
    cube8 = module_create();
    module_color(cube8, &Blue); 
    module_translate(cube8, 0+count*0.01, 0, 0-count*0.01);
    module_cube(cube8, 0);


    //put the cubes into a scene! 
    manyCubes = module_create();
    module_module(manyCubes, cube5);
    module_module(manyCubes, cube6);
    module_module(manyCubes, cube7);
    module_module(manyCubes, cube8);
    module_module(manyCubes, cube1);
    module_module(manyCubes, cube2);
    module_module(manyCubes, cube3);
    module_module(manyCubes, cube4);

    //Create the image draw state
    src = image_create(rows, cols);
    ds = drawstate_create();
    ds->shade = ShadeConstant;

    //Draw the scene
    module_draw( manyCubes, &vtm, &gtm, ds, NULL, src );
    //write out the scene
    sprintf(filename, "/export/home/vedwards/Desktop/Graphics/images/blueCube/frame-%04d.ppm", count );
    printf("Writing image\n");
    image_write( src, filename );

    //image_write(src, "blueCubeNew.ppm");
  }
  //free the modules
  module_delete( manyCubes );
  module_delete( cube1 );
  module_delete( cube2 );
  module_delete( cube3 );
  module_delete( cube4 );
  module_delete( cube5 );
  module_delete( cube6 );
  module_delete( cube7 );
  module_delete( cube8 );

  //free the drawState
  free(ds);

  //free the image
  image_free( src );

  return(0);

}
