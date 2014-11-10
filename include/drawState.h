#ifndef DRAWSTATE_H

#define DRAWSTATE_H

typedef enum {
  ShadeFrame, // draw only the borders of objs, including polygons
  ShadeConstant, // draw objs using current foreground color, fill polygons
  ShadeDepth, // draw objs usign their depth val
  ShadeFlat, // draw obj using shading calculations (each polygon constant val)
  ShadeGouraud, // draws objs using gouraud shading
  ShadePhong, // draws objects using phongs shading
}ShadeMethod; 

typedef struct{
  Color color;  //foreground color
  Color flatColor; //flat-fill a polygon based on shading calculation
  Color body; // body reflection color
  Color surface;  //surface reflection color
  float surfaceCoeff; //float to represent the shinniness of the surface
  ShadeMethod shade; 
  int zBufferflag; // whether to use z-buffer hidden surface removal
  Point viewer; // point representing the view location in 3D (IDENTICAL TO VRP)
}DrawState;

/*create a new DrawState structure and initalize the fields*/
DrawState *drawstate_create(void);

/*set the color field to c*/
void drawstate_setColor(DrawState *s, Color *c);

/*set the body field to c*/
void drawstate_setBody(DrawState *s, Color *c);

/*set teh surface field to c*/
void drawstate_setSurface(DrawState *s, Color *c);

/*set the surface coeff field to f*/
void drawstate_setSurfaceCoeff(DrawState *s, float f);

/*copy the DrawState data*/
void drawstate_copy(DrawState *to, DrawState *from);


#endif
