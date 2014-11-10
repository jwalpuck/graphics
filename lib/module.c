/*
  module.c
 
  Jack Walpuck and Torrie Edwards

  Graphics CS 351 
  October 28, 2014
 -----------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <graphics.h>

/*allocate and return an initalized but empty Element*/
Element *element_create(void) {
  Element *ret = malloc(sizeof(Element));
  Object temp;
  temp.module = NULL;
  ret->type = ObjNone;
  ret->obj = temp;
  ret->next = NULL;
  
  return ret;
}

/*allocate an element and store a duplicate of the data pointed to by obj in the Element. Modules do not get duplicated. The function needs to handle each type of object separately in case statement. */
Element *element_init(ObjectType type, void *obj) {
  Element *ret = malloc(sizeof(Element));
  ret->type = type;

  //Depending on the ObjectType, assign the contents of ret accordingly
  switch(type) {
  case ObjNone:
    ret->obj.module = NULL;
    break;
  case ObjLine:
    ret->obj.line = *((Line *)obj);
    break;
  case ObjPoint:
    ret->obj.point = *((Point *)obj);
    break;
  case ObjPolyline: {
    polyline_init(&(ret->obj.polyline));
    polyline_copy(&(ret->obj.polyline), (Polyline *)obj);
  }
    break;
  case ObjPolygon: {
    polygon_init(&(ret->obj.polygon));
    polygon_copy(&(ret->obj.polygon), (Polygon *)obj);
  }
    break;
  case ObjIdentity:
    break;
  case ObjMatrix:
    ret->obj.matrix = *((Matrix *)obj);
    break;

  //because all of these are color types they can all be set by a color pointer.
  case ObjColor:
  case ObjBodyColor:
  case ObjSurfaceColor:
    ret->obj.color = *((Color *)obj);
    break;
  case ObjSurfaceCoeff:
    ret->obj.coeff = *((float *)obj);
    break;
  case ObjLight:
    //obj.?????????
    break;
  case ObjModule:
    ret->obj.module = obj;  
    break;
  }
  ret->next = NULL; 

  return ret;
}

/*free the element and the object it containts, as appropriate*/
void element_delete(Element *e) {
  //Do we need to free e->obj yes. Are the only two we need to check polylines and polygons?

  switch(e->type) {
  case ObjNone:
    break;
  case ObjLine:
    break;
  case ObjPoint:
    break;
  case ObjPolyline: 
    polyline_clear(&(e->obj.polyline));
    break;
  case ObjPolygon: 
    polygon_clear(&(e->obj.polygon));
    break;
  case ObjIdentity:
    break;
  case ObjMatrix:
    break;
  case ObjColor:
  case ObjBodyColor:
  case ObjSurfaceColor:
    break;
  case ObjSurfaceCoeff:
    break;
  case ObjLight:
    break;
  case ObjModule:
    break;
  }
  if(e)
    free(e);
}

/*allocate an empty module*/
Module *module_create(void) {
  Module *ret = malloc(sizeof(Module));
  ret->head = NULL;
  ret->tail = NULL;

  return ret;
}

/* clear the module's list of Elements, freeing memory as appropriate*/
void module_clear(Module *md) {
  if(md->head == NULL) //If list is empty
    return;

  Element *cur = md->head;

  //what is temp???
  while(cur->next != NULL) {
    Element *temp = (Element *)cur->next;
    element_delete(cur);
    cur = temp;
  }
  md->head = NULL;
  md->tail = NULL;
}

/*Free all the memory associated with a module, including the memory pointed to by md*/
void module_delete(Module *md){
  module_clear(md);
  if(md)
    free(md);
}

/*generic insert of an element into the module at the tail of the list*/
void module_insert(Module *md, Element *e) {
  //printf("So many\n");
  if(md->head == NULL) {
    //printf("head is null\n");
    md->head = e;
    md->tail = e;
  }
  else {
    //printf("otherwise\n");
    md->tail->next = (void *)e;
    md->tail = e;
  } 
  //printf("Questions\n");
}

/*adds a pointer to the module sub to the tail of the module's list*/
void module_module(Module *md, Module *sub) {
  Element *new = element_init(ObjModule, (void *)sub);
  module_insert(md, new);
}

/*adds p to the tail of the module's list*/
void module_point(Module *md, Point *p) {
  Element *new = element_init(ObjPoint, (void *)p);
  module_insert(md, new);
}

/*adds p to the tail of the module's list*/
void module_line(Module *md, Line *p) {
  Element *new = element_init(ObjLine, (void *)p);
  module_insert(md, new);
}

/*adds p to the tail of the module's list*/
void module_polyline(Module *md, Polyline *p) {
  Element *new = element_init(ObjPolyline, (void *)p);
  module_insert(md, new);
}

/*adds p to the tail of the module's list*/
void module_polygon(Module *md, Polygon *p) {
  Element *new = element_init(ObjPolygon, (void *)p);
  module_insert(md, new);
}

/*Object that sets the curren transformation to the identity, placed at the tail of the module's list*/
void module_identity(Module *md) {
  Element *new = element_init(ObjIdentity, NULL);
  module_insert(md, new);
}

/*Matrix operand to add a translation matrix to the tail of the module's list*/
void module_translate2D(Module *md, double tx, double ty) {
  Matrix temp;
  matrix_identity(&temp);
  matrix_translate2D(&temp, tx, ty);
  Element *new = element_init(ObjMatrix, (void *)&temp);
  module_insert(md, new);
}

/*Matrix operand to add a scale matrix to the tail of the module's list*/
void module_scale2D(Module *md, double sx, double sy) {
  Matrix temp;
  matrix_identity(&temp);
  matrix_scale2D(&temp, sx, sy);
  Element *new = element_init(ObjMatrix, (void *)&temp);
  module_insert(md, new);  
}

/*Matrix operand to add a rotation about the Z axis to the tail of the module's list*/
void module_rotateZ(Module *md, double cth, double sth) {
  Matrix temp;
  matrix_identity(&temp);
  matrix_rotateZ(&temp, cth, sth);
  Element *new = element_init(ObjMatrix, (void *)&temp);
  module_insert(md, new);
}

/*Matrix operand to add a 2D shear matrix to the tail of the module's list*/
void module_shear2D(Module *md, double shx, double shy) {
  Matrix temp;
  matrix_identity(&temp);
  matrix_shear2D(&temp, shx, shy);
  Element *new = element_init(ObjMatrix, (void *)&temp);
  module_insert(md, new);
}

/*Draw the module into the image using the given view transformation matrix [VTM], Lighting, and DrawState by traversing the list of Elements (FOR NOW Lighting will be an empty structure (DO NOT ATTEMPT THIS DIRECT WARNING FROM INSTRUCTIONS)*/
void module_draw(Module *md, Matrix *VTM, Matrix *GTM, DrawState *ds, Lighting *lighting, Image *src) {
  Matrix LTM;
  matrix_identity(&LTM);

  //Start with head of module
  Element *iter = md->head;

  //Iterate through module
  while(iter != NULL) {
    switch(iter->type) {
    case ObjNone:
      break;
    case ObjLine: {
      Line temp;
      temp = iter->obj.line;
      matrix_xformLine(&LTM, &temp);
      matrix_xformLine(GTM, &temp);
      matrix_xformLine(VTM, &temp);
      line_normalize(&temp);
      line_draw(&temp, src, ds->color);
    }
      break;
    case ObjPoint: {
      Point temp;
      matrix_xformPoint(&LTM, &iter->obj.point, &temp);
      matrix_xformPoint(GTM, &temp, &temp);
      matrix_xformPoint(VTM, &temp, &temp);   
      point_normalize(&temp);
      point_draw(&temp, src, ds->color);
    }
      break;
    case ObjPolyline: {
      Polyline *temp = polyline_create();
      polyline_copy(temp, &iter->obj.polyline);
      *temp = iter->obj.polyline;
      matrix_xformPolyline(&LTM, temp);
      matrix_xformPolyline(GTM, temp);
      matrix_xformPolyline(VTM, temp);
      polyline_normalize(temp);
      polyline_draw(temp, src, ds->color);
      polyline_free(temp);
    }
      break;
    case ObjPolygon: {
      Polygon *temp = polygon_create();
      polygon_copy(temp, &iter->obj.polygon);
      matrix_xformPolygon(&LTM, temp);
      matrix_xformPolygon(GTM, temp);
      matrix_xformPolygon(VTM, temp);
      polygon_normalize(temp);
      if (ds->shade == ShadeFrame){
	polygon_draw(temp, src, ds->color);
      }else{
	polygon_drawFill(temp, src, ds->color);
      }
      polygon_free(temp);
    }
      break;
    case ObjIdentity:
      matrix_identity(&LTM);
      break;
    case ObjMatrix:
      matrix_multiply( &iter->obj.matrix, &LTM, &LTM);
      break;
    case ObjColor:
      ds->color = iter->obj.color;
      break;
    case ObjBodyColor:
      ds->body = iter->obj.color;
      break;
    case ObjSurfaceColor:
      ds->surface = iter->obj.color;
      break;
    case ObjSurfaceCoeff:
      ds->surfaceCoeff = iter->obj.coeff;
      break;
    case ObjLight:
      lighting = NULL;
      break;
    case ObjModule: {
      Matrix GTMtemp;
      DrawState *temp = drawstate_create();
      drawstate_copy(temp, ds);
      matrix_multiply(GTM, &LTM, &GTMtemp);
      module_draw((Module *)(iter->obj.module), VTM, &GTMtemp, temp, lighting, src);
    }
      break;
    }
    //Update iter
    iter = iter->next;
  }
}

/*-----------------------------------3D functions------------------------------*/

/*Matrix operand to add a 3D translation to the module*/
void module_translate(Module *md, double tx, double ty, double tz) {
  Matrix temp;
  matrix_identity(&temp);
  matrix_translate(&temp, tx, ty, tz);
  Element *new = element_init(ObjMatrix, (void *)&temp);
  module_insert(md, new);
}

/*Matrix operand to add a 3D scale to the Module*/
void module_scale(Module *md, double sx, double sy, double sz) {
  Matrix temp;
  matrix_identity(&temp);
  matrix_scale(&temp, sx, sy, sz);
  Element *new = element_init(ObjMatrix, (void *)&temp);
  module_insert(md, new);
}

/*Matrix operand to add a rotation about the X-axis to the Module*/
void module_rotateX(Module *md, double cth, double sth) {
  Matrix temp;
  matrix_identity(&temp);
  matrix_rotateX(&temp, cth, sth);
  Element *new = element_init(ObjMatrix, (void *)&temp);
  module_insert(md, new);
}

/*Matrix operand to add a rotation about the Y-axis to the Module*/
void module_rotateY(Module *md, double cth, double sth) {
  Matrix temp;
  matrix_identity(&temp);
  matrix_rotateY(&temp, cth, sth);
  Element *new = element_init(ObjMatrix, (void *)&temp);
  module_insert(md, new);
}

/*Matrix operand to add a rotation that orients to teh orthonormal axes u, v,w*/
void module_rotateXYZ(Module *md, Vector *u, Vector *v, Vector *w) {
  Matrix temp;
  matrix_identity(&temp);
  matrix_rotateXYZ(&temp, u, v, w);
  Element *new = element_init(ObjMatrix, (void *)&temp);
  module_insert(md, new);
}

/*Adds a unit cube, axis-aligned and centered on zero to the Module. If solid is zero, add only lines. If solid is non-zero use polygons. Make sure each polygon has surface normals defined for it*/
void module_cube(Module *md, int solid) {

  if(solid ==  0){
    //build a cube using lines. 
    Line edges;
    Point vertex[8];

    //set the points for the verticies of the cube
    point_set( &vertex[0], -1, -1, -1, 1 );
    point_set( &vertex[1],  1, -1, -1, 1 );
    point_set( &vertex[2],  1,  1, -1, 1 );
    point_set( &vertex[3], -1,  1, -1, 1 );

    point_set( &vertex[4], -1, -1,  1, 1 );
    point_set( &vertex[5],  1, -1,  1, 1 );
    point_set( &vertex[6],  1,  1,  1, 1 );
    point_set( &vertex[7], -1,  1,  1, 1 );
    
    line_set(&edges, vertex[0], vertex[1]);  //1
    module_line(md, &edges);

    line_set(&edges, vertex[0], vertex[3]); //2
    module_line(md, &edges);

    line_set(&edges, vertex[0], vertex[4]); //3
    module_line(md, &edges);

    line_set(&edges, vertex[1], vertex[2]); //4
    module_line(md, &edges);

    line_set(&edges, vertex[1], vertex[5]); //5
    module_line(md, &edges);

    line_set(&edges, vertex[2], vertex[3]); //6
    module_line(md, &edges);

    line_set(&edges, vertex[2], vertex[6]); //7
    module_line(md, &edges);

    line_set(&edges, vertex[3], vertex[7]); //8
    module_line(md, &edges);
  
    line_set(&edges, vertex[4], vertex[5]); //9
    module_line(md, &edges);

    line_set(&edges, vertex[4], vertex[7]); //10
    module_line(md, &edges);

    line_set(&edges, vertex[5], vertex[6]); //11
    module_line(md, &edges);

    line_set(&edges, vertex[6], vertex[7]); //12
    module_line(md, &edges);
  }else{
      //build a cube using polygons. 
      Point pt[4];
      Polygon p;

      polygon_init( &p );
      point_set3D( &pt[0], -1, -1, -1 );
      point_set3D( &pt[1], -1, -1,  1 );
      point_set3D( &pt[2], -1,  1,  1 );
      point_set3D( &pt[3], -1,  1, -1 );
      polygon_set( &p, 4, pt );
      module_polygon( md, &p );

      point_set3D( &pt[0], 1, -1, -1 );
      point_set3D( &pt[1], 1, -1,  1 );
      point_set3D( &pt[2], 1,  1,  1 );
      point_set3D( &pt[3], 1,  1, -1 );
      polygon_set( &p, 4, pt );
      module_polygon( md, &p );

      point_set3D( &pt[0], -1, -1, -1 );
      point_set3D( &pt[1], -1, -1,  1 );
      point_set3D( &pt[2],  1, -1,  1 );
      point_set3D( &pt[3],  1, -1, -1 );
      polygon_set( &p, 4, pt );
      module_polygon( md, &p );

      point_set3D( &pt[0], -1, 1, -1 );
      point_set3D( &pt[1], -1, 1,  1 );
      point_set3D( &pt[2],  1, 1,  1 );
      point_set3D( &pt[3],  1, 1, -1 );
      polygon_set( &p, 4, pt );
      module_polygon( md, &p );

      point_set3D( &pt[0], -1, -1, -1 );
      point_set3D( &pt[1], -1,  1, -1 );
      point_set3D( &pt[2],  1,  1, -1 );
      point_set3D( &pt[3],  1, -1, -1 );
      polygon_set( &p, 4, pt );
      module_polygon( md, &p );

      point_set3D( &pt[0], -1, -1, 1 );
      point_set3D( &pt[1], -1,  1, 1 );
      point_set3D( &pt[2],  1,  1, 1 );
      point_set3D( &pt[3],  1, -1, 1 );
      polygon_set( &p, 4, pt );
      module_polygon( md, &p ); 

      polygon_clear( &p );
  }
}

/* make a unit cylinder, method written by Bruce Maxwell.*/
void module_cylinder(Module *md, int sides){
  Polygon p;
  Point xtop, xbot;
  double x1, x2, z1, z2;
  int i;

  polygon_init( &p );
  point_set3D( &xtop, 0, 1.0, 0.0 );
  point_set3D( &xbot, 0, 0.0, 0.0 );
  // make a fan for the top and bottom sides
  // and quadrilaterals for the sides
  for(i=0;i<sides;i++) {			
    Point pt[4];

    x1 = cos( i * M_PI * 2.0 / sides );
    z1 = sin( i * M_PI * 2.0 / sides );
    x2 = cos( ( (i+1)%sides ) * M_PI * 2.0 / sides );
    z2 = sin( ( (i+1)%sides ) * M_PI * 2.0 / sides );

    point_copy( &pt[0], &xtop );
    point_set3D( &pt[1], x1, 1.0, z1 );
    point_set3D( &pt[2], x2, 1.0, z2 );

    polygon_set( &p, 3, pt );
    module_polygon( md, &p );
    point_copy( &pt[0], &xbot );
    point_set3D( &pt[1], x1, 0.0, z1 );
    point_set3D( &pt[2], x2, 0.0, z2 );

    polygon_set( &p, 3, pt );
    module_polygon( md, &p );

    point_set3D( &pt[0], x1, 0.0, z1 );
    point_set3D( &pt[1], x2, 0.0, z2 );
    point_set3D( &pt[2], x2, 1.0, z2 );
    point_set3D( &pt[3], x1, 1.0, z1 );
    
    polygon_set( &p, 4, pt );
    module_polygon( md, &p );
  }
  polygon_clear( &p );
}

/* make a unit pyrmaid*/
void module_pyramid(Module *md, int solid){
  Point pt[4];
  Point sides[3];
  Polygon p;
  
  //Base
  polygon_init( &p );
  point_set3D( &pt[0], -1, -1, 1 );
  point_set3D( &pt[1], -1, -1, -1 );
  point_set3D( &pt[2], 1,  -1,  -1 );
  point_set3D( &pt[3], 1,  -1, 1 );
  polygon_set( &p, 4, pt );
  module_polygon( md, &p );

  //Sides
  point_set3D( &sides[0],-1 ,-1 ,1 );
  point_set3D( &sides[1],0 ,0 ,0 );
  point_set3D( &sides[2],-1 ,-1 , -1);
  polygon_set( &p, 3, sides);
  module_polygon( md, &p );
  
  point_set3D( &sides[0],-1 ,-1 ,-1 );
  point_set3D( &sides[1],0 ,0,0 );
  point_set3D( &sides[2],1 ,-1 , -1);
  polygon_set( &p, 3, sides);
  module_polygon( md, &p );

  point_set3D( &sides[0],1 ,-1 ,-1 );
  point_set3D( &sides[1],0 ,0 ,0 );
  point_set3D( &sides[2],1 , -1 , 1);
  polygon_set( &p, 3, sides);
  module_polygon( md, &p );

  point_set3D( &sides[0],1 ,-1 ,1 );
  point_set3D( &sides[1],0 ,0,0 );
  point_set3D( &sides[2],-1 ,-1 , 1);
  polygon_set( &p, 3, sides);
  module_polygon( md, &p );

  polygon_clear( &p );
}

/*make a unit diamond*/
void module_diamond(Module *md, int solid){
  Point pt[4];
  Point sides[3];
  Polygon p;
  
  //Base
  polygon_init( &p );
  point_set3D( &pt[0], -1, -1, 1 );
  point_set3D( &pt[1], -1, -1, -1 );
  point_set3D( &pt[2], 1,  -1,  -1 );
  point_set3D( &pt[3], 1,  -1, 1 );
  polygon_set( &p, 4, pt );
  module_polygon( md, &p );

  //Sides
  point_set3D( &sides[0],-1 ,-1 ,1 );
  point_set3D( &sides[1],0 ,0 ,0 );
  point_set3D( &sides[2],-1 ,-1 , -1);
  polygon_set( &p, 3, sides);
  module_polygon( md, &p );
  
  point_set3D( &sides[0],-1 ,-1 ,-1 );
  point_set3D( &sides[1],0 ,0,0 );
  point_set3D( &sides[2],1 ,-1 , -1);
  polygon_set( &p, 3, sides);
  module_polygon( md, &p );

  point_set3D( &sides[0],1 ,-1 ,-1 );
  point_set3D( &sides[1],0 ,0 ,0 );
  point_set3D( &sides[2],1 , -1 , 1);
  polygon_set( &p, 3, sides);
  module_polygon( md, &p );

  point_set3D( &sides[0],1 ,-1 ,1 );
  point_set3D( &sides[1],0 ,0,0 );
  point_set3D( &sides[2],-1 ,-1 , 1);
  polygon_set( &p, 3, sides);
  module_polygon( md, &p );

  //Sides
  point_set3D( &sides[0],-1 ,-1 ,1 );
  point_set3D( &sides[1],0 ,-2 ,0);
  point_set3D( &sides[2],-1 ,-1 , -1);
  polygon_set( &p, 3, sides);
  module_polygon( md, &p );
  
  point_set3D( &sides[0],-1 ,-1 ,-1 );
  point_set3D( &sides[1],0 ,-2,0);
  point_set3D( &sides[2],1 ,-1 , -1);
  polygon_set( &p, 3, sides);
  module_polygon( md, &p );

  point_set3D( &sides[0],1 ,-1 ,-1 );
  point_set3D( &sides[1],0, -2, 0);
  point_set3D( &sides[2],1 , -1 , 1);
  polygon_set( &p, 3, sides);
  module_polygon( md, &p );

  point_set3D( &sides[0],1 ,-1 ,1 );
  point_set3D( &sides[1],0, -2, 0);
  point_set3D( &sides[2],-1 ,-1 , 1);
  polygon_set( &p, 3, sides);
  module_polygon( md, &p );

  polygon_clear( &p );
}

/*draws a circle with polygons*/
void module_circle(Module *md, int radius){
  Point resolution[100];
  Polygon circ;
  int k;
  polygon_init(&circ);
  for (k = 0; k< 100; k++){
    point_set2D(&(resolution[k]),radius*cos( k * 2.0 * M_PI / (float)100), 
		radius*sin( k * 2.0 * M_PI /(float)100));

  }
  polygon_set( &circ, 100, &(resolution[0]));
  module_polygon(md, &circ);
  polygon_clear(&circ);
}

/*draw a circle with  polylines*/
void module_circleLines(Module *md, int radius) {
  Point resolution[100];
  Polyline circ;
  int k;
  polyline_init(&circ);
  for (k = 0; k< 100; k++){
    point_set2D(&(resolution[k]),radius*cos( k * 2.0 * M_PI / (float)100), 
		radius*sin( k * 2.0 * M_PI /(float)100));

  }
  polyline_set( &circ, 100, &(resolution[0]));
  module_polyline(md, &circ);
  polyline_clear(&circ);
}



/*adds the foreground color value to the tail of the module's list*/
void module_color(Module *md, Color *c) {
  Element *new = element_init(ObjColor, (void *)c);
  module_insert(md, new);
}


/* use the de Casteljau algorithm to subdivide the Bezier curve divisions times, then add the lines connecting the control points to the module. For example if divisions is one the four original bezier curve control points will be used to generate eight control points, one level of subdividsion, and then the algorithm will create and insert seven lines into the module to connect the eight control points*/
void module_bezierCurve(Module *md, BezierCurve *b, int divisions){
  Line l[3];
  Point temp[8];
  int i;

  //Base case
  if(divisions == 0){
    line_set(&l[0], b->control[0], b->control[1]);
    module_line(md, &l[0]);
    
    line_set(&l[1], b->control[1], b->control[2]);
    module_line(md, &l[1]);
    
    line_set(&l[2], b->control[2], b->control[3]);
    module_line(md, &l[2]);
    //point_print(&(b->control), stdout);
  }else{
    BezierCurve bezCurveA;
    BezierCurve bezCurveB;
    
    //Initalize new bezier curves
    bezierCurve_init(&bezCurveA);
    bezierCurve_init(&bezCurveB);

    //Do DeCast Algorithm on them
    deCastAlg(&(b->control[0]), &(temp[0]));

    //Set up the new bezier curves
    bezierCurve_set(&bezCurveA, &temp[0]);
    bezierCurve_set(&bezCurveB, &temp[4]);
    
    //Make recursive call
    module_bezierCurve(md, &bezCurveA, divisions - 1);
    module_bezierCurve(md, &bezCurveB, divisions - 1);
  }
}

/*use the de Casteljau algorithm to subdivide the Bezier surface divisions times, then draw either the lines connecting the contorl points if solid is zero, or draw triangles connecting the surface. For example if divisions is one, the sixteen original Bezier curve control points wil lbe used to generate 64 control poitns and four new Bezier surfaces, 1 level of subdivision, and then the algorithm will draw lines or triangles to connect adjacent control points.*/ 
void module_bezierSurface(Module *md, BezierSurface *b, int divisions, int solid){
  int i, j; 
  Line l[24];
  Polygon p;
  Point vertex[3];
  Point A[16];
  Point A2[16];
  Point B[32];
  Point C[64];
  Point Afinal[16], Bfinal[16], Cfinal[16], Dfinal[16];
  int count;

  //line
  if(divisions == 0){
    if(solid == 0){
      // Draw Vertical lines
      for(i = 4; i < 16; i++){
      	line_set(&l[i-4], b->control[i-4], b->control[i]);
      	module_line(md, &l[i-4]);
      }

      //Draw horizontal lines
      for(i = 1; i < 16; i++){
	if(i % 4 == 0 )
	  continue;
	line_set(&l[i-1], b->control[i-1], b->control[i]);
	module_line(md, &l[i-1]);
      }

    }else{
      //Draw polygon stuff
      for(i = 0; i< 3; i++){
	polygon_init( &p );

	// draw the first column of triangles!
	point_copy(&vertex[0], &(b->control[0+i]));
	point_copy(&vertex[1], &(b->control[4+i]));
	point_copy(&vertex[2], &(b->control[5+i]));
	polygon_set(&p, 3, &vertex[0]);
	module_polygon(md, &p);

	point_copy(&vertex[0], &(b->control[4+i]));
	point_copy(&vertex[1], &(b->control[8+i]));
	point_copy(&vertex[2], &(b->control[9+i]));
	polygon_set(&p, 3, &vertex[0]);
	module_polygon(md, &p);

	point_copy(&vertex[0], &(b->control[8+i]));
	point_copy(&vertex[1], &(b->control[12+i]));
	point_copy(&vertex[2], &(b->control[13+i]));
	polygon_set(&p, 3, &vertex[0]);
	module_polygon(md, &p);

	point_copy(&vertex[0], &(b->control[0+i]));
	point_copy(&vertex[1], &(b->control[5+i]));
	point_copy(&vertex[2], &(b->control[1+i]));
	polygon_set(&p, 3, &vertex[0]);
	module_polygon(md, &p);

	point_copy(&vertex[0], &(b->control[4+i]));
	point_copy(&vertex[1], &(b->control[9+i]));
	point_copy(&vertex[2], &(b->control[5+i]));
	polygon_set(&p, 3, &vertex[0]);
	module_polygon(md, &p);

	point_copy(&vertex[0], &(b->control[8+i]));
	point_copy(&vertex[1], &(b->control[13+i]));
	point_copy(&vertex[2], &(b->control[9+i]));
	polygon_set(&p, 3, &vertex[0]);
	module_polygon(md, &p);

	polygon_clear( &p);
      }
   }
  }else{
      //Recursive stuff
      BezierSurface bezSurfaceA;
      BezierSurface bezSurfaceB;
      BezierSurface bezSurfaceC;
      BezierSurface bezSurfaceD;

      //initalize the new surfaces one for each quadrant
      bezierSurface_init(&bezSurfaceA);
      bezierSurface_init(&bezSurfaceB);
      bezierSurface_init(&bezSurfaceC);
      bezierSurface_init(&bezSurfaceD);

      //Set up a temp list of vertices that are organized by column
      count = 0;
      for(j = 0; j < 4; j++){
	for(i = 0; i< 4; i++){
	  A[count++] = b->control[i*4+j]; 
	}
      }

      //Run deCast algorithm on the column points getting 32 points
      for(i = 0; i < 4; i++){ 
	deCastAlg(&(A[i*4]), &(B[i * 8]));
      }

      //Set up a new temp list of vertices that are organized by row
      count = 0;
      for(j = 0; j < 8; j++){
	for(i = 0; i < 4; i++){
	  A2[count++] = B[i*8+j];
	}
      }

      //Run deCast algorithm on the row points ending with a total of 64 points
      for(i = 0; i < 8; i++){
	deCastAlg(&(A2[i*4]), &(C[i * 8]));
      }

      //Split up the points into the appropriate quadrants
      for(i = 0; i < 4; i++){
	for(j = 0; j< 4; j++){
	  Afinal[i * 4 + j] = C[i * 8 + j];
	  Bfinal[i * 4 + j] = C[i * 8+(j + 4)];
	  Cfinal[i * 4 + j] = C[(i + 4) * 8 + j];
	  Dfinal[i * 4 + j] = C[(i + 4) * 8 + (j + 4)];
	}
      }

      //set the new bezier surfaces
      bezierSurface_set(&bezSurfaceA, &Afinal[0]);
      bezierSurface_set(&bezSurfaceB, &Bfinal[0]);
      bezierSurface_set(&bezSurfaceC, &Cfinal[0]);
      bezierSurface_set(&bezSurfaceD, &Dfinal[0]);

      //Make the 4 recursive calls
      module_bezierSurface(md, &bezSurfaceA, divisions - 1, solid);
      module_bezierSurface(md, &bezSurfaceB, divisions - 1, solid);
      module_bezierSurface(md, &bezSurfaceC, divisions - 1, solid);
      module_bezierSurface(md, &bezSurfaceD, divisions - 1, solid);
  }
 
}
