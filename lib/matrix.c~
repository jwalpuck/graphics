/*
 * Jack Walpuck and Torrie Edwards
 * matrix.c

CS 351 Graphics
October 16, 2014
----------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

/* Set the vector to (x, y, z, 0.0) */
void vector_set(Vector *v, double x, double y, double z) {
  v->val[0] = x;
  v->val[1] = y;
  v->val[2] = z;
  v->val[3] = 0;
}

/* Print out the Vector to stream fp in a pretty form */
void vector_print(Vector *v, FILE *fp) {
  if(fp){
    fprintf(fp, "[%.1f %.1f %.1f %.1f]\n\n", v->val[0], v->val[1], v->val[2],v->val[3]);
  }
}

/* Copy the src Vector into the dest Vector */
void vector_copy(Vector *dest, Vector *src) {
  *dest = *src;
}


/* Returns the Euclidean length of the vector, assuming homogeneous coord = 1.0 */
double vector_length(Vector *v) {
  return sqrt(v->val[0] * v->val[0] + v->val[1] * v->val[1] + v->val[2] * v->val[2]);
}

/* Normalize the Vector to unit length */
void vector_normalize(Vector *v) {
  double length = sqrt(v->val[0] * v->val[0] + v->val[1] * v->val[1] + v->val[2] * v->val[2]);
  v->val[0] = v->val[0] / length;
  v->val[1] = v->val[1] / length;
  v->val[2] = v->val[2] / length;
}

/* Returns the scalar product of a and b */
double vector_dot(Vector *a, Vector *b) {
  return a->val[0] * b->val[0] + a->val[1] * b->val[1] + a->val[2] * b->val[2];
}

/* Calculates the cross product (vector product) of a and b, putting result in c */
void vector_cross(Vector *a, Vector *b, Vector *c) {
  c->val[0] = (a->val[1]*b->val[2]) - (a->val[2]*b->val[1]);
  c->val[1] = (a->val[2]*b->val[0]) - (a->val[0]*b->val[2]);
  c->val[2] = (a->val[0]*b->val[1]) - (a->val[1]*b->val[0]);
}

/*----------------------------------------------------------------------------------------------*/


/*print out the matrix in 4x4 arrangement with blank line below*/
void matrix_print(Matrix *m, FILE *fp){
  if(fp){
   fprintf(fp, "[[%.1f, %.1f, %.1f, %.1f]\n", m->m[0][0], m->m[0][1], m->m[0][2], m->m[0][3]);
   fprintf(fp, "[%.1f, %.1f, %.1f, %.1f]\n", m->m[1][0], m->m[1][1], m->m[1][2], m->m[1][3]);
   fprintf(fp, "[%.1f, %.1f, %.1f, %.1f]\n", m->m[2][0], m->m[2][1], m->m[2][2], m->m[2][3]);
   fprintf(fp, "[%.1f, %.1f, %.1f, %.1f]]\n\n", m->m[3][0], m->m[3][1], m->m[3][2], m->m[3][3]);
  }
}

/*set the matrix to all zeros*/
void matrix_clear(Matrix *m){
  int i,j;
  for(i=0; i<4;i++){
    for(j = 0; j<4; j++){
      m->m[i][j] = 0.0;
    }
  }
}

/*set the matrix to the identity matrix*/ 
void matrix_identity(Matrix *m){
  int i,j;
  for(i=0; i<4;i++){
    for(j = 0; j<4; j++){
      m->m[i][j] = 0.0;
    }
  }
  m->m[0][0] = 1.0;
  m->m[1][1] = 1.0;
  m->m[2][2] = 1.0;
  m->m[3][3] = 1.0;
}

/*Return the element of the matrix at row r, column c*/
double matrix_get(Matrix *m, int r, int c){
  return m->m[r][c];
}

/*Copy the src matrix into the dest matrix*/
void matrix_copy(Matrix *dest, Matrix *src){
  *dest = *src;
}

/*set teh element of the matrix at row r, column c to v*/
void matrix_set(Matrix *m, int r, int c, double v){
  m->m[r][c] = v;
}

/* Transpose the matrix m in place */
void matrix_transpose(Matrix *m){
  Matrix mtemp;
  int i, j;
  matrix_copy(&mtemp, m);
  for(i=0; i<4; i++){
    for (j = 0; j<4; j++){
      m->m[j][i] = mtemp.m[i][j];
    }
  }
}

/*Multiply left and right and put the result in m*/
void matrix_multiply(Matrix *left, Matrix *right, Matrix *m){
  Matrix mTemp;
  int i;
  for (i = 0; i< 4; i++){
        mTemp.m[i][0] = left->m[i][0]*right->m[0][0]+ left->m[i][1]*right->m[1][0]+ left->m[i][2]*right->m[2][0]+ left->m[i][3]*right->m[3][0];
	mTemp.m[i][1] = left->m[i][0]*right->m[0][1]+ left->m[i][1]*right->m[1][1]+ left->m[i][2]*right->m[2][1]+ left->m[i][3]*right->m[3][1];
	mTemp.m[i][2] = left->m[i][0]*right->m[0][2]+ left->m[i][1]*right->m[1][2]+ left->m[i][2]*right->m[2][2]+ left->m[i][3]*right->m[3][2];
	mTemp.m[i][3] = left->m[i][0]*right->m[0][3]+ left->m[i][1]*right->m[1][3]+ left->m[i][2]*right->m[2][3]+ left->m[i][3]*right->m[3][3];
  }

  *m = *&mTemp;
}

/* Transform the point p by the matrix m and put the result in q. P and Q must be different variables */
void matrix_xformPoint(Matrix *m, Point *p, Point *q){
  Point temp;
  int i;
  for (i = 0; i< 4; i++){
    temp.val[i] = m->m[i][0]*p->val[0]+m->m[i][1]*p->val[1]+m->m[i][2]*p->val[2] +m->m[i][3]*p->val[3] ;
  }
  *q = temp;
}


/* Transform the vector p by the matrix m and put the result in q. P and Q must be different variables */
void matrix_xformVector(Matrix *m, Vector *p, Vector *q){
  Vector temp;
  int i;
  for (i = 0; i< 4; i++){
    temp.val[i] = m->m[i][0]*p->val[0]+m->m[i][1]*p->val[1]+m->m[i][2]*p->val[2] +m->m[i][3]*p->val[3] ;
  }
  *q= temp; 
}

/* Transform the points and surface normals (if they exist) in the polygon by the matrix m */
void matrix_xformPolygon(Matrix *m, Polygon *p){
  double temp1, temp2, temp3, temp4;
  int i, k;
  for( k = 0; k< p->nVertex; k++){
    temp1 = p->vertex[k].val[0];
    temp2 = p->vertex[k].val[1];
    temp3 = p->vertex[k].val[2];
    temp4 = p->vertex[k].val[3];
    for (i = 0; i<4; i++){
      p->vertex[k].val[i] = m->m[i][0]*temp1+m->m[i][1]*temp2+m->m[i][2]*temp3+ m->m[i][3]*temp4;
    }
  }
}

/* Transform the points in the Polyling p by the matrix m */
void matrix_xformPolyline(Matrix *m, Polyline *p){
  double temp1, temp2, temp3, temp4;
  int i, k;
  for( k = 0; k< p->numVertex; k++){
    temp1 = p->vertex[k].val[0];
    temp2 = p->vertex[k].val[1];
    temp3 = p->vertex[k].val[2];
    temp4 = p->vertex[k].val[3];
    for (i = 0; i<4; i++){
      p->vertex[k].val[i] = m->m[i][0]*temp1+m->m[i][1]*temp2+m->m[i][2]*temp3+ m->m[i][3]*temp4;
    }
  }
}

/* Transform the points in line by the matrix m */
void matrix_xformLine(Matrix *m, Line *line){
  int i;
  Line temp; 
  for (i = 0; i< 4; i++){
    temp.a.val[i] = m->m[i][0]*line->a.val[0]+m->m[i][1]*line->a.val[1]+m->m[i][2]*line->a.val[2] +m->m[i][3]*line->a.val[3] ;
    temp.b.val[i] = m->m[i][0]*line->b.val[0]+m->m[i][1]*line->b.val[1]+m->m[i][2]*line->b.val[2] +m->m[i][3]*line->b.val[3] ;
  }
  line_copy(line, &temp);
}


/* Premultiply the matrix by a scale matrix parameterized by sx and sy */
void matrix_scale2D(Matrix *m, double sx, double sy){
  //int i; 
  Matrix temp; 
  matrix_identity(&temp);

  temp.m[0][0] = sx; 
  temp.m[1][1] = sy; 

  matrix_multiply( &temp, m, m);
}

/* Premultiply the matrix by a Z-axis rotation matrix parameterized by cos and sin, where theta is the angle of rotation about the Z-axis */
void matrix_rotateZ(Matrix *m, double cth, double sth){
  Matrix temp; 
  matrix_identity(&temp);

  temp.m[0][0] = cth; 
  temp.m[0][1] = -sth;
  temp.m[1][0] = sth;
  temp.m[1][1] = cth;

  matrix_multiply( &temp, m, m);

}

/* Premultiply the matrix by a 2D translation matrix parameterized by tx and ty */
void matrix_translate2D(Matrix *m, double tx, double ty){
  Matrix temp; 
  matrix_identity(&temp);

  temp.m[0][3] = tx;
  temp.m[1][3] = ty;

  matrix_multiply(&temp, m, m);
}

/* Premultiply the matrix by a 2D shear matrix pararmeterized by shx and shy */
void matrix_shear2D(Matrix *m, double shx, double shy){
  Matrix temp; 
  matrix_identity(&temp);

  temp.m[0][1] = shx;
  temp.m[1][0] = shy;

  matrix_multiply(&temp, m, m);
}

/* Premultiply the matrix by a translation matrix parameterized by tx, ty and tz */
void matrix_translate(Matrix *m, double tx, double ty, double tz){
  Matrix temp; 
  matrix_identity(&temp);

  temp.m[0][3] = tx;
  temp.m[1][3] = ty;
  temp.m[2][3] = tz;

  matrix_multiply(&temp, m, m);
}

/* Premultiply the matrix by a scale matrix parameterized by sx, sy, sz */
void matrix_scale(Matrix *m, double sx, double sy, double sz){
  Matrix temp; 
  matrix_identity(&temp);

  temp.m[0][0] = sx; 
  temp.m[1][1] = sy;
  temp.m[2][2] = sz;

  matrix_multiply(&temp, m, m);

}

/* Premultiply the matrix by an X-axis rotation parameterized by cos and sin, where theta is tha angle of rotation about the X-axis */
void matrix_rotateX(Matrix *m, double cth, double sth){
  Matrix temp; 
  matrix_identity(&temp);

  temp.m[1][1] = cth; 
  temp.m[1][2] = -sth;
  temp.m[2][1] = sth;
  temp.m[2][2] = cth;

  matrix_multiply(&temp, m, m);
  
}

/* Premultiply the matrix by an Y-axis rotation parameterized by cos and sin, where theta is tha angle of rotation about the Y-axis */
void matrix_rotateY(Matrix *m, double cth, double sth){
  Matrix temp; 
  matrix_identity(&temp);

  temp.m[0][0] = cth; 
  temp.m[0][2] = sth;
  temp.m[2][0] = -sth;
  temp.m[2][2] = cth;

  matrix_multiply(&temp, m, m); 
}

/* Premultiply the matrix by an XYZ-axis rotation matrix parameterized by the vectors u, v, and w, where the three vectors represent an orthonormal 3D basis */
void matrix_rotateXYZ(Matrix *m, Vector *u, Vector *v, Vector *w){
  Matrix mtemp;
  int i; 
  for(i = 0; i < 4; i++) {
    mtemp.m[0][i] = u->val[i];
    mtemp.m[1][i] = v->val[i];
    mtemp.m[2][i] = w->val[i];
    mtemp.m[3][i] = i == 3 ? 1 : 0;
  }
  matrix_multiply( &mtemp,m, m);
}

/* Premultiply the matrix by a shear Z matrix parameterized by shx and shy */
void matrix_shearZ(Matrix *m, double shx, double shy){
  Matrix temp; 
  matrix_identity(&temp);

  temp.m[0][2] = shx;
  temp.m[1][2] = shy;

  matrix_multiply(&temp, m, m);

}

/* Premultiply the matrix by a perspective matrix parameterized by d */
void matrix_perspective(Matrix *m, double d){
  Matrix temp; 
  matrix_identity(&temp);

  temp.m[3][2] = 1/d; 

  matrix_multiply( &temp, m, m); 

}
