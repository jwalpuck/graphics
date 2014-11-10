/*
 This is the library of functions for the view pipeline

October 16, 2014 
Graphics CS 351
----------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

void view2D_set(View2D *view, Point *vrp, double d, Vector *orientation, double x, double y){
  view->dx = d; 
  view->vrp = *vrp;
  view->x = *orientation;
  view->screenx = x;
  view->screeny = y;
}

/*define the view transformation matrix from the 2D view structure*/
void matrix_setView2D(Matrix *vtm, View2D *view){
  double dy0;
  Point vrp0 = view->vrp;
  double dx0 = view->dx;
  Vector x0 = view->x;
  double screenx0 = view->screenx;
  double screeny0 = view->screeny;
  
  //Initialize the vtm
  matrix_identity(vtm);

  //Translate the vtm to the origin
  matrix_translate2D(vtm, -1*vrp0.val[0], -1*vrp0.val[1]);

  //rotate the vtm by the orientation angle
  matrix_rotateZ(vtm, x0.val[0], x0.val[1]);

  // determine the correct y screen value, we calculate this so that the numbers do not turn out all wonky. 
  dy0= (screeny0*dx0)/screenx0;

  // scale the matrix to the screen coordinates
  matrix_scale2D(vtm,screenx0/dx0, -1*screeny0/dy0);

  //translate the vtm to the screen! 
  matrix_translate2D(vtm,screenx0/2, screeny0/2);
}

/*set up the 3D viewing pipeline, 
NOTE: when the function returns the vtm should contain the complete view matrix*/
void matrix_setView3D(Matrix *vtm, View3D *view){
  Vector u0;
  Point vrp0 = view->vrp;
  Vector vpn0 = view->vpn;
  Vector vup0 = view->vup;
  double d0 = view->d;//the negative length of the vpn, related to the COP;
  double du0 = view->du;
  double dv0 = view->dv;
  double f0 = view->f;
  double b0 = view->b;
  int screenx0 = view->screenx;
  int screeny0 = view->screeny;
  //Point center; Do we really need this. Is it used anywhere else??
  //ANSWER: view->d is directly tied to the center, and we need to shift d to account for the change. 

  //initalize to the identity
  matrix_identity(vtm);
  
  //Step 1: Move vrp to the origin
  matrix_translate(vtm, -1 * vrp0.val[0],-1*vrp0.val[1], -1*vrp0.val[2]);
  //printf("translate by vrp\n");
  //matrix_print(vtm, stdout);

  //Step 2: Create an orthonormal coordinate system, and normalize the resulting vectors
  vector_set(&u0, 0.0, 0.0, 0.0);
  vector_cross(&vup0, &vpn0, &u0);
  vector_cross(&vpn0, &u0, &vup0);

  vector_normalize(&u0);
  vector_normalize(&vpn0);
  vector_normalize(&vup0);
  
  //printf("VECTORS\n");
  // vector_print(&u0, stdout);
  //vector_print(&vup0, stdout);
  //vector_print(&vpn0, stdout);

  //Step 3: align the axses with the orientation angle
  matrix_rotateXYZ(vtm, &u0, &vup0, &vpn0);
  // printf("ROTATE XYZ\n");
  // matrix_print(vtm, stdout);

  //Step 4: move the COP to the origin, Translate by (0, 0, d);
  matrix_translate(vtm, 0, 0, d0);
  //matrix_print(vtm, stdout);

  //Step 5: set the Back plane distance; 
  b0 = d0+b0;

  //Step 6: scale teh canonical view volume (CVV)
  matrix_scale(vtm, 2*d0/(b0*du0), 2*d0/(b0*dv0), 1/b0);
  // printf("Scale to CVV\n");
  // matrix_print(vtm, stdout);

  //Step 7: Calculate the new project distance (the new d!)
  d0 = d0/b0;
  
  //Step 8: Project the scene onto the view plane
  Matrix temp;
  matrix_identity(&temp);
  temp.m[3][2] = 1.0 / d0;
  temp.m[3][3] = 0;
  matrix_multiply(&temp, vtm, vtm);

  //printf("After weird step\n");
  //matrix_print(vtm, stdout);
  
 
  //Step 9a: scale the view volume to screen size

  matrix_scale(vtm, (-1*screenx0)/(2*d0), (-1*screeny0)/ (2*d0), 1);
  //printf("scale to screen\n");
  //matrix_print(vtm, stdout);
  //Step 9b: translate the view volume to the screen. 
  matrix_translate(vtm, screenx0/2.0, screeny0/2.0, 0);
  //matrix_print(vtm, stdout);
}
