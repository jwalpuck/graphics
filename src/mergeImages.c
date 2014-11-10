/*
This takes in three inputs, two images to be merged with the help of an alpha mask. 
The alpha mask should be based on one of the images importing. Note: all 3 image
files need to be the same size! 

Input: 
	image1: a ppm image file
	image2, mask: a ppm image file with its corresponding alpha mask
	output filename: the new name of the output file. 
	x-position(dy rows), y-position(dx columns): the positions that image2 will be put into image1 
		+x position moves the image right , -x position moves the image to the left 
		+y position moves the image down, -y position moves the image up
		*note:It is important to remember that pictures are oriented different than standard x,y
		(the code handles this for the user just supply a dx, dy values)
	specialEffect: Apply one of 3 effects by supplying 1: upside down, 2: flip, 0: normal
	maskEffect: Apply one of 3 mask types by supplying 1: random, 2: fog, 0: normal
Output: 
	A new image from the two provided images
	
Torrie Edwards
Graphics CS351
September 11, 2014

-----------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "ppmIO.h"

#define USECPP 0

int main(int argc, char *argv[]) {
  Pixel *image1;
  Pixel *image2;
  Pixel *mask;
  int rows1, cols1, colors1;
  int rows2, cols2, colors2;
  int rowsMask, colsMask, colorsMask;
  int  dx,dy;
  int  idx1, idx2; 
  int i;
  int j;
  int specialEffect;
  int maskEffect;
  float alpha;
  float num;
  long imagesize1;
  long imagesize2;

  if(argc < 7) {
    printf("Usage: Merge IMages <input file 1> <input file 2> <mask> <output file> <dx>, <dy>, <Special Effect>, <Mask Effect>\n");
    exit(-1);
  }

  /* read in the image [readPPM allots memory for the images which is why I do not use malloc to 
   allot space for the image]*/
  image1 = readPPM(&rows1, &cols1, &colors1, argv[1]);
  image2 = readPPM(&rows2, &cols2, &colors2, argv[2]);
  mask = readPPM(&rowsMask, &colsMask, &colorsMask, argv[3]);
  dx = atoi(argv[5]);
  dy = atoi(argv[6]);
  printf("%s:  %d\n","dx",dx);
  printf("%s:  %d\n","dy", dy);

  specialEffect = atoi(argv[7]);
  maskEffect = atoi(argv[8]);

  /* tell the user if the input is a problem and what is missing*/
  if(!image1 ) {
    fprintf(stderr, "Unable to read %s\n", argv[1]);
    exit(-1);
  }else if (!image2) {
      fprintf(stderr, "Unable to read %s\n", argv[2]);
      exit(-1);
  }else if (!mask) {
      fprintf(stderr, "Unable to read %s\n", argv[3]);
      exit(-1); 
  }

  /*set up the random counter based on the computers internal clock for
    one of the mask options*/
  srand((float)time(NULL));

  
  /* calculate the image size */
  imagesize1 = (long)rows1 * (long)cols1;
  imagesize2 = (long) rows2 * (long)cols2;
  
  /*Check that the images are the same size */
  /*Code written to work for images of like sizes.*/
  if (imagesize1!= imagesize2){
     printf("Images are not the same size\n");
     exit(-1);
  }
  printf("%s %d\n", "rows of background:", rows1);
  printf("%s %d\n", "columns of background:", cols1);
  printf("%s %lu\n","background size:", imagesize1);
  printf("%s %d\n", "rows of foreground:", rows2);
  printf("%s %d\n", "columns of foreground:", cols2);
  printf("%s %lu\n","size of foreground:", imagesize2);

  /* Tell you what effects you are using*/
  if (specialEffect ==1 ){
    printf("%s %d\n","SpecialEffect Upside Down",specialEffect);
  }else if(specialEffect ==2){
	printf("%s %d\n","SpecialEffect Flip",specialEffect);
  } else{
	printf("%s %d\n","SpecialEffect Normal",specialEffect);
  }

  if (maskEffect == 1){
	printf("%s %d\n","Mask Effect Random",maskEffect);
  }else if(maskEffect == 2){
	printf("%s %d\n","Mask Effect Fog",maskEffect);
  }else{
	printf("%s %d\n","Mask Effect Normal",maskEffect);
  }
  printf("Apply special effect and mask effect selected!\n");
  /* Merge Pixels Here! */
  for(i=0;i<rows2;i++) {
    for(j=0;j<cols2; j++){
      /*Select special effect the user specified*/
      if (specialEffect == 1){
	/*UpsideDown x*/
	idx1 = (i+dy-rows2)*-cols2+(j+dx);
	idx2 = i*cols2+j;
      }else if (specialEffect == 2){
	/*FLIP*/
	idx1 = (i+dy)*cols2+(j-cols2+dx)*-1;
	idx2 = i*cols2+j;
      }else{
	/*Normal*/
	idx1 = (i+dy)*cols2+(j+dx);
	idx2 = i*cols2+j;
      }

      /* this catches exceptions if my dx or dy moves the image out 
	 of range it will just continue on!!! (we do this by checking
         to make sure the image does not go off any of the edges)*/
	if (i+dy<0 || i+dy>rows1 ||j+dx<0 ||  j+dx>cols1){
	  continue;
	} 

      /* select the type of mask the user has specified*/
      if (maskEffect == 1){
	/*Random*/
	num = (float)rand()/(float)RAND_MAX;
	alpha = num;
      }else if (maskEffect == 2){
	/*Fog*/
	alpha = 0.6;
      }else{
	/*Normal*/
	alpha = mask[idx2].g/255.0; 
      }
      /*Apply the alpha blending*/      
      image1[idx1].g = alpha*image1[idx1].g + (1.0-alpha)*image2[idx2].g;
      image1[idx1].b = alpha*image1[idx1].b + (1.0-alpha)*image2[idx2].b;
      image1[idx1].r = alpha*image1[idx1].r + (1.0-alpha)*image2[idx2].r;
    }
  }
 
   fprintf(stderr, "Your Resulting Image name is: %s\n", argv[4]);

  /* write out the resulting image */
  writePPM(image1, rows1, cols1, colors1 /* s/b 255 */, argv[4]);

/* free the image memory */
#if USECPP
  delete[] image1;
  delete[] image2;
  delete[] mask;

#else
  free(image1);
  free(image2);
  free(mask);

#endif
  return(0);
}  
