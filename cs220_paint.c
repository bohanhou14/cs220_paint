#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cs220_paint.h"

unsigned char *read_image(const char *filename, int *width, int *height) {
  // open file for reading
  FILE *in = fopen(filename, "rb");
  if (in == NULL) {
    return NULL;
  }

  // read image dimensions
  if (fscanf(in, "%d %d", width, height) != 2) {
    fclose(in);
    return NULL;
  }

  // allocate buffer for RGBA triples
  int num_vals = *width * *height * 3;
  unsigned char *buf = (unsigned char *) malloc(num_vals * sizeof(unsigned char));
  if (buf == NULL) {
    fclose(in);
    return NULL;
  }

  // read RGBA triples
  int error = 0;
  for (int i = 0; i < num_vals; i++) {
    unsigned val;
    if (fscanf(in, "%x", &val) != 1) {
      error = 1;
    } else {
      buf[i] = (unsigned char) val;
    }
  }

  // now can close input
  fclose(in);

  // if error, delete buffer and return NULL
  if (error) {
    free(buf);
    return NULL;
  }

  // return buffer
  return buf;
}

// To write image to a text file
int write_image(const char *filename, int width, int height, const unsigned char *buf) {
  FILE *out = fopen(filename, "w");
  
  if(out == NULL){
    return 0;
  }
  
  fprintf(out, "%d %d\n", width, height);
  int num_vals = width * height * 3;
  
  
  for (int i = 0; i < num_vals; i++){
    /* if (val > 255 || val < 0) {
      printf("Error: found invalid RGB value %x at %dth number.\n", buf[i], i);
      return 0;
      }*/
    fprintf(out, "%x ", buf[i]);
  }
  
  //  free(buf);
  fclose(out);
  return 1;
}

// To calculate the geometric distance
double geom_dist(double x1, double y1, double x2, double y2) {
  return pow((pow((x1 - x2), 2) + pow((y1-y2), 2)),0.5);
}
int is_ellipse(int x, int y, double f1_x, double f1_y, double f2_x, double f2_y, double len){
  double sum = geom_dist(f1_x, f1_y, f2_x, f2_y) + geom_dist(x, y, f1_x, f1_y) + geom_dist(x,y,f2_x,f2_y);
  if (sum <= len) {
    return 1;
  }
  return 0;
}

int truncate(int num, int max) {
  if (num >= max) {
    return max;
  }
  return num;
}

void render_rectangle(unsigned char *pixel_data, int img_width, int img_height,
                      int rect_x, int rect_y, int rect_w, int rect_h,
                      int r, int g, int b) {
  int width = rect_x + rect_w;
  rect_w = truncate(width, img_width) - rect_x;
  int height = rect_y + rect_h;
  rect_h = truncate(height, img_height) - rect_y;
  
  int start = rect_y * img_width * 3 + rect_x * 3;
  int right_1 = 3; //shift one pixel rightward.
  int down_1 = 3 * img_width; //shift one pixel downward
  int right_end = start + right_1 * rect_w;//the top right corner
  int down_end = start + down_1 * rect_h;//the bottom left corner
  
  for (int j = start; j < down_end; j += down_1){
    for (int i = start; i < right_end; i += right_1){
      pixel_data[i] = r;
      pixel_data[i+1] = g;
      pixel_data[i+2] = b;
    }
    start += down_1; //start with a new row
    right_end += down_1;
  }
}


void render_ellipse(unsigned char *pixel_data, int img_width, int img_height,
                      double x1, double y1, double x2, double y2, double len,
                      int r, int g, int b) {
  int start = 0;
  int right_1 = 3;
  int down_1 = 3 * img_width;
  int right_end = img_width * right_1;
  int down_end = img_height * down_1;
  int x = 0; //the x coordinate being checked
  int y = 0; //the y coordinate being checked
  for (int i = start; i < down_end; i += down_1) {
    for (int j = start; j < right_end; j+= right_1) {
      if(is_ellipse(x, y, x1, y1, x2, y2, len)) {
	pixel_data[j] = r;
	pixel_data[j+1] = g;
	pixel_data[j+2] = b;
      }
      x++;
    }
    start += down_1; //search the next row
    right_end += down_1;
    y++;
    x=0;
  }
       
       
}


// Recursive implementation
void flood_fill(unsigned char *pixel_data, int img_width, int img_height,
                int x, int y, int r, int g, int b) {
  int right_1 = 3;
  int down_1 = img_width*3;
  int i_r = x * right_1 + y*down_1;
  int i_g = i_r + 1;
  int i_b = i_r + 2;
  rec_flood_fill(pixel_data, img_width, img_height,x,y,pixel_data[i_r],pixel_data[i_g],pixel_data[i_b],r,g,b,0);
}


// Helper method for flood_fill
void rec_flood_fill(unsigned char *pixel_data, int img_width, int img_height,
                    int x, int y,
                    int orig_r, int orig_g, int orig_b,
                    int r, int g, int b,
                    int dir) {
  int right_1 = 3;
  int down_1 = img_width*3;
  switch(dir) {
     case 0:{
  }break;
      case 1: {//right
      x += 1;
    }  break;
      case 2: {//up
      y+=1;
    }  break;
      case 3: {//left
      x-=1;
    }  break;
      case 4:{//down
      y-=1;
    }
      break;
  }
  int i_r = x * right_1 + y*down_1;
  int i_g = i_r + 1;
  int i_b = i_r + 2;
  
  if ((x<=img_width) && (y<=img_height) && (pixel_data[i_r] == orig_r) && (pixel_data[i_g] == orig_g) && (pixel_data[i_b] == orig_b)){
    pixel_data[i_r] = r;
    pixel_data[i_g] = g;
    pixel_data[i_b] = b;
    rec_flood_fill(pixel_data, img_width, img_height, x, y, orig_r, orig_g, orig_b, r, g , b, 1);
    rec_flood_fill(pixel_data, img_width, img_height, x, y, orig_r, orig_g, orig_b, r, g , b, 2);
    rec_flood_fill(pixel_data, img_width, img_height, x, y, orig_r, orig_g, orig_b, r, g , b, 3);
    rec_flood_fill(pixel_data, img_width, img_height, x, y, orig_r, orig_g, orig_b, r, g , b, 4);
  }
}

