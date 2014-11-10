/*
  Torrie's Scene

  Graphics CS351 
  October 28, 2014 
  ------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

int main( int argc, char *argv[]){
  //set up the images
  Image *src; 
  Image *myImage;

  //set up the modules!!
  Module *basket;

  Module *connector;
  Module *connector1;
  Line l;
  Point pts[2];

  Module *circle;
  Module *hotAirBalloon;
  Module *teamOfBalloons; 
  Module *scene; 

  //pick the colors
  Color colors[6]; 
  Color brown;
  Color blue;
  Color green;
  Color grey; 

  //set up view stuff, and image file stuff
  Matrix vtm, gtm; 
  int rows; 
  int cols; 
  View3D view; 
  DrawState *ds;
  char filename[256];

  int i, j, k, m, n; 

  //Set the colors up
  color_set(&brown, 0.2, 0.1, 0.0);
  color_set(&blue, 0.6, 0.8, 1.0);
  color_set(&green, 0.1, 0.4, 0.0);
  color_set(&grey, 0.3, 0.3, 0.3);
  color_set(&colors[0], 1.0, 0.0, 0.0);//Red
  color_set(&colors[1],1.0, 0.5, 0.0);//orange
  color_set(&colors[2],1.0, 1.0, 0.1);//yellow
  color_set(&colors[3], 0.0, 1.0, 0.0);//green
  color_set(&colors[4], 0.0, 0.0, 1.0);//blue
  color_set(&colors[5], 0.4, 0.0, 0.8);//purple
  
  //if you want to supply a background image you can, otherwise I set a default sky blue background!
  if(argc>1){
    printf("you supplied an image\n");
    myImage = image_read(argv[1]);
    rows = myImage->rows;
    cols = myImage->cols;
    printf("%d %d\n", rows, cols);
  }else{
    printf("We are giving your image a default size!\n");
    rows = 500;
    cols = 500;
    myImage = image_create(rows, cols); 
    for(m = 0; m< rows; m++){
      for(n = 0; n<cols; n++){
	image_setColor(myImage, m, n, blue);
      }
    }
  }

  //Loop over the scene 300 times moving the scene around!! 
  for(k = 0; k<300; k++){
    //Set up the view
    point_set( &(view.vrp), 150, 100, 200, 1.0);
    vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2]);
    vector_set( &(view.vup), 0, 1.0, 0);
    view.d = 20; 
    view.du = 10; 
    view.dv = view.du* (float)rows/cols;
    view.f = 0; 
    view.b = 5; 
    view.screenx = rows; 
    view.screeny = cols; 

    matrix_setView3D( &vtm, &view); 
    matrix_identity( &gtm ); 

    // basket: cube (will need 1 in hot air balloon module)
    basket = module_create(); 
    module_color(basket, &brown);
    module_cube(basket, 1); 

    //connectors: lines need 4
    connector = module_create();
    point_set3D(&pts[0],1,1,1 );
    point_set3D(&pts[1],2,4.2,1);
    line_set(&l, pts[0], pts[1]);
    module_line(connector, &l);

    connector1 = module_create();
    point_set3D(&pts[0], 1,1 , 1);
    point_set3D(&pts[1], 0,4.2 ,1 );
    line_set(&l, pts[0], pts[1]);
    module_line(connector1, &l);

    // balloon: circles nested on top of eachother 
    circle = module_create();
    module_color(circle, &colors[0]);
    module_rotateX(circle, 0, 1);
    module_translate2D(circle, 0, 3);
    module_circle(circle, 1);

    module_color(circle, &colors[1]);
    module_rotateX(circle, 1, 0);
    module_translate2D(circle, 0, 1);
    module_circle(circle, 2.5);

    module_color(circle, &colors[2]);
    module_rotateX(circle, 1, 0);
    module_translate2D(circle, 0, 1);
    module_circle(circle, 3);

    module_color(circle, &colors[3]);
    module_rotateX(circle, 1, 0);
    module_translate2D(circle, 0, 1);
    module_circle(circle, 4);

    module_color(circle, &colors[4]);
    module_rotateX(circle, 1, 0);
    module_translate2D(circle, 0, 1);
    module_circle(circle, 5);

    module_color(circle, &colors[5]);
    module_rotateX(circle, 1, 0);
    module_translate2D(circle, 0, 1);
    module_circle(circle, 6);

    module_color(circle, &colors[0]);
    module_rotateX(circle, 1,0);
    module_translate2D(circle, 0, 1);
    module_circle(circle, 7);

    module_color(circle, &colors[1]);
    module_rotateX(circle, 1, 0);
    module_translate2D(circle, 0, 1);
    module_circle(circle, 7);

    module_color(circle, &colors[2]);
    module_rotateX(circle, 1, 0);
    module_translate2D(circle, 0,1);
    module_circle(circle, 7);

    module_color(circle, &colors[3]);
    module_rotateX(circle, 1, 0);
    module_translate2D(circle, 0, 1);
    module_circle(circle, 7);

    module_color(circle, &colors[4]);
    module_rotateX(circle, 1, 0);
    module_translate2D(circle, 0, 1);
    module_circle(circle, 6);

    module_color(circle, &colors[5]);
    module_rotateX(circle, 1, 0);
    module_translate2D(circle, 0, 1);
    module_circle(circle, 5);

    module_color(circle, &colors[0]);
    module_rotateX(circle, 1, 0);
    module_translate2D(circle, 0, 1);
    module_circle(circle, 4);

    module_color(circle, &colors[1]);
    module_rotateX(circle, 1, 0);
    module_translate2D(circle, 0, 0.5);
    module_circle(circle, 3);

    module_color(circle, &colors[2]);
    module_rotateX(circle, 1, 0);
    module_translate2D(circle, 0, 0.5);
    module_circle(circle, 2);

    //hotAirBalloon: put the above parts together
    hotAirBalloon = module_create();
    module_module(hotAirBalloon, basket);
    module_module(hotAirBalloon, connector);
    module_translate(hotAirBalloon, -2,0 ,0 );
    module_module(hotAirBalloon, connector1);
    module_translate(hotAirBalloon, 0, 0, -2);
    module_module(hotAirBalloon, connector1);
    module_translate(hotAirBalloon, 2, 0, 0);
    module_module(hotAirBalloon, connector);
    module_module(hotAirBalloon, circle);


    //make a team of balloons
    teamOfBalloons = module_create();
    module_translate(teamOfBalloons, 0,-30,-15);
    module_module(teamOfBalloons, hotAirBalloon);
    module_translate(teamOfBalloons, 0, 0+(k*0.1),15);
    module_module(teamOfBalloons, hotAirBalloon);
    module_translate(teamOfBalloons, 0, 0+(k*0.1),15);
    module_module(teamOfBalloons, hotAirBalloon);


    //make a scene of balloons
    scene = module_create(); 
    module_translate(scene, -40, 10+(k*0.1), 10);
    module_module(scene, teamOfBalloons);
    module_translate(scene, 140, 10, 55);
    module_module(scene, teamOfBalloons);
    module_translate(scene, -50, 10+(k*0.1), -40);
    module_module(scene, teamOfBalloons);
    module_translate(scene, 30, 10+(k*0.2) , -55);
    module_module(scene, teamOfBalloons);

    //set up the image
    src = image_create(rows, cols); 

    //Either draw the background image you supplied or use my default background
    for (i = 0; i<rows; i++){
      for (j = 0; j<cols; j++){
	  blue = image_getColor(myImage, i, j);
	  image_setColor(src,i, j, blue);
      }
    }

    //set up the draw state if you want filled polygons need to use ShadeConstant instead of ShadeFrame
    ds = drawstate_create();
    ds->shade = ShadeFrame; 

    //draw the modules!
    module_draw( scene, &vtm, &gtm, ds, NULL, src); 

    //put the files in the right place with the right name!! 
    sprintf(filename, "/export/home/vedwards/Desktop/Graphics/images/hotAirBalloons3/frame-%04d.ppm", k );
    printf("Writing image\n");
    image_write( src, filename );
  }

  //Clean up, delete all of the modules, images, and drawState
  module_delete(basket);
  module_delete(connector);
  module_delete(connector1);
  module_delete(circle);
  module_delete(hotAirBalloon);
  module_delete(teamOfBalloons);

  free(ds);
  image_free( src );
  image_free( myImage );
  return(0);
}
