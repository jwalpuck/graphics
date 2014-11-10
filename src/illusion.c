/*
This creates an optical illusion!! 

October 16, 2014 
CS 351 Graphics
----------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

void setBlack( Image *src );
void setBlack( Image *src ) {
  int i, j;
  Color White;

  color_set(&White, 0.0, 0.0, 0.0);

  for(i=0;i<src->rows;i++) {
    for(j=0;j<src->cols;j++) {
      image_setColor( src, i, j, White );
    }
  }
}

int main(int argc, char *argv[]) {
  int nFrames;
  int i, t, j;
  Image *src;
  Polygon p[3]; 
  Polygon phold;
  Point edges[18];
  Color color[3];

  View2D view; 
  Matrix vtm; 
  Matrix ltm;
  char filename[256];

  if( argc > 1 ) {
    nFrames = atof( argv[1] );
  }else{
    nFrames = 50;
  }


  // create image
  src = image_create( 500, 500 );

  //set up the colors
  color_set( &color[0], 1, 1, 1);
  color_set( &color[1],0.6 ,0.6, 0.6 );
  color_set( &color[2], 0.4, 0.4, 0.4 );

  //build the polygons! 
  for(i=0; i<3; i++){
    polygon_init( &p[i]);
  }

  point_set3D(&edges[0], 420, 80, 1);
  point_set3D(&edges[1], 240, 396, 1);
  point_set3D(&edges[2], 30, 50, 1);
  point_set3D(&edges[3], 40, 20, 1);
  point_set3D(&edges[4], 240, 366, 1);
  point_set3D(&edges[5], 390, 80, 1);
  
  polygon_set( &p[0], 6, &(edges[0]));

  point_set3D(&edges[6], 440, 20, 1);
  point_set3D(&edges[7], 450, 50, 1);
  point_set3D(&edges[8], 80, 50, 1);
  point_set3D(&edges[9], 256, 336, 1);
  point_set3D(&edges[10], 240, 366, 1);
  point_set3D(&edges[11], 40, 20, 1);
  
  polygon_set( &p[1], 6, &(edges[6]));

  point_set3D(&edges[12], 450, 50, 1);
  point_set3D(&edges[13], 270, 396, 1);
  point_set3D(&edges[14], 240, 396, 1);
  point_set3D(&edges[15], 420, 80, 1);
  point_set3D(&edges[16], 98, 80, 1);
  point_set3D(&edges[17], 80, 50, 1);

  polygon_set( &p[2], 6, &(edges[12]));

  //Set up the view stuff
  point_set2D( &(view.vrp), 150, 150 );
  view.dx = 1200.0;
  vector_set( &(view.x), 0.0, 1.0, 0.0 );
  view.screenx = 300;
  view.screeny = 300;

  matrix_setView2D( &vtm, &view );
  printf("vtm:\n");
  matrix_print(&vtm, stdout);

  polygon_init(&phold);
  //loop through for the number of frames
  for(t = 0; t<nFrames; t++){
    setBlack(src);
    //go through the list of polygons
    for( i = 0; i<3; i++){
      polygon_copy( &phold, &p[i]);
     
      matrix_identity( &ltm );
      //DO TRANSFORMATIONS TO THE IMPOSSIBLE OBJECT THING.
      //Scale the shape, this will pan the image out (image will get smaller).
      //matrix_scale2D( &ltm, 1.0/(t/2+1), 1.0/(t/2+1));

      //Scale the shape, this will zoom the image in (I hope).
      //matrix_scale2D( &ltm, 1.0/(nFrames-t), 1.0/(nFrames-t));

      //rotate the image about 360 degrees. 
      matrix_rotateZ( &ltm, cos(t/(2*3.14)), sin(t/(2*3.14)));

      matrix_xformPolygon(&ltm, &phold);
      matrix_xformPolygon(&vtm, &phold);
      polygon_normalize(&phold);
      polygon_drawFill(&phold, src, color[i]);
    }

    printf("write the image\n");
    sprintf(filename, "/export/home/vedwards/Desktop/Graphics/images/illusion/frame-%04d.ppm", t);
    image_write(src, filename);
    // translate the view across the scene
    // point_set2D( &(view.vrp), 2.0 - 2.4*(t+1)/nFrames, 2.0 - 2.4*(t+1)/nFrames );
    point_set2D( &(view.vrp), 150+t * 10, 150 + t * 20);
    matrix_setView2D( &vtm, &view );
  }

  free(src);

  return(0);
}
