/*
This is a library of functions for an ellipse

September 25, 2014
Graphics CS 351
------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"
#include "color.h"
#include "point.h"
#include "line.h"
#include "ellipse.h"

#define PI 3.1415926

void ellipse_set(Ellipse *e, Point tc, double ta, double tb, double tan){
  /* initialize an ellipse to location tc and radii ta and tb*/
  e->c = tc;
  e->ra = ta; //major axis raduis
  e->rb = tb; // minor axis radius
  e->a = tan;
}

void ellipse_draw(Ellipse *e, Image *src, Color p){
  /* draw an ellipse into src using color p*/
  double x, y, px, py, pz;
  double xCenter, yCenter;
  double Rx, Ry;

  /*set center values */
  xCenter = e->c.val[0];
  yCenter = e->c.val[1];

  /*Major axis: Rx*/
  Rx = e->ra;
  /*Minor axis: Ry*/
  Ry = e->rb;

  /*when you are not trying to rotate the ellipse you will be using Bresenhan's
    Algorithm. It considers the cartesian equation for an ellipse and uses an 
    updated error term to decide on which pixel to draw up or to the side. We 
    will start drawing in the third quadrant to help account for pixel error*/
   /*This algorithm, for when a = 0 comes from: ellipseMidpoint, Chapter 3, pg 109-110*/ 
  if(e->a == 0){
    /*set initial x and y values*/
    x= -1; 
    y= -Ry;

    /*initial starting error terms!*/
    px = 2*Rx*Ry;
    py = 2*Rx*Rx*-y;
 
    printf("x: %f y: %f \n", x,y);
    printf("px: %f py: %f\n", px, py);
    printf("Major Axis: %f Minor Axis: %f\n", Rx, Ry);

    /*set up p, this is necessray because we have to draw an entire 
      quadrant of the ellipse. The symmetry here is not as nice as in a 
      circle*/
    pz = (Ry*Ry-(Rx*Rx*Ry)+(Rx*Rx*0.25)+Ry*Ry+py);
 
    /*this sets the color of the initial points*/
    image_setColor(src, xCenter+x, yCenter+y, p);
    image_setColor(src, xCenter-x-1, yCenter-y-1, p);

    image_setColor(src, xCenter+x, yCenter+y, p);
    image_setColor(src, xCenter-x-1, yCenter+y, p);
    image_setColor(src, xCenter+x, yCenter-y-1, p);
    image_setColor(src, xCenter-x-1, yCenter-y-1, p);

    image_setColor(src, xCenter+x, yCenter+y, p);
    image_setColor(src, xCenter-x-1, yCenter+y, p);
    image_setColor(src, xCenter+x, yCenter-y-1, p);
    image_setColor(src, xCenter-x-1, yCenter-y-1, p);


    /*wile the points are still below the tangent line with a -1 slope value
      decrement over x*/
    printf("Starting the first half of the ellipse\n");
    while (px<py){
      x--; // decrement x
      px = px+ 2*Ry*Ry;
      if (pz<0){
	pz += Ry*Ry+px;
      }else{
	y++;// increment y
	py = py- 2*Rx*Rx;
	pz += Ry*Ry +px-py;
      }
      /*set the pixel color in the 4 quadrants*/
      image_setColor(src, xCenter+x, yCenter+y, p);
      image_setColor(src, xCenter-x-1, yCenter+y, p);
      image_setColor(src, xCenter+x, yCenter-y-1, p);
      image_setColor(src, xCenter-x-1, yCenter-y-1, p);
    }

    /* when the points pass the tangent line with slope of -1 now incrementing 
       over y*/
    pz = Ry*Ry *(x*x +x) +Rx*Rx* (y*y-2*y +1) -Rx*Rx *Ry*Ry +Rx*Rx -py;

    printf("Starting the second half of the ellipse\n");
    while (y<0){
      y++;//increment y
      py = py - 2*Rx*Rx;
      if (pz>0){
	pz += Rx*Rx-py;
      }else{
	x--;//decrement x
	px +=  2*Ry *Ry;
	pz += Rx*Rx-py+px;
      }
      /*set the pixel color in the 4 quadrants*/

      image_setColor(src, xCenter+x, yCenter+y, p);
      image_setColor(src, xCenter-x-1, yCenter+y, p);
      image_setColor(src, xCenter+x, yCenter-y-1, p);
      image_setColor(src, xCenter-x-1, yCenter-y-1, p);
    }
    printf("YAY you have drawn an ellipse at angle 0\n");

  }else{

    printf("You are rotating the ellipse\n");
    /*We are going to use a different method to rotate the ellipse*/
    /*First: we will build a list of points on the boundary of the ellipse
      where at the further regions there are more points and we will ultimately
      connect the lines together to make an ellipse.*/

    Point *holdPoints; 
    Point pt;
    double rmax, numPoints, stepSize;
    double x1, y1, x2, y2;
    double xR1, yR1, xR2, yR2, step;
    double angle;
    Line l1;
    int k, m;
    
    /*pick which is bigger the Major axis or the Minor axis*/
    if (Rx >Ry){
      rmax = Rx;
    }else{
      rmax = Ry;
    }

    /*convert the angle to polar coordinates*/
    angle = (e->a)*(PI/180);
    printf("angle: %f\n", angle);

    /*determine the step size based on the fact that we will have Rmax number 
     of points*/
    stepSize = 1/(rmax);
    numPoints = rmax*0.5;

    /*malloc space for an array of Points*/
    holdPoints = malloc(sizeof(Point)*(numPoints));
    
    printf("number of points %f\n", numPoints);
    printf("size of a step %f\n:", stepSize);
    
    /*get the initial point*/
    x1 = Rx*cos(0);
    y1 = Ry*sin(0);
    point_set2D(&pt, x1,y1);

    /*add that point to the list*/
    holdPoints[0] = pt;

    printf("x1: %f y1: %f\n", x1, y1);

    /*loop through the number of points and deterine the point value for 
      the incremented step size*/
    for(k = 1; k<numPoints; k++){
      step = stepSize*(double)k;
      x2 = (holdPoints[k-1].val[0] * cos(step))-((Rx/Ry)*holdPoints[k-1].val[1]*sin(step));
      y2 = ((Ry/Rx)*holdPoints[k-1].val[0]*sin(step))+(holdPoints[k-1].val[1]*cos(step));
      point_set2D(&pt, x2, y2);
      
      holdPoints[k]=pt;
    }

    /*breaking down matrix math into two equations apply a rotation and translation to the list of points 
      and draw the points at there new location connecting the lines between them*/
    for(m=0; m+1<numPoints; m++){
      xR1 = holdPoints[m].val[0]*cos(angle)+holdPoints[m].val[1]*sin(angle)*-1 +xCenter;
      yR1 = holdPoints[m].val[0]*sin(angle)+holdPoints[m].val[1]*cos(angle)+yCenter;
      xR2 = holdPoints[m+1].val[0]*cos(angle)+holdPoints[m+1].val[1]*sin(angle)*-1 +xCenter;
      yR2 = holdPoints[m+1].val[0]*sin(angle)+holdPoints[m+1].val[1]*cos(angle)+yCenter;
      line_set2D(&l1, xR1, yR1, xR2, yR2);
      line_draw(&l1, src, p);
    }
    /*free malloced space for the holdPoints array*/
    free(holdPoints);
  }

}


void ellipse_drawFill(Ellipse *e, Image *src, Color p){
  /* draw an ellipse into src using color p*/
  double x, y, px, py, pz;
  double xCenter, yCenter;
  double Rx, Ry;
  double left;

  xCenter= e->c.val[0];
  yCenter = e->c.val[1];

  /*Major axis: Rx*/
  Rx = e ->ra;
  /*Minor axis: Ry*/
  Ry = e ->rb;
  /*initial starting points!*/
  x = -1;
  y = -Ry;
  px = 2*Rx*Ry;
  py = 2*Rx*Rx*-y;
 
  printf("x: %f y: %f \n", x,y);
  printf("px: %f py: %f\n", px, py);
  printf("Major Axis: %f Minor Axis: %f\n", Rx, Ry);

  /*set up p, this is necessray because we have to draw an entire 
    quadrant of the ellipse. The symmetry here is not as nice as in a 
    circle*/
   left = y;
    while(left<-y){
      image_setColor(src,xCenter, yCenter+left,p);
      image_setColor(src,xCenter, yCenter+left,p) ;
      image_setColor(src,xCenter+x, yCenter+left,p);
      image_setColor(src,xCenter-x, yCenter+left,p);
      left++;
    }

  /*This algorithm comes from: ellipseMidpoint, Chapter 3, pg 109-110*/ 
  pz = (Ry*Ry-(Rx*Rx*Ry)+(Rx*Rx*0.25)+Ry*Ry+py);

  /*wile the points are still below the tangent line with a -1 slope value
    increment over x*/
  printf("Starting the first half of the ellipse\n");
  while (px<py){
    x--; // decrement x
    px = px+2*Ry*Ry;
    if (pz<0){
      pz += Ry*Ry+px;
    }else{
      y++;// increment y
      py = py -2*Rx*Rx;
      pz +=Ry*Ry +px-py;
    }
    /*set the pixel color in the 4 quadrants by drawing a line to 
      corresponding point*/
   left = y;
    while(left<-y){
      image_setColor(src,xCenter+x, yCenter+left,p);
      image_setColor(src,xCenter-x, yCenter+left,p);
      left++;
    }
  }
  /* when the points pass the tangent line with slope of -1 now incrementing 
     over y instead of x*/
  pz = Ry*Ry *(x*x +x) +Rx*Rx* (y*y-2*y +1) -Rx*Rx *Ry*Ry +Rx*Rx -py;
  printf("Starting the second half of the ellipse\n");
  while (y<0){
    y++;//increment y
    py = py-2*Rx*Rx;
    if (pz>0){
      pz += Rx*Rx-py;
    }else{
      x--;//decrement x
      px +=  2 *Ry *Ry;
      pz += Rx*Rx-py+px;
    }
    /*set the pixel color in the 4 quadrants by drawing a line to 
      corresponding point*/
   left = y;
    while(left<-y){
      image_setColor(src,xCenter+x, yCenter+left,p);
      image_setColor(src,xCenter-x, yCenter+left,p);
      left++;
    }
  }
  printf("Yay you have drawn a filled ellipse\n");
}
