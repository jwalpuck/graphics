/*
  drawState.c
 
  Jack Walpuck and Torrie Edwards
  Graphics CS351
  October 28, 2014
 -----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

/*create a new DrawState structure and initalize the fields*/
DrawState *drawstate_create(void) {
  DrawState *ret = malloc(sizeof(DrawState));
  Color White;
  Point vrp;
  point_set(&vrp, 0, 0, 0, 1);
  color_set(&White, 1.0, 1.0, 1.0);
  ret->color = White;
  ret->flatColor = White;
  ret->body = White;
  ret->surface = White;
  ret->surfaceCoeff = 0;
  ret->shade = ShadeConstant;//This is absolutely wrong
  ret->zBufferflag = 0;
  ret->viewer = vrp;

  return ret;
}

/*set the color field to c*/
void drawstate_setColor(DrawState *s, Color *c) {
  s->color = *c;
}

/*set the body field to c*/
void drawstate_setBody(DrawState *s, Color *c) {
  s->body = *c;
}

/*set teh surface field to c*/
void drawstate_setSurface(DrawState *s, Color *c) {
  s->surface = *c;
}

/*set the surface coeff field to f*/
void drawstate_setSurfaceCoeff(DrawState *s, float f) {
  s->surfaceCoeff = f;
}

/*copy the DrawState data*/
void drawstate_copy(DrawState *to, DrawState *from) {
  *to = *from;
}
