#ifndef VIEW_H


#define VIEW_H

typedef struct{
  Point vrp;//center
  double dx;//width
  Vector x;//orientation
  double screenx;//num columns
  double screeny;//num rows
}View2D;

typedef struct{
  Point vrp;
  Vector vpn;
  Vector vup;
  double d;//the negative length of the vpn, related to the COP;
  double du;
  double dv;
  double f;
  double b;
  int screenx;
  int screeny;
}View3D;

/*set up a view2D object*/
void view2D_set(View2D *view, Point *vrp, double d, Vector *orientation, double x, double y);

 /*sets the vtm to be the view transformation defined by the 2D view structure*/
void matrix_setView2D(Matrix *vtm, View2D *view);

/*implements teh 3D prespective pipeline*/
void matrix_setView3D(Matrix *vtm, View3D *view);

#endif
