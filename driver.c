#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cs220_paint.h"

int main(int argc, char *argv[]) {
  // check that correct number of command line arguments were passed
  // report error if not
  if (argc != 3) {
    printf("Error: incorrect number of command line arguments passed.\n");
    return 1;
  }
  
  const char *in_filename = argv[1];
  const char *out_filename = argv[2];
  
  FILE *input = fopen(in_filename, "r");
  if(input == NULL){
    printf("Error: cannot open file.\n");
    return 1;
  }
  
  // Read the width and height of the frame
  int width = 0;
  int height = 0;
  fscanf(input, "%d %d", &width, &height);
  
  int num_vals = width * height * 3;
  unsigned char *pixel =  (unsigned char*) calloc(num_vals, sizeof(int));

  int error = 0;
  char command;

  int rc = fscanf(input, " %c", &command); // read first command

  // Continue the flow until all command are processed in the command file is processed or an error has occurred
  while (!error && rc != EOF) {
    int r,g,b; // RGB of the color
    switch (command) {
    case 'c':   // set current color
      {
	fscanf(input, " %d %d %d", &r, &g, &b);
      }
      break;

    case 'r':   // rectangle
      {
        int x,y,w,h; // coordinate of the upper-left corner and the width and height of the rectangle
       	if(fscanf(input, " %d %d %d %d", &x, &y, &w, &h)!=4){
	  printf("Error: invalid number of input for drawing rectangle.\n");
	  return 1;
	}
	if (x < 0 || y<0||w<0||h<0){
	  printf("Error: invalid input for drawing rectangle.\n");
	  return 1;
	}
	render_rectangle(pixel,width,height,x,y,w,h,r,g,b);
      }
      break;

    case 'e':   // ellipse
      {
        float x1,y1,x2,y2,length; //coordinates of the two focal points and the size of the ellipse
	if(fscanf(input, " %f %f %f %f %f", &x1, &y1, &x2, &y2, &length)!=5){
	  printf("Error: invalid number of input for drawing ellipse.\n");
	  return 1;
	}
	if (x1 < 0 || y1<0||x2<0||y2<0||length<=0){
	  printf("Error: invalid parameters for drawing rectangle.\n");
	  return 1;
	}
	
	render_ellipse(pixel,width,height,x1,y1,x2,y2,length,r,g,b);
      }
      break;

    case 'f':   // flood fill
      {
        
	int x,y;
	if(fscanf(input, " %d %d", &x, &y)!=2){
	  printf("Error: invalid number of input for flood fill.\n");
	  return 1;
	}
	if (x < 0 || y < 0){
	  printf("Error: invalid parameters for flood fill.\n");
	  return 1;
	}
	
	flood_fill(pixel,width,height,x,y,r,g,b);

      }
      break;

    default:    // unknown command
      printf("Error: Unknown command '%c'\n", command);
      error = 1;
      break;
    }

    if (!error) {
      rc = fscanf(input, " %c", &command); // read next command
    }
  }

 
  fclose(input);
  
  if(error) {
    printf("Error: command processing error.\n");
    return 1;
  }
  
  if(write_image(out_filename, width, height, pixel) != 1){
    printf("Error: write_image failed.\n");
    return 1;
  }
 
  printf("Success\n");
  free(pixel);
  return 0;
}
