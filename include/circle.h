#ifndef CIRCLE_H

#define CIRCLE_H


typedef struct{
  double r; //Radius
  Point c; //Center
}Circle;

void circle_set(Circle *c, Point tc, double tr);

void circle_draw(Circle *c, Image *src, Color p);

void circle_drawFill(Circle *c, Image *src, Color p);


#endif
