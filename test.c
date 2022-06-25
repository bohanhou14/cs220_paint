#include <stdio.h>
#include <stdlib.h>
#include "cs220_paint.h"

void print_matrix(unsigned char *pixel, int width, int height){
  int start = 0;
  int end = width*3;
  for (int i = start; i < width*height*3; i += width*3){
    for (int j = start; j < end; j+=3){
      printf("%d|%d|%d ", pixel[j], pixel[j+1], pixel[j+2]);
    }
    printf("\n");
    start += width*3;
    end += width*3;
  }
}
int main (){
  int width = 5;
  int height = 5;
  unsigned char *pixel = (unsigned char*) calloc (width * height * 3, sizeof(int));
  print_matrix(pixel, width, height);
  printf("\n");
  
  int x = 2;
  int y = 2;
  // int w = 3;
  // int h = 3;
  
  
  int r = 10;
  int g = 11;
  int b = 12;
  // render_rectangle(pixel, width, height, x,y,w,h,r,g,b);
  int val = is_ellipse(0,0,2,2,3,3,4);
  printf("%d\n", val);
  render_ellipse(pixel,width, height,2,2,3,3,4,r,g,b);
  print_matrix(pixel, width, height);
  return 0;
}
