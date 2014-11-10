#ifndef MODULE_H

#define MODULE_H

typedef enum { // example of an enumberated type
  ObjNone,
  ObjLine, 
  ObjPoint,
  ObjPolyline,
  ObjPolygon,
  ObjIdentity,
  ObjMatrix,
  ObjColor,
  ObjBodyColor,
  ObjSurfaceColor,
  ObjSurfaceCoeff,
  ObjLight,
  ObjModule,
} ObjectType;

//OPTION 2 
typedef union {
  Point point;
  Line line; 
  Polyline polyline;
  Polygon polygon; 
  Matrix matrix; 
  Color color; 
  float coeff; 
  void *module; 
}Object; 

typedef struct{
  ObjectType type;
  Object obj; 
  void *next;
}Element;

typedef struct {
  Element *head;   // pointer to the head of the linked list
  Element *tail;   // keep around a pointer o fthe last object 
}Module; 

typedef struct{
  int nLights;
} Lighting;

/* ---------------------Generic Functions and 2D Module Stuff --------------*/

/*allocate and return an initalized but empty Element*/
Element *element_create(void);

/*allocate an element and store a duplicate of the data pointed to by obj in the Element. Modules do not get duplicated. The function needs to handle each type of object separately in case statement. */
Element *element_init(ObjectType type, void *obj);

/*free the element adn the object it containts, as appropriate*/
void element_delete(Element *e);

/*allocate an empty module*/
Module *module_create(void);

/* clear the module's list of Elements, freeing memory as appropriate*/
void module_clear(Module *md);

/*Free all the memory associated with a module, including the memory pointed to by md*/ 
void module_delete(Module *md);

/*generic insert of an element into the module at the tail of the list*/
void module_insert(Module *md, Element *e);

/*adds a pointer to the module sub to the tail of the module's list*/
void module_module(Module *md, Module *sub);

/*adds p to the tail of the module's list*/
void module_point(Module *md, Point *p);

/*adds p to the tail of the module's list*/
void module_line(Module *md, Line *p);

/*adds p to the tail of the module's list*/
void module_polyline(Module *md, Polyline *p);

/*adds p to the tail of the module's list*/
void module_polygon(Module *md, Polygon *p);

/*Object that sets the curren transformation to the identity, placed at the tail of the module's list*/
void module_identity(Module *md);

/*Matrix operand to add a translation matrix to the tail of the module's list*/
void module_translate2D(Module *md, double tx, double ty);

/*Matrix operand to add a scale matrix to the tail of the module's list*/
void module_scale2D(Module *md, double sx, double sy);

/*Matrix operand to add a rotation about the Z axis to the tail of the module's list*/
void module_rotateZ(Module *md, double cth, double sth);

/*Matrix operand to add a 2D shear matrix to the tail of the module's list*/
void module_shear2D(Module *md, double shx, double shy);

/*Draw the module into the image using the given view transformation matrix [VTM], Lighting, and DrawState by traversing the list of Elements (FOR NOW Lighting will be an empty structure (DO NOT ATTEMPT THIS DIRECT WARNING FROM INSTRUCTIONS)*/
void module_draw(Module *md, Matrix *VTM, Matrix *GTM, DrawState *ds, Lighting *lighting, Image *src);

/*-----------------------------------3D functions------------------------------*/

/*Matrix operand to add a 3D translation to the module*/
void module_translate(Module *md, double tx, double ty, double tz);

/*Matrix operand to add a 3D scale to the Module*/
void module_scale(Module *md, double sx, double sy, double sz);

/*Matrix operand to add a rotation about the X-axis to the Module*/
void module_rotateX(Module *md, double cth, double sth);

/*Matrix operand to add a rotation about the Y-axis to the Module*/
void module_rotateY(Module *md, double cth, double sth);

/*Matrix operand to add a rotation that orients to teh orthonormal axes u, v,w*/
void module_rotateXYZ(Module *md, Vector *u, Vector *v, Vector *w);

/*Adds a unit cube, axis-aligned and centered on zero to the Module. If solid is zero, add only lines. If solid is non-zero use polygons. Make sure each polygon has surface normals defined for it*/
void module_cube(Module *md, int solid);

/* make a unit cylinder, method written by Bruce Maxwell.*/
void module_cylinder(Module *md, int sides);

/* make a unit pyrmaid*/
void module_pyramid(Module *md, int solid);

/*make a unit diamond*/
void module_diamond(Module *md, int solid);

/*draw a circle with polygons*/
void module_circle(Module *md, int radius);

/*draw a circle with polylines*/
void module_circleLines(Module *md, int radius);

/*--------------------------------Shading/Color-------------------------------*/

/*adds the foreground color value to the tail of the module's list*/
void module_color(Module *md, Color *c);

/*------------------------------ Bezier Curve --------------------------------*/

/* use the de Casteljau algorithm to subdivide the Bezier curve divisions times, then add the lines connecting the control points to the module. For example if divisions is one the four original bezier curve control points will be sued to generate eight control points, one level of subdividsion, and then the algorithm wil lcreate and insert seven lines into the module to connect the eight control points*/
void module_bezierCurve(Module *md, BezierCurve *b, int divisions);

/*use the de Casteljau algorithm to subdivide the Bezier surface divisions times, then draw either the lines connecting the contorl points if solid is zero, or draw triangles connecting the surface. For example if divisions is one, the sixteen original Bezier curve control points wil lbe used to generate 64 control poitns and four new Bezier surfaces, 1 level of subdivision, and then the algorithm will draw lines triangles to connect adjacent control points.*/ 
void module_bezierSurface(Module *md, BezierSurface *b, int divisions, int solid);

#endif
