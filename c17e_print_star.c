// gcc -std=c99 -g -Wall c17e_print_star.c -o c17e_print_star

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void print_star(int h){
	int i, j, num_stars = 1; 
	for (i= 0; i<h; i++){
		if(i!=0) num_stars*=2; 
		for (j = 0; j<num_stars; j++)
			printf("*");
		printf("\n");
	}
	return;
}

void print_star_rev(int h){
	int i, j, num_stars = pow(2, h-1); 
	for (i= h; i>0; i--){
		for (j = 0; j<num_stars; j++)
			printf("*");
		printf("\n");
		num_stars/=2; 
	}
	return;
}

int main(int argc, char* argv[]){
	int num_stars = ( argc>1 ? atoi(argv[1]) : 5);
	print_star(num_stars);printf("\n");
	print_star_rev(num_stars);
	return 0;
}
