/*
 * Jack Walpuck
 * music.c
 * 10/27/14
 */

#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

int main(int argc, char *argv[]) {
  Image *src;

  Module *scene;
  Module *v1, *v2;
  Module *note, *hnote;
  
  Color black;
  Color white;

  Matrix vtm, gtm;
  int rows = 500;
  int cols = 500;
  View3D view;
  DrawState *ds;

  Line l;
  Point p1, p2;

  int i, j;

  char filename[256];

  //Set up the image
  src = image_create(rows, cols);

  //Initialize our colors
  color_set(&white, 1.0, 1.0, 1.0);
  color_set(&black, 0.0, 0.0, 0.0);

  //Make the image white
  for(i = 0; i < cols; i++) {
    for(j = 0; j < rows; j++) {
      image_setColor(src, i, j, white);
    }
  }

  //Initialize the drawState
  ds = drawstate_create();
  ds->shade = ShadePhong;
  
  

  //Set up the view
  point_set3D(&(view.vrp), 0, 0, 300); 
  vector_set(&(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2]);
  vector_set(&(view.vup), 0, 1.0, 0);

  view.d = 600; 
  view.du = 10; 
  view.dv = view.du * (float)rows / cols;
  view.f = 0; 
  view.b = 5; 
  view.screenx = rows; 
  view.screeny = cols;

  matrix_setView3D(&vtm, &view);
  matrix_identity(&gtm);

  /***********************************************************/
  /** Create module note:: An ellipse with a vertical stem **/
  /*********************************************************/
  note = module_create();
  module_color(note, &black);
  //Create the stem
  point_set2D(&p1, 2.0, 0.0);
  point_set2D(&p2, 2.0, 6.0);
  line_set(&l, p1, p2);
  module_line(note, &l);
  //Make the head of the note
  module_scale(note, 2, 1, 1);
  module_circle(note, 1);

  /********************************************************************************/
  /** Create module hnote: An ellipse constructed of lines with a vertical stem **/
  /******************************************************************************/
  hnote = module_create();
  module_color(hnote, &black);
  //Create the stem
  point_set2D(&p1, 2.0, 0.0);
  point_set2D(&p2, 2.0, 6.0);
  line_set(&l, p1, p2);
  module_line(hnote, &l);
  //Make the head of the note
  module_scale(hnote, 2, 1, 1);
  module_circleLines(hnote, 1);

  /***************************************************************/
  /** Create module v1:: 5 horizontal lines with notes on them **/
  /*************************************************************/
  v1 = module_create();
  module_color(v1, &black);

  //Line 1
  point_set2D(&p1, 0, 0.0);
  point_set2D(&p2, 1000.0, 0.0);
  line_set(&l, p1, p2);
  module_line(v1, &l);

  //Line 2
  point_set2D(&p1, 0, 1.0);
  point_set2D(&p2, 1000.0, 1.0);
  line_set(&l, p1, p2);
  module_line(v1, &l);

  //Line 3
  point_set2D(&p1, 0, 2.0);
  point_set2D(&p2, 1000.0, 2.0);
  line_set(&l, p1, p2);
  module_line(v1, &l);

  //Line 4
  point_set2D(&p1, 0, 3.0);
  point_set2D(&p2, 1000.0, 3.0);
  line_set(&l, p1, p2);
  module_line(v1, &l);

  //Line 5
  point_set2D(&p1, 0, 4.0);
  point_set2D(&p2, 1000.0, 4.0);
  line_set(&l, p1, p2);
  module_line(v1, &l);

  //Add notes:: space notes by dx = 0.5, each step is dy = 1
  //Scale by -1, -1, 1 to get stem direction down (kind of)
  module_scale(v1, 0.5, 0.5, 1);
  //C4
  module_translate(v1, 5, -1, 0);
  module_module(v1, note);
  //Create ledger line
  point_set2D(&p1, 3.5, 0);
  point_set2D(&p2, -3.5, 0);
  line_set(&l, p1, p2);
  module_line(v1, &l);
  //D4
  module_translate(v1, 5, 0.5, 0);
  module_module(v1, note); 
  //E4
  module_translate(v1, 5, 0.5, 0);
  module_module(v1, note);
  //F4
  module_translate(v1, 5, 0.5, 0);
  module_module(v1, note);
  //G4
  module_translate(v1, 5, 0.5, 0);
  module_module(v1, note);
  //A4
  module_translate(v1, 5, 0.5, 0);
  module_module(v1, note);
  //C4
  module_translate(v1, 5, -2.5, 0);
  module_module(v1, note); 
  //Create ledger line
  point_set2D(&p1, 3.5, 0);
  point_set2D(&p2, -3.5, 0);
  line_set(&l, p1, p2);
  module_line(v1, &l);
  //E4
  module_translate(v1, 5, 1.0, 0);
  module_module(v1, note);
  //C4 
  module_translate(v1, 5, -1.0, 0);
  module_module(v1, note);
  //Create ledger line
  point_set2D(&p1, 3.5, 0);
  point_set2D(&p2, -3.5, 0);
  line_set(&l, p1, p2);
  module_line(v1, &l);
  //Create ledger line
  point_set2D(&p1, 3.5, 0);
  point_set2D(&p2, -3.5, 0);
  line_set(&l, p1, p2);
  module_line(v1, &l);
  //C4
  module_translate(v1, 5, 0.0, 0);
  module_module(v1, note);
  //Create ledger line
  point_set2D(&p1, 3.5, 0);
  point_set2D(&p2, -3.5, 0);
  line_set(&l, p1, p2);
  module_line(v1, &l);
  //B3
  module_translate(v1, 5, -0.5, 0);
  module_module(v1, hnote);
  //Create ledger line
  point_set2D(&p1, 3.5, 1.0);
  point_set2D(&p2, -3.5, 1.0);
  line_set(&l, p1, p2);
  module_line(v1, &l);

  //Next phrase
  //C4
  module_translate(v1, 5, 0.5, 0);
  module_module(v1, note);
  //Create ledger line
  point_set2D(&p1, 3.5, 0);
  point_set2D(&p2, -3.5, 0);
  line_set(&l, p1, p2);
  module_line(v1, &l);
  //D4
  module_translate(v1, 5, 0.5, 0);
  module_module(v1, note); 
  //E4
  module_translate(v1, 5, 0.5, 0);
  module_module(v1, note);
  //F4
  module_translate(v1, 5, 0.5, 0);
  module_module(v1, note);
  //G4
  module_translate(v1, 5, 0.5, 0);
  module_module(v1, note);
  //A4
  module_translate(v1, 5, 0.5, 0);
  module_module(v1, note);  
  //E5
  module_translate(v1, 5, 2.0, 0);
  module_rotateX(v1, -1, 0); 
  module_rotateZ(v1, -1, 0);
  module_rotateX(v1, -1, 0);
  module_translate(v1, 180, 7.0, 0);
  module_module(v1, note);
  //D5
  module_translate(v1, 5, -0.5, 0);
  module_module(v1, note);
  //C5
  module_translate(v1, 5, -0.5, 0);
  module_module(v1, note);
  //B4 -- note + hnote
  module_translate(v1, 5, -0.5, 0);
  module_module(v1, hnote);

  /***************************************************************/
  /** Create module v2:: 5 horizontal lines with notes on them **/
  /*************************************************************/
  v2 = module_create();
  module_color(v2, &black);

  //Line 1
  point_set2D(&p1, 0, 0.0);
  point_set2D(&p2, 1000.0, 0.0);
  line_set(&l, p1, p2);
  module_line(v2, &l);

  //Line 2
  point_set2D(&p1, 0, 1.0);
  point_set2D(&p2, 1000.0, 1.0);
  line_set(&l, p1, p2);
  module_line(v2, &l);

  //Line 3
  point_set2D(&p1, 0, 2.0);
  point_set2D(&p2, 1000.0, 2.0);
  line_set(&l, p1, p2);
  module_line(v2, &l);

  //Line 4
  point_set2D(&p1, 0, 3.0);
  point_set2D(&p2, 1000.0, 3.0);
  line_set(&l, p1, p2);
  module_line(v2, &l);

  //Line 5
  point_set2D(&p1, 0, 4.0);
  point_set2D(&p2, 1000.0, 4.0);
  line_set(&l, p1, p2);
  module_line(v2, &l);

  //Add notes:: space notes by dx = 0.5, each step is dy = 1
  //Scale by -1, -1, 1 to get stem direction down (kind of)
  module_scale(v2, 0.5, 0.5, 1);
  //A3
  module_translate(v2, 5, -2, 0);
  module_module(v2, note);
  //Create ledger line 1
  point_set2D(&p1, 3.5, 0);
  point_set2D(&p2, -3.5, 0);
  line_set(&l, p1, p2);
  module_line(v2, &l);
  //Create ledger line 2
  point_set2D(&p1, 3.5, 2.0);
  point_set2D(&p2, -3.5, 2.0);
  line_set(&l, p1, p2);
  module_line(v2, &l);
  //B3
  module_translate(v2, 5, 0.5, 0);
  module_module(v2, note); 
  //Create ledger line
  point_set2D(&p1, 3.5, 1.0);
  point_set2D(&p2, -3.5, 1.0);
  line_set(&l, p1, p2);
  module_line(v2, &l);
  //C4
  module_translate(v2, 5, 0.5, 0);
  module_module(v2, note);
  //Create ledger line
  point_set2D(&p1, 3.5, 0);
  point_set2D(&p2, -3.5, 0);
  line_set(&l, p1, p2);
  module_line(v2, &l);
  //D4
  module_translate(v2, 5, 0.5, 0);
  module_module(v2, note);
  //E4
  module_translate(v2, 5, 0.5, 0);
  module_module(v2, note);
  //F4
  module_translate(v2, 5, 0.5, 0);
  module_module(v2, note);
  //A3
  module_translate(v2, 5, -2.5, 0);
  module_module(v2, note); 
  //Create ledger line 1
  point_set2D(&p1, 3.5, 0);
  point_set2D(&p2, -3.5, 0);
  line_set(&l, p1, p2);
  module_line(v2, &l);
  //Create ledger line 2
  point_set2D(&p1, 3.5, 2.0);
  point_set2D(&p2, -3.5, 2.0);
  line_set(&l, p1, p2);
  module_line(v2, &l);
  //C4
  module_translate(v2, 5, 1.0, 0);
  module_module(v2, note);
  //Create ledger line
  point_set2D(&p1, 3.5, 0);
  point_set2D(&p2, -3.5, 0);
  line_set(&l, p1, p2);
  module_line(v2, &l);
  //A3 
  module_translate(v2, 5, -1.0, 0);
  module_module(v2, note);
  //Create ledger line 1
  point_set2D(&p1, 3.5, 0);
  point_set2D(&p2, -3.5, 0);
  line_set(&l, p1, p2);
  module_line(v2, &l);
  //Create ledger line 2
  point_set2D(&p1, 3.5, 2);
  point_set2D(&p2, -3.5, 2);
  line_set(&l, p1, p2);
  module_line(v2, &l);
  //A3
  module_translate(v2, 5, 0.0, 0);
  module_module(v2, note);
  //Create ledger line 1
  point_set2D(&p1, 3.5, 0);
  point_set2D(&p2, -3.5, 0);
  line_set(&l, p1, p2);
  module_line(v2, &l);
  //Create ledger line 2
  point_set2D(&p1, 3.5, 2);
  point_set2D(&p2, -3.5, 2);
  line_set(&l, p1, p2);
  module_line(v2, &l);
  //G3
  module_translate(v2, 5, -0.5, 0);
  module_module(v2, hnote);
  //Create ledger line 1
  point_set2D(&p1, 3.5, 1);
  point_set2D(&p2, -3.5, 1);
  line_set(&l, p1, p2);
  module_line(v2, &l);
  //Create ledger line 2
  point_set2D(&p1, 3.5, 3);
  point_set2D(&p2, -3.5, 3);
  line_set(&l, p1, p2);
  module_line(v2, &l);

  //Next phrase
  //A3
  module_translate(v2, 5, 0.5, 0);
  module_module(v2, note);
  //Create ledger line 1
  point_set2D(&p1, 3.5, 0);
  point_set2D(&p2, -3.5, 0);
  line_set(&l, p1, p2);
  module_line(v2, &l);
  //Create ledger line 2
  point_set2D(&p1, 3.5, 2);
  point_set2D(&p2, -3.5, 2);
  line_set(&l, p1, p2);
  module_line(v2, &l);
  //B4
  module_translate(v2, 5, 0.5, 0);
  module_module(v2, note); 
  //Create ledger line
  point_set2D(&p1, 3.5, 1);
  point_set2D(&p2, -3.5, 1);
  line_set(&l, p1, p2);
  module_line(v2, &l);
  //C4
  module_translate(v2, 5, 0.5, 0);
  module_module(v2, note);
  //Create ledger line
  point_set2D(&p1, 3.5, 0);
  point_set2D(&p2, -3.5, 0);
  line_set(&l, p1, p2);
  module_line(v2, &l);
  //D4
  module_translate(v2, 5, 0.5, 0);
  module_module(v2, note);
  //E4
  module_translate(v2, 5, 0.5, 0);
  module_module(v2, note);
  //F4
  module_translate(v2, 5, 0.5, 0);
  module_module(v2, note);  
  //A4
  module_translate(v2, 15, 1.5, 0);
  module_module(v2, note);
  //G4 -- note + hnote
  module_translate(v2, 5, -0.5, 0);
  module_module(v2, hnote);
  //C5
  module_translate(v2, -15, 1.0, 0);
  module_rotateX(v2, -1, 0); 
  module_rotateZ(v2, -1, 0);
  module_rotateX(v2, -1, 0);
  module_translate(v2, 180, 5.0, 0);
  module_module(v2, note);
  //B4
  module_translate(v2, 5, -0.5, 0);
  module_module(v2, note);


  

  /*****************************************************/
  /** Create module scene:: Contains multiple staves **/
  /***************************************************/
  scene = module_create();
  module_translate(scene, -20, 0, 0);
  module_module(scene, v1);
  module_translate(scene, 0, -10, 0);
  module_module(scene, v2);
  //module_translate(scene, 0, 10, 0);
  
  /**************************/
  /** End module creation **/
  /************************/

  //Draw scene
  for(i = 0; i < 500; i++) {
    point_set3D(&(view.vrp), (i / 5.0) - 20, 3, 300); //Scroll to the right
    if(i > 250 && i < 350) {
      //Pan out
      view.d -= 5;
      //printf("%f\n", view.d);
    }
    matrix_setView3D(&vtm, &view);
    module_draw(scene, &vtm, &gtm, ds, NULL, src);
    //printf("Writing image\n");
    //image_write(src, "music_test.ppm");

    sprintf(filename, "/export/home/vedwards/Desktop/Graphics/images/music/music_frame%04d.ppm", i);
    image_write(src, filename);
    image_reset(src);
    //Make the image white
    int k;
    for(k = 0; k < cols; k++) {
      for(j = 0; j < rows; j++) {
	image_setColor(src, k, j, white);
      }
    }
  }

  //Clear modules
  module_delete(scene);
  module_delete(v1);
  module_delete(v2);
  module_delete(note);
  module_delete(hnote);

  //Free remaining memory
  free(ds);
  image_free(src);

  return 0;
}
