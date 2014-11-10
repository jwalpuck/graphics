/*
  This is the library of functions for color. 

  September 25, 2014
  Graphics CS 351
----------------------------------------------------------------------------- */
#include <stdio.h>
#include "color.h"

void color_copy(Color *to, Color *from) {
  /*returns a copy of the color data*/
  *to = *from;
}

void color_set(Color *to, float r, float g, float b) {
  /*sets the color data*/
  to->c[0] = r;
  to->c[1] = g;
  to->c[2] = b;
}
