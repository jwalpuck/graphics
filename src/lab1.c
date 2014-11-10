/*
This takes in two inputs an image and a new filename for the image. This code is set up 
to apply different filters. In this file the filter is rainbow so all six colors of the 
rainbow appear overlaying the image. 

Input: 
	image1: the image with an object in a green screen
	outputfile name: the name of the output file.  
	
Output: 
	A new image with an applied filter
	
/*Torrie Edwards*/
/*Graphics CS351*/
/*September 11, 2014*/

-----------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "ppmIO.h"

#define USECPP 0

int main(int argc, char *argv[]) {
  Pixel *image;
  int rows, cols, colors;
  long imagesize;
  long i;
  // int intensity;

  if(argc < 3) {
    printf("Usage: ppmtest <input file> <output file>\n");
    exit(-1);
  }

  /* read in the image */
  image = readPPM(&rows, &cols, &colors, argv[1]);
  if(!image) {
    fprintf(stderr, "Unable to read %s\n", argv[1]);
    exit(-1);
  }

  /* calculate the image size */
  imagesize = (long)rows * (long)cols;

    imagesize = imagesize/6;

  /* mess with the image here  */
   for(i=0;i<(imagesize);i++) { 
   image[i].r = 255; 
      }
      for(i=imagesize;i<(imagesize*2);i++) {
     image[i].r = 255; 
     image[i].g = 255;
      }
     for(i=(imagesize*2);i<(imagesize*3);i++) {
        image[i].r = 255; 
     image[i].g = 150;
   if ((int)image[i].b >175){
    image[i].b = 100;
  }
   }  
  for(i=(imagesize*3);i<(imagesize*4);i++) {
   image[i].g = 255; 
   }  
  for(i=(imagesize*4);i<(imagesize*5);i++) {
    image[i].b = 255; 
   } 
  for(i=(imagesize*5);i<(imagesize*6);i++) {
    image[i].r = 255;
    image[i].b = 255;
   }

  /* write out the resulting image */
  writePPM(image, rows, cols, colors /* s/b 255 */, argv[2]);

  /* free the image memory */
#if USECPP
  delete[] image;
#else
  free(image);
#endif

  return(0);
}
