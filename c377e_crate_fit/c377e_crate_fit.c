	#include<stdio.h>
	#include<string.h>
	#include<math.h>

	int ptoi(char* p){
		int x, len;
		x=0;
		len = strlen(p);
		for (int i = 0; i<len; i++){
			x+=(p[i]-'0')*pow(10, len-1-i);
		}
		return x;
	}
	
	int main(int argc, char* argv[]){
		int X, Y, x, y, num_crates;
		
		if (argc < 5){
			printf("Error! Please enter four arguments!\n"); 
			return 0;	
		}
		
		X = ptoi(argv[1]);
		Y = ptoi(argv[2]);
		x = ptoi(argv[3]);
		y = ptoi(argv[4]);
		
		printf("The inputs are %d, %d, %d, and %d\n", X, Y, x, y);
		num_crates = (X/x)*(Y/y);
		printf("The number of crates we can pack is %d\n", num_crates);
		
		return 0;
	}
