//r/dailyprogrammer
//challenge 90 (easy)
//image rasterizer
//Aug 24
// ./ImageRasterizer Sx Sy instructions

#include<stdio.h>
#include<stdlib.h> //calloc()
#include<ctype.h> //tolower()
#include<string.h> //strlen()

int main(int argc, char** argv){
 int x_size = atoi(argv[1]); int y_size = atoi(argv[2]); 
 //y_size: height, x_size: width
 int** bin_img = calloc(y_size, sizeof(int*)); 
 for (int i = 0; i<y_size; i++){
  bin_img[i] = calloc(x_size, sizeof(int)); 
 } 

 int xp = 0, yp = 0; 
 
 char* ins = argv[3]; 
 int len = strlen(ins); 

 for (int i= 0; i<len; i++){
  if(tolower(ins[i])=='p'){
   bin_img[xp][yp] = 1;
  }
  else if (tolower(ins[i]) == 'e')
   xp++; 
  else if (tolower(ins[i]) == 'w')
   xp--; 
  else if (tolower(ins[i]) == 'n')
   yp--; 
  else if (tolower(ins[i]) == 's')
   yp++; 
 
 }

 printf("Image is: \n");
 for (int j = 0; j < y_size; j++){
  for (int i = 0; i < x_size; i++){
    printf("%c", (bin_img[i][j]==1?'X':' '));
  }
  printf("\n");
 }

 printf("\n"); 

 return 0;
}
