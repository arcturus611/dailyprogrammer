	/*
	You will accept two numbers, w and h, separated by a space. These are to be the width and height of the image in characters, with the top-left being (0, 0). You will then accept a grid of ASCII characters of size w*h. Finally you will accept two more numbers, x and y, and a character c. x and y are the co-ordinates on the image where the flood fill should be done, and c is the character that will be filled.
	*/
	//y: along vertical axis (height:h), x: along horizontal axis (width: w)
	
	#include<stdio.h>
	#include<stdlib.h>
	
	char** create_orig_image(int h, int w){
		char** A = (char **)malloc(h*sizeof(char*));
		for(int i = 0; i<h; i++)	
			A[i] = (char *)malloc(w*sizeof(char));
			
		for(int row = 0; row<h; row++){
			for(int col = 0; col<w; col++){
				scanf(" %c", &A[row][col]); 
			}
		}
		
		return A;
	}
	
	void flood_fill(char** A, int h, int w, int y, int x, char c, char ref){

		A[y][x] = c;
		if((y-1>=0) && (A[y-1][x] == ref)) flood_fill(A, h, w, y-1, x, c, ref);
		if((y+1<h) && (A[y+1][x] == ref)) flood_fill(A, h, w, y+1, x, c, ref);
		if((x-1>=0) && (A[y][x-1] == ref)) flood_fill(A, h, w, y, x-1, c, ref);
		if((x+1<w) && (A[y][x+1] == ref)) flood_fill(A, h, w, y, x+1, c, ref);
		
		return;
	}
	
	void print_flood_filled_image(char** A, int h, int w){
		for(int row=0; row<h; row++){
			printf("\n");
			for(int col = 0; col<w; col++){
				printf("%c ", A[row][col]);
			}
		}
		printf("\n\n");
		return;
	}
	
	void free_image(char** A, int h, int w){
		for(int row = 0; row<h; row++){
			free(A[row]);
		}
		free(A);
		return;
	}
	
	int main(int argc, char* argv[]){
		int w, h, x, y;
		char c; 
		scanf("%d %d", &w, &h);
		
		char** A = create_orig_image(h, w);
		
		scanf("%d %d %c", &x, &y, &c);
		char ref = A[y][x]; //reference character. All characters touching original point (y, x); 
		flood_fill(A, h, w, y, x, c, ref);
	
		print_flood_filled_image(A, h, w);
		free_image(A, h, w);
	
		return 0;
	}
