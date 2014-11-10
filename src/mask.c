/*
This takes in three inputs, an image that will have a green screen removed and a new image
name, along with a red to green ratio. 

Input: 
	image1: the image with an object in a green screen
	outputfile name: the name of the output file.  
        rtogRatio(compareValue): this value is used as the comparison value for the ration between the 
		red and green colors in each pixel. Because we are using a green screen the pixels we 
		want to remove will have a lot more green than red and will thus have a larger value 
		in the ratio (typically use between 0.9 and 1).
		** I added this feature because even if an image was not taken on a green screen 
		if the image has a large section of concentrated green than this method can be 
		applied and have that green taken out. 
	
Output: 
	A mask to be used in mergeImages. It is a strictly black and white image, 
	   it also has inbetween values for boundary pixels! 
	
Torrie Edwards
Graphics CS351
September 11, 2014

-----------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "ppmIO.h"

#define USECPP 0

int main(int argc, char *argv[]) {
  Pixel *image;
  int rows, cols, colors;
  long imagesize;
  int i;
  int j;
  int index;
  int radiusA,radiusB,radiusC,radiusD;
  
  float rtogRatio;

  if(argc < 4) {
    printf("Usage: Mask Files <input file> <output file> <red:green val\n");
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
  /* build mask here*/
  printf("Begin Mask\n");
  for(i=0;i<imagesize;i++) {
    rtogRatio = (float)image[i].r/(float)image[i].g;
    if(rtogRatio<atof(argv[3])){
       image[i].g = 255;
       image[i].b = 255;
       image[i].r = 255;
    }else if(rtogRatio<(atof(argv[3])+.1) && rtogRatio>atof(argv[3])){
      image[i].g = 128;
	image[i].b = 128;
	image[i].r = 128;
     }else{
	image[i].g = 0;
	image[i].b = 0;
	image[i].r = 0;
     }
  }

  printf("Check for any holes and fill them\n");
  /*fill any holes in the body of the image*/
  for(i=5;i<rows-5;i++) {
    for(j= 5;j<cols-5;j++){
      index = i*cols+j;
      radiusA = (i+5)*cols+j;
      radiusB = (i-5)*cols+j;
      radiusC = i*cols +j+5;
      radiusD = i*cols+j-5;
    /*Fill in any holes in the mask (pixels that might have gotten
	 through
	1) check neighbors
	2) if the neighbors are all one color change the current pixel*/
      if(( image[radiusA].g== 0 && image[radiusB].g==0 && image[index].g!=0 && image[index].g!= 128) ||  (image[radiusC].g==0 && image[radiusD].g==0 && image[index].g!= 0 && image[index].g !=128)){
      if (radiusA%rows < rows || radiusB%rows < rows || radiusC%cols <cols || radiusD%cols <cols){
	  image[index].g = 0;
	  image[index].r = 0;
	  image[index].b = 0;
      }
	}
    }
  }
  
  /* write out the resulting image */
  printf( "Write out new Mask\n");
  writePPM(image, rows, cols, colors /* s/b 255 */, argv[2]);

  /* free the image memory */
#if USECPP
  delete[] image;
#else
  free(image);
#endif

  return(0);
}

