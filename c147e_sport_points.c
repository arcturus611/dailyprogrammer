	//r/dailyprogrammer sport points(easy)
	//challenge 147
	
	//Possible scores are 6 + x (x = 0 to inf), or 3. So only 1, 2, 4, 5 are invalid
	
	#include<stdio.h>
	#include<stdlib.h>
	
	int main(int argc, char* argv[]){
		int s = atoi(argv[1]); 
		if((s==1)||(s==2)||(s==4)||(s==5)) printf("Invalid Score\n"); 
		else printf("Valid Score\n");
		return 0;
	}
