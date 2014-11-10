/*
This is the image library it holds all of the functions that can be used on a data type structure  
At the end of this file are two noise functions, a Mandelbrot function, and a Julia set function. 
	
Torrie Edwards
Graphics CS351
September 18, 2014

-----------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ppmIO.h>
#include "color.h"
#include "image.h"

/*CONSUCTORS AND DECONSTRUCTORS*/
/*I am choosing to use a 2D pointer system because I think it will be easier in the long run*/
/* creates an image structure, where it allocates a place in memory for the new image
sets the rows, columns and data fields, and allows for indexing to look like the 
following: image[i][j] (this is because using a pointer pointing to a list of pointers
pointing at an image*/
Image *image_create(int rows, int cols){
  int i;
  Image *src = NULL;
  src = malloc(sizeof(Image)); /*sets aside some memory*/
  if (rows<=0 || cols<=0){
    printf("Rows and Columns must be greater than 0\n");
    src->data = NULL;
    src->rows = 0;
    src->cols = 0;
    return(src);
  }else{
    printf("allocate size of image\n");
    src->data = malloc(sizeof(FPixel*)*rows);/*creates a column of pointers*/
    src->data[0] = malloc(sizeof(FPixel)*rows*cols);/*attaches those pointers to the image*/
			 
     /*loops through the first column of pixels and sets
     pointers to them for eaiser indexing*/
     for(i = 1; i<rows; i++){
	src->data[i] = &(src->data[0][i*cols]);
     }
  }
  /*set the rows and columns*/
  src->rows = rows;
  src->cols = cols;
  
  /*returns a new image*/
  printf("make an image\n");
  return(src);
 }

 void image_free(Image *src){
    /* frees the image structure space in memory the conditionals are to check that I am not trying to free something that does not have alloted memory there */ 
   printf("free the image\n");
   if (src!=NULL){
     if (src-> data!=NULL ){
       if(src-> data[0]!= NULL){
	 free(src-> data[0]);
       }
      free(src->data);
     }
     free(src);
   }
 }

 void image_init(Image *src){
   /*sets the rows and cols fields to 0 and the data field to NULL*/
   printf("set up the image again \n");
  src->data = NULL;
  src->rows = 0;
  src->cols = 0;
 }

 int image_alloc(Image *src, int rows, int cols){
   /*if rows and cols are >0 free memory*/
   /*allocate space for the image data given rows and cols*/
   /*initialize the image data RGBA = 0, and z = 1*/
   int i;
   int j;
   FPixel blank = {{0.0, 0.0, 0.0}, 0.0, 1.0};
   printf("allocate space\n");
   if (src->rows >0 && src->cols>0){
     printf("clearing out old stuff\n");
     free(src->data[0]);
     free(src->data);
   }
   printf("make new space for data\n");
   if (src==NULL){
     src->data = malloc(sizeof(FPixel*)*rows);/*creates a column of pointers*/
     src->data[0] = malloc(sizeof(FPixel)*rows*cols);/*attaches those pointers to the image*/
   }else{
     return(-1);
   }
     /*loops through the first column of pixels and sets
     pointers to them for eaiser indexing*/
   for(i = 1; i<rows; i++){
	src->data[i] = &(src->data[0][i*cols]);
   }	
   for(i = 1; i<rows; i++){
     for(j = 1; j<cols; j++){
       src->data[i][j] = blank;
     }
   }
   src->rows = rows;
   src->cols = cols;
   return(0);
 }

 void image_dealloc(Image *src) {
   printf("deallocate space\n");
   /*deallocate image data*/
   if(src->data!=NULL){
     if(src->data[0] !=NULL){
       free(src->data[0]);
     }
     free(src->data);
   }
   /*reset(NOT THE SAME AS FREE) the image structure fields*/
   src->rows =0;
   src->cols =0;
   src->data =  NULL;
 }

 /*I/O FUNCTIONS*/

 Image *image_read(char *filename){
   /*reads a ppm image from the given filename*/
   int row, col, colors;
   int i, j;
   Image *newImage=NULL;
   Pixel *arrayImage;
   
   /*use readPPM function from ppmIO library*/
   arrayImage = readPPM(&row, &col, &colors, filename);
   newImage = image_create(row,col);
   /*Initalize alpha channel to 1*/
   /*Initalize the z channel to 1*/
   /*convert pixel values to 0-1 scale*/
   for (i = 0; i<(newImage->rows); i++){
     for (j = 0; j<(newImage->cols); j++){
       newImage->data[i][j].a = 1;
       newImage->data[i][j].z = 1;
       newImage->data[i][j].rgb[0] = (float)arrayImage[i*col+j].r/255;
       newImage->data[i][j].rgb[1] = (float)arrayImage[i*col+j].g/255;
       newImage->data[i][j].rgb[2] = (float)arrayImage[i*col+j].b/255;
     }
   }
   newImage->rows = row;
   newImage->cols = col;
   
   /*allocated memory when call readPPM need to free that memory*/
   free(arrayImage);
   /*return null pointer if operation fails*/
   return(newImage);
 }

 int image_write(Image *src, char *filename) {
   int i, j;
   int imagesize;
 
   imagesize = src->rows*src->cols;
   Pixel *holdImage = malloc(sizeof(Pixel)*imagesize);
   /*convert back to 255 scale*/
   for (i = 0; i<src->rows; i++){
     for(j = 0; j<src->cols;j++){
       holdImage[i*src->cols+j].r = src->data[i][j].rgb[0]*255;
       holdImage[i*src->cols+j].g = src->data[i][j].rgb[1]*255;
       holdImage[i*src->cols+j].b = src->data[i][j].rgb[2]*255;
     }
   }
   /*write a PPM image to the given filename using writePPM from ppmIO*/
   writePPM(holdImage, src->rows, src->cols, 255  , filename);
   
   /*free all malloced statemnts*/
   free(holdImage);
   /*return 0 on success*/
   return(0);
 }

 /*ACCESS*/

 FPixel image_getf(Image *src, int r, int c){
   /*return the pixel at (r,c)*/
   return(src->data[r][c]);
 }

 float image_getc(Image *src, int r, int c, int b){
   /*returns the pixel value of band b at pixel(r,c)*/
   return(src->data[r][c].rgb[b]);
 }

 float image_getz(Image *src, int r, int c){
   /*returns the alpha value at (r,c)*/
   return(src->data[r][c].a);
 }

Color image_getColor(Image *src, int r, int c){
  /*get the color object at a specific pixel*/
  Color color;
  color.c[0] = src->data[r][c].rgb[0];
  color.c[1] = src->data[r][c].rgb[1];
  color.c[2] = src->data[r][c].rgb[2];
  return(color);
}

 void image_setf(Image *src, int r, int c, FPixel val){
   /*set the value of a pixel (r,c) to the FPixel val*/
   src->data[r][c] = val;
 }

 void image_setc(Image *src, int r, int c, int b, float val){
   /* set the value of (r,c) band b to val*/
   src->data[r][c].rgb[b] = val;
 }

 void image_seta(Image *src, int r, int c, float val){
   /*set the alpha value of pixel (r,c) to val*/
   src-> data[r][c].a = val;
 }

 void image_setz(Image *src, int r, int c, float val){
   /*set the depth value of the pixel (r,c) to val*/
   src->data[r][c].z = val;
 }

 void image_setColor(Image *src, int r, int c, Color val){
   if(r>src->rows - 1 || r<0 || c>src->cols - 1 || c<0)
     return;
   src->data[r][c].rgb[0] = val.c[0];
   src->data[r][c].rgb[1] = val.c[1];
   src->data[r][c].rgb[2] = val.c[2];
 }

 /* UTILITY*/

 void image_reset(Image *src){
   /*resets every pixel to a default value (RGB = 0; a = 1, z = 1)*/
   int i; 
   int j;
   if (src == NULL){
     printf("source is equal to null and it shouldn't be\n");
   }

   FPixel blank = {{0.0, 0.0, 0.0}, 1.0, 1.0};
   for (i = 0; i< src->rows; i++){
     for( j = 0; j< src->cols; j++){
       src->data[i][j] = blank;
     }
   }
 }

 void image_fill(Image *src, FPixel val){
   /*sets every FPixel to the given value*/
   int i; 
   int j;
   for (i = 0; i< src->rows; i++){
     for( j = 0; j< src->cols; j++){
       src->data[i][j] = val;
     }
   }
 }

 void image_fillrgb(Image *src, float r, float g, float b){
   /*sets the (r,g,b) values of each pixel to the given color*/
   int i; 
   int j;
   for (i = 0; i< src->rows; i++){
     for( j = 0; j< src->cols; j++){
       src->data[i][j].rgb[0] = r;
       src->data[i][j].rgb[1] = g;
       src->data[i][j].rgb[2] = b;
     }
   }
 }

 void image_filla(Image *src, float a){
   /* set the alpha value of each pixel to a*/
   int i; 
   int j;
   for (i = 0; i< src->rows; i++){
     for( j = 0; j< src->cols; j++){
       src->data[i][j].a = a;
     }
   }
 }

 void image_fillz(Image *src, float z){
   /*sets the z value for each pixel with z*/
   int i; 
   int j;
   for (i = 0; i< src->rows; i++){
     for( j = 0; j< src->cols; j++){
       src->data[i][j].z = z;
     }
   }
 }

void mandelbrot(Image *dst, float x0, float y0, float dx, int r, int g, int b){
  /*builds a mandelbrot set!!*/
  float x1, y1, dy;
  float srows, scols, cx,cy;
  int maxVal=500;
  int numIters; 
  float zx, zy, zxHold;
  int i, j;

  dy = (dst->rows*dx)/dst->cols;
  x1 = x0+dx;
  y1 = y0+dy;

  srows = (y1-y0)/(float)(dst->rows);
  scols = (x1-x0)/(float)(dst->cols);

  /*Information print statements*/
  printf("\ndx: %f dy:  %f\n",dx, dy);
  printf("x0: %f y0: %f\n", x0, y0);
  printf("x1: %f y1: %f \n", x1, y1);
  printf("scaleR: %f scaleC: %f\n", srows, scols);
  printf("rows: %d cols: %d\n", dst->rows,dst-> cols);

  /*for each pixel in the image(i,j)*/
  numIters = 0;
  printf("Calculating the Mandelbrot Set\n\n");
  for( i = 0; i< dst->rows; i++){
    for( j= 0; j<dst->cols; j++){
      cy = -srows*i +y1;
      cx = scols*j +x0;
      zx = 0; zy = 0;

      for(numIters=0; numIters<=maxVal; numIters++){
	zxHold = (zx*zx)-(zy*zy)-cx;
	zy =(2*zx*zy)-cy;
	zx = zxHold;
	if (((zx*zx)+(zy*zy))>=4){
	  break;
	}
      }
      if (numIters >= maxVal){
	image_setc(dst,i,j,0,0.0);
	image_setc(dst,i,j,1,0.0);
	image_setc(dst,i,j,2,0.0);
      }else{
      	float snew = sqrt(zx*zx +zy*zy); 
       	int smoothed = numIters +1 - log2(log2(snew)/log2(2)); 
	image_setc(dst,i,j,0,(float)(smoothed%maxVal)/r);
       	image_setc(dst,i,j,1,(float)(smoothed%maxVal)/g);
	image_setc(dst,i,j,2,(float)(smoothed%maxVal)/b);
      }
    }
  }
}

void julia(Image *dst, float x0, float y0, float dx, float c1, float c2, int r, int g, int b){
  float dy,srows,scols, y1, x1;
  float zx,zy, zxHold;
  int i,j, maxVal=500, numIters;
  dy = (dst->rows*dx)/dst->cols;
  x1 = x0+dx;
  y1 = y0+dy;

  srows = (y1-y0)/dst->rows;
  scols = (x1-x0)/dst->cols;

  /*Information print statements!*/
  printf("\ndx: %f dy:  %f\n",dx, dy);
  printf("x0: %f y0: %f\n", x0, y0);
  printf("x1: %f y1: %f \n", x1, y1);
  printf("scaleR: %f scaleC: %f\n", srows, scols);
  printf("rows: %d cols: %d\n", dst->rows,dst-> cols);

  numIters = 0; 
  printf("Calculating the Julia Set\n\n");
  for (i = 0; i<dst->rows; i++){
    for(j = 0; j<dst->cols; j++){
      zy = -srows*i +y1;
      zx = scols*j +x0;
      for(numIters=0; numIters<=maxVal; numIters++){
	zxHold = (zx*zx)-(zy*zy)-c1;
	zy =(2*zx*zy)-c2;
	zx = zxHold;
	if (((zx*zx)+(zy*zy))>=4){
	  break;
	}
      }
      /*color PIXEL*/ 
      if (numIters >= maxVal){
	image_setc(dst,i,j,0,0.0);
	image_setc(dst,i,j,1,0.0);
	image_setc(dst,i,j,2,0.0);
      }else{
      	float snew = sqrt(zx*zx +zy*zy); 
       	int smoothed = numIters +1 - log2(log2(snew)/log2(2)); 
	image_setc(dst,i,j,0,(float)(smoothed%maxVal)/r);
       	image_setc(dst,i,j,1,(float)(smoothed%maxVal)/g);
	image_setc(dst,i,j,2,(float)(smoothed%maxVal)/b);
      }
    }
  }
}


void noise(Image *src, float theta, int type){
  /*This function makes NOISE :)*/
  int i,j;
  float x, y;
  printf("making noise\n");
  for(i = 1; i< src->rows; i++){
    for(j = 1; j<src->cols; j++){
      /*sine and cosine make a green diagonal lines*/
      if (type == 1){
       x = sinf(theta+i+j);
       y = cosf(theta+i+j);
      }else if(type ==2){

      /*makes a plaid pattern*/
	x =(float) (i*i+j/10);
	y =(float) (j*j+i/10);
      }else{
      /*pretty boxes*/
	x = (i+1/j)%255;
	y = (j+5/i)%255;
      }
      image_setc(src,i,j,0,y);
      image_setc(src,i,j,1,1.0);
      image_setc(src, i,j,2,x);
    }
  }
}

void speckle(Image *src, int density){
  /* this function speckels the image with white pixels
     with the intent to use for an alpha mask!*/
  int i, j;
  for(i = density; i< src->rows-density; i=i+density){
    for(j = density; j<src->cols-density; j=j+density){
      image_setc(src,i,j,0,0.0);
      image_setc(src,i,j,1,0.0);
      image_setc(src, i,j,2,0.0);
    }
  }

}
