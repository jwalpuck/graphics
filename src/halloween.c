/*
Halloween code! 

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
  int i, t;
  const int Resolution = 50;
  Image *src;
  Polygon p[3]; 
  Polygon phold[10];
  Polygon pcopy;
  Point unitTriangle[3];
  Color color[3];
  Point unitCircle[Resolution];
  Point unitSquare[4];
  float radius = 250;
  View2D view; 
  Matrix vtm; 
  Matrix setup;
  Matrix ltm;
  char filename[256];

  if( argc > 1 ) {
    nFrames = atof( argv[1] );
  }else{
    nFrames = 1;
  }


  // create image
  src = image_create( 500, 500 );

  

  //set up the colors
  color_set( &color[0], 0.0, 0.0, 0.0);
  color_set( &color[1], 1.0 ,1.0, 0.4 );
  color_set( &color[2], 0.8, 0.4, 0.0);

  //build the polygons! 
  for(i=0; i<8; i++){
    polygon_init( &p[i]);
  }

  // make a list of points that form the unit circle
  for(i=0;i<Resolution;i++) {
    point_set2D(&(unitCircle[i]), 
		radius*cos( i * 2.0 * M_PI / (float)Resolution)+250, 
		radius*sin( i * 2.0 * M_PI / (float)Resolution)+250);
  }
  polygon_set( &p[0], Resolution, &(unitCircle[0]));

  point_set3D(&unitTriangle[0], 1, 1, 1);
  point_set3D(&unitTriangle[1], 0, 0, 1);
  point_set3D(&unitTriangle[2], 1, 0, 1);

  polygon_set( &p[1], 3, &(unitTriangle[0]));

  point_set3D(&unitSquare[0], 0, 0, 1);
  point_set3D(&unitSquare[1], 0, 1, 1);
  point_set3D(&unitSquare[2], 1, 1, 1);
  point_set3D(&unitSquare[3], 1, 0, 1);

  polygon_set( &p[2], 4, &(unitSquare[0]));

  //BUILD THE WITCH
  matrix_identity(&setup);
  polygon_init(&phold[0]);
  polygon_copy(&phold[0], &p[0]);

  polygon_init(&phold[1]);
  polygon_copy(&phold[1], &p[1]);
  matrix_shear2D(&setup, 5, 1);
  matrix_scale2D(&setup, 30,30);
  matrix_translate2D(&setup, 150, 150);
  matrix_xformPolygon(&setup, &phold[1]);

  matrix_identity(&setup);
  polygon_init(&phold[2]);
  polygon_copy(&phold[2], &p[1]);
  matrix_scale2D(&setup, 30,45);
  matrix_rotateZ(&setup, cos(-3.00), sin(-3.00));
  matrix_translate2D(&setup, 190, 165);
  matrix_xformPolygon(&setup, &phold[2]);

  matrix_identity(&setup);
  polygon_init(&phold[3]);
  polygon_copy(&phold[3], &p[1]);
  matrix_shear2D(&setup, 20, 30);
  matrix_rotateZ(&setup, cos(-5.94), sin(-5.94));
  matrix_translate2D(&setup, 170, 95);
  matrix_xformPolygon(&setup, &phold[3]);

  matrix_identity(&setup);
  polygon_init(&phold[4]);
  polygon_copy(&phold[4], &p[1]);
  matrix_scale2D(&setup, 20,20);
  matrix_rotateZ(&setup, cos(-1.9), sin(-1.9));
  matrix_translate2D(&setup, 325, 225);
  matrix_xformPolygon(&setup, &phold[4]);

  //Draw House
  
  matrix_identity(&setup);
  polygon_init(&phold[7]);
  polygon_copy(&phold[7], &p[2]);
  matrix_scale2D(&setup, 30,40);
  matrix_translate2D(&setup, 380, 400);
  matrix_xformPolygon(&setup, &phold[7]);

  matrix_identity(&setup);
  polygon_init(&phold[5]);
  polygon_copy(&phold[5], &p[2]);
  matrix_scale2D(&setup, 30,60);
  matrix_translate2D(&setup, 400, 380);
  matrix_xformPolygon(&setup, &phold[5]);

  matrix_identity(&setup);
  polygon_init(&phold[6]);
  polygon_copy(&phold[6], &p[2]);
  matrix_scale2D(&setup, 100,100);
  matrix_translate2D(&setup, 300, 340);
  matrix_xformPolygon(&setup, &phold[6]);

  matrix_identity(&setup);
  polygon_init(&phold[10]);
  polygon_copy(&phold[10], &p[1]);
  matrix_scale2D(&setup, 100,60);
  matrix_rotateZ(&setup, cos(-0.5), sin(-0.5));
  matrix_translate2D(&setup, 295, 340);
  matrix_xformPolygon(&setup, &phold[10]);

  matrix_identity(&setup);
  polygon_init(&phold[8]);
  polygon_copy(&phold[8], &p[1]);
  matrix_scale2D(&setup, 60,90);
  matrix_rotateZ(&setup, cos(-3.14/2), sin(-3.14/2));
  matrix_translate2D(&setup, 300, 500);
  matrix_xformPolygon(&setup, &phold[8]);
 
  matrix_identity(&setup);
  polygon_init(&phold[9]);
  polygon_copy(&phold[9], &p[1]);
  matrix_scale2D(&setup, 40,70);
  matrix_rotateZ(&setup, cos(-5.14), sin(-5.14));
  matrix_translate2D(&setup, 300, 440);
  matrix_xformPolygon(&setup, &phold[9]);

  //Set up the view stuff
  point_set2D( &(view.vrp), 250.0, 250.0 );
  view.dx = 1.0;
  vector_set( &(view.x), 1.0, 0.0, 0.0 );
  view.screenx = 500;
  view.screeny = 500;

  matrix_setView2D( &vtm, &view );
  printf("vtm:\n");
  matrix_print(&vtm, stdout);

  polygon_init(&pcopy);
  //loop through for the number of frames
  for(t = 0; t<nFrames; t++){
    setBlack(src);
    //go through the list of polygons
    for( i = 0; i<10; i++){
      polygon_copy( &pcopy, &phold[i]);
      //matrix_identity( &ltm );
      //matrix_scale2D( &ltm, 1.0/(t/2+1), 1.0/(t/2+1));
      
      //matrix_xformPolygon(&ltm, &pcopy);
      matrix_xformPolygon(&vtm, &pcopy);
      polygon_normalize(&pcopy);
      if (i == 0){
	polygon_drawFill(&pcopy, src, color[1]);
      }

      if((i>0 && i<5) || (i>7 && i<=9)){
	printf("draw\n");
	polygon_drawFill(&pcopy, src, color[0]);
      }	else{
	polygon_drawFill(&pcopy, src, color[0]);
      }
    }

    printf("write the image\n");
    sprintf(filename, "/export/home/vedwards/Desktop/Graphics/images/halloween/frame-%04d.ppm", t);
    image_write(src, filename);
    // translate the view across the scene
    //point_set2D( &(view.vrp), 2.0 - 2.4*(t+1)/nFrames, 2.0 - 2.4*(t+1)/nFrames );
    point_set2D( &(view.vrp), t * 10, 50 + t * 20);
    matrix_setView2D( &vtm, &view );
    //matrix_print( &vtm, stdout );

  }

  free(src);

  return(0);
}
