#ifndef COLOR_H

#define COLOR_H

typedef struct {
  float c[3];
} Color;

/* Copy the color data */
void color_copy(Color *to, Color *from);

/* Set the color data */
void color_set(Color *to, float r, float g, float b);

#endif
