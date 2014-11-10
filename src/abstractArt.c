/*
This is going to be a line drawing trying to mimic an abstract form of art. 


September 25, 2014
Graphics CS 351
 -----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"


int main(int argc, char *argv[]){
  Image *src;
  Image *myImage;
  Image *myImage1;
  Image *myImage2;
  Color Black;
  Color White;
  Color color;
  Line l1;
  int i, j, k,m;

  color_set(&White, 1.0, 1.0, 1.0);
  color_set(&Black, 0.0, 0.0, 0.0);

  src = image_create(712, 1072);
  myImage = image_read(argv[1]);
  myImage1 = image_read(argv[2]);
  myImage2 = image_read(argv[3]);

  if(!src){
    fprintf(stderr, "unable to allocate memory\n");
    exit(0);
  }

  // Initialize the image to all white
  for(i=0;i<src->rows;i++) {
    for(j=0;j<src->cols;j++) {
      image_setColor(src, i, j, White );
    }
  }

 for (m = 13; m<= 253; m++){
  for (k = 693;k<= 999; k++){
      color = image_getColor(myImage, m,k);
      image_setColor(src,m,k, color);
      }
  }

 for (m = 13; m<= 133; m++){
  for (k = 13;k<= 63; k++){
      color = image_getColor(myImage1, m,k);
      image_setColor(src,m,k, color);
      }
  }
 for (m = 258; m<= 454; m++){
  for (k = 153;k<= 173; k++){
      color = image_getColor(myImage, m,k);
      image_setColor(src,m,k, color);
      }
  }


 for (m = 459; m<= 710; m++){
  for (k = 353;k<= 500; k++){
      color = image_getColor(myImage1, m,k);
      image_setColor(src,m,k, color);
      }
  }
 
 for (m = 258; m<= 456; m++){
  for (k = 837;k<= 999; k++){
      color = image_getColor(myImage2, m,k);
      image_setColor(src,m,k, color);
      }
  }


  for(i=0;i<6; i++){
    line_set2D(&l1, 10+i,0, 10+i, 711);
    line_draw(&l1,src, Black);
 
    line_set2D(&l1, 65+i,0, 65+i, 711);
    line_draw(&l1,src, Black);

    line_set2D(&l1, 95+i,0, 95+i,711);
    line_draw(&l1,src, Black);

    line_set2D(&l1, 150+i,0, 150+i,711);
    line_draw(&l1,src, Black);

    line_set2D(&l1, 175+i,0, 175+i,711);
    line_draw(&l1,src, Black);

    line_set2D(&l1, 350+i,0, 350+i,711);
    line_draw(&l1,src, Black);
 
    line_set2D(&l1, 475+i,0, 475+i,135);
    line_draw(&l1,src, Black);

    line_set2D(&l1, 500+i,0, 500+i,711);
    line_draw(&l1,src, Black);

    line_set2D(&l1, 690+i,0, 690+i,255);
    line_draw(&l1,src, Black);

    line_set2D(&l1, 834+i,255, 834+i,711);
    line_draw(&l1,src, Black);

    line_set2D(&l1, 1001+i,0, 1001+i,711);
    line_draw(&l1,src, Black);

    line_set2D(&l1, 0,10+i,1071 ,10+i);
    line_draw(&l1,src, Black);

    line_set2D(&l1, 0, 135+i, 500, 135+i);
    line_draw(&l1,src, Black);

    line_set2D(&l1, 0, 255+i, 1071, 255+i);
    line_draw(&l1,src, Black);

    line_set2D(&l1, 0, 456+i, 1071, 456+i);
    line_draw(&l1,src, Black);
  }

  image_write(src, "abstractArt2.ppm");
  image_free(src);
  image_free(myImage);
  image_free(myImage1);
  image_free(myImage2);
  return(0);
  


}
