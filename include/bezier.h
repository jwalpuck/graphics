#ifndef BEZIER_H

#define BEZIER_H

typedef struct{
  Point control[4];
  int zBuffer; 
}BezierCurve;

typedef struct{
  Point control[16];
  int zBuffer;
}BezierSurface;


/*sets the zbuffer flag to 1 and the curve poitns to the X-axis between 0 and 1*/
void bezierCurve_init(BezierCurve *b);

/*sets the zbuffer flag to 1 and the surface to the X-Z plane between (0,0) and (1,1)*/
void bezierSurface_init(BezierSurface *b);

/*sets the contorl points of the BezierCurve to the four points in the vlist array*/
void bezierCurve_set(BezierCurve *b, Point *vlist);

/*sets the control points of the BezierSurface to the 16 poitns in the vlist array*/
void bezierSurface_set(BezierSurface *b, Point *vlist);

/*sets the z-buffer flag to the given value*/
void bezierCurve_zBuffer(BezierCurve *p, int flag);

/*sets the z_bffer flag to the given value*/
void bezierSurface_zBuffer(BezierCurve *p, int flag);

void deCastAlg(Point *a, Point *b);

/*draws the Bezier curve, given in screen coordinates, into the image using the given color. The function should be adaptive so that it uses an appropriate number of line segments to draw the curve. For example if the bounding box of the control points is less than 10 pixels in the largest dimension, then it is reasonable to draw the lines between teh control poitns as an approximation to the curve*/
void bezierCurve_draw(BezierCurve *b, Image *src, Color c); 


#endif
