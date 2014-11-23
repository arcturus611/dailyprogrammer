	//r/dailyprogrammer
	//intermediate sierpinski carpet 
	
	#include<stdlib.h>
	#include<stdio.h>
	
	int power_fn(int a, int x){
		int b = 1;
		for (int i = 0; i<x; i++)
			b*=a;
		return b;
	}
	
	void one_level_sierpinski(int pixel_step, int num_bases, char*** sier){
	
		for(int i = 0; i<num_bases; i++){
			for(int j = 0; j<num_bases; j++){
				int base_x = 3*i*pixel_step + 1; 
				int base_y = 3*j*pixel_step + 1;
				int mid_x = base_x + pixel_step; 
				int mid_y = base_y + pixel_step;
				
				for(int ii = 0; ii < pixel_step; ii++){
					for(int jj = 0; jj<pixel_step ; jj++){
						int blank_x = mid_x + ii; 		
						int blank_y = mid_y + jj;		
						//printf("Got here\n");
						(*sier)[blank_x-1][blank_y-1] = '#';
					}
				}
				 
			}
		}
		
		return;	
	}
	
	void print_sierpinski(char*** sier, int d){
		
		for(int i = 0; i<d; i++){
			for(int j = 0; j<d; j++){
				printf("%c", (*sier)[i][j]);
			}
			printf("\n");
		}
	
		return;
	}
	
	void sierpinski_carpet(int r){ // r = #recursions
		int dim = power_fn(3, r);	
		//printf("dim is %d\n", dim);
		
		char** sierpinski = malloc(dim*sizeof(char* )); 
		for(int i = 0; i<dim; i++)
			sierpinski[i] = malloc(dim*sizeof(char));
		for(int i = 0; i<dim; i++){
			for(int j = 0; j<dim; j++){
				sierpinski[i][j] = ' ';
			}
		}
	
		//printf("got here...\n");
		for(int i = 0; i< r; i++){
			int pixel_step = power_fn(3, i); //number of steps from base to blank start; size of blank section
			int num_bases = power_fn(3, r-i-1);// (see notes); number of values of k
			one_level_sierpinski(pixel_step, num_bases, &sierpinski);
		}
		
		print_sierpinski(&sierpinski, dim);
		
		for(int i = 0; i<dim; i++)
			free(sierpinski[i]);
		free(sierpinski);
	}
	
	int main(int argc, char* argv[]){
		int depth = atoi(argv[1]);
		sierpinski_carpet(depth);
		return 0;
	}
