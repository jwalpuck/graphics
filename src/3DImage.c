/* 
 This is nested cubes inspired from the rubix cube! 

CS351 Graphcis
October 16, 2014
----------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "graphics.h"


int main(int argc, char *argv[]) {
  const int rows = 180;
  const int cols = 320;
  View3D view;
  Matrix vtm;
  Matrix ltm;
  Polyline cube[8];
  Polyline tpoly;
  Point  v[24];
  Color  color[6];
  Image *src;
  char filename[256];
  int i;

  // set some colors
  color_set( &color[0], 1, 0, 1 );
  color_set( &color[1], 1, 1, 0 );
  color_set( &color[2], 0, 1, 0 );
  color_set( &color[3], 0, 0, 1 );
  color_set( &color[4], 1, 0.5, 0 );
  color_set( &color[5], 1, 1, 1 );

  // initialize polygons
  for(i=0;i<6;i++) {
    polyline_init( &cube[i] );
  }

  // corners of a cube, centered at (0, 0, 0)
  //front side
  point_set( &v[0], -1, -1, -1,1);
  point_set( &v[1],  1, -1, -1,1 );
  point_set( &v[2],  1,  1, -1,1 );
  point_set( &v[3], -1,  1, -1,1 );

  //top side
  point_set( &v[4], -1, 1, -1,1);
  point_set( &v[5],  1, 1, -1,1 );
  point_set( &v[6],  1, 1,  1,1 );
  point_set( &v[7],  -1, 1,  1,1 );

  //left side
  point_set( &v[8], -1, 1,  1,1 );
  point_set( &v[9],  -1, 1, -1,1 );
  point_set( &v[10],  -1,  -1,  -1,1 );
  point_set( &v[11], -1,  -1, 1,1 );

  // bottom side
  point_set( &v[12],  -1, -1,  1,1 );
  point_set( &v[13], -1, - 1, - 1,1 );
  point_set( &v[14], 1, -1, -1,1);
  point_set( &v[15],  1, -1, 1,1 );
  
  //backside 
  point_set( &v[16], 1, -1,  1,1 );
  point_set( &v[17], -1, -1,  1,1 );
  point_set( &v[18],  -1,  1,  1,1 );
  point_set( &v[19], 1,  1,  1,1 );

    //right side
  point_set( &v[20], 1, 1,  1,1 );
  point_set( &v[21],  1, -1,  1,1 );
  point_set( &v[22],  1, - 1,  -1,1 );
  point_set( &v[23], 1,  -1,  1,1 );

  // front side
  polyline_set( &cube[0], 24, &(v[0]));
  polyline_init(&cube[1]);
  polyline_init(&cube[2]);
  polyline_init(&cube[3]);
  polyline_init(&cube[4]);
  polyline_init(&cube[5]);
  polyline_init(&cube[6]); 
  polyline_init(&cube[7]);


  polyline_copy(&cube[1], &cube[0]);
  polyline_copy(&cube[2], &cube[0]);
  polyline_copy(&cube[3], &cube[0]);
  polyline_copy(&cube[4], &cube[0]);
  polyline_copy(&cube[5], &cube[0]);
  polyline_copy(&cube[6], &cube[0]); 
  polyline_copy(&cube[7], &cube[0]);
  
  matrix_identity(&ltm);
  matrix_translate(&ltm, 2, 0, 0);
  matrix_xformPolyline(&ltm, &cube[1]);

  matrix_identity(&ltm);
  matrix_translate(&ltm, 2, 0, 2);
  matrix_xformPolyline(&ltm, &cube[2]);

  matrix_identity(&ltm);
  matrix_translate(&ltm, 0, 2, 0);
  matrix_xformPolyline(&ltm, &cube[3]);

  matrix_identity(&ltm);
  matrix_translate(&ltm, 0, 2, 2);
  matrix_xformPolyline(&ltm, &cube[4]);

  matrix_identity(&ltm);
  matrix_translate(&ltm, 2, 2, 0);
  matrix_xformPolyline(&ltm, &cube[5]);

  matrix_identity(&ltm);
  matrix_translate(&ltm, 2, 2, 2);
  matrix_xformPolyline(&ltm, &cube[6]);

  matrix_identity(&ltm);
  matrix_translate(&ltm, 0,0, 2);
  matrix_xformPolyline(&ltm, &cube[7]);

  //create a certain number of frames. 
  int count;
  for(count = 0; count < 30; count++){

    float alpha = count * 0.01;

    //cool spinning stuff. 
    // point_set( &(view.vrp), 3*alpha*sin(count*(3.14/180)), 2*alpha*cos(count*(3.14/180)), -2*alpha - (1.0-alpha)*3,0);
    
    //Another way to move the VRP around! 
    //point_set( &(view.vrp),0, 2+alpha,1,0);
    point_set(&(view.vrp), 3,2, -2,0);
    vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );

    vector_set( &(view.vup), 0,1.0, 0 );
    view.d = 2;  // focal length
    view.du = 5;
    view.dv = view.du * (float)rows / cols;
    view.f = 0; // front clip plane
    view.b = 5; // back clip plane
    view.screenx = cols;
    view.screeny = rows;

    matrix_setView3D( &vtm, &view );
    matrix_print(&vtm, stdout);
    // create image
    src = image_create( rows, cols );

    // use a temprary polygon to transform stuff
    polyline_init( &tpoly );

    //matrix_print(&vtm, stdout);
    printf("Drawing Polygons\n");
    for(i=0;i<8;i++) {
      matrix_identity(&ltm);
      polyline_copy( &tpoly, &cube[i] );
      if(i%2 == 0){
		matrix_translate(&ltm, -count*0.5, -count*0.5, -count*0.5);
      }else{
		matrix_translate(&ltm, count*0.01, count*0.01, count*0.01);
      }
      matrix_xformPolyline( &ltm, &tpoly);
      matrix_xformPolyline( &vtm, &tpoly );
    
      //normalize by homogeneous coordinate before drawing
      polyline_normalize( &tpoly );

      polyline_draw( &tpoly, src, color[i%6] );
      polyline_print( &tpoly, stdout );
    }

    sprintf(filename, "/export/home/vedwards/Desktop/Graphics/images/cube2/frame-%04d.ppm", count );
    printf("Writing image\n");
    image_write( src, filename );

  }

  return(0);
}

