//r/dailyprogrammer
//challenge 12 (intermediate)
//factorisation of a number
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void factorise(int n){
 printf("Factorising %d... \n", n); 
 int s = ceil(sqrt((double)n));
 int count = 0; 

 while((n%2)==0){
  count++; 
  if(count==1){
   printf("%d = ", n);
   printf("2");
  } 
  else 
   printf("*2"); 
  n = n/2; 
 }

 for (int i = 3; i<=s ;i+=2){
  while((n%i)==0){
   count++;
   if (count==1){
    printf("%d = ", n); 
    printf("%d", i); 
   }
   else 
    printf("*%d", i); 
   n = n/i;
  }
 }

 if (count>0 && n!=1)
  printf("*%d", n);  
 
 if (count==0)
   printf("Number is prime. Factors are 1 and %d\n", n); 
 printf("\n"); 
}

int main(int argc, char** argv){
 int n; 
 n = atoi(argv[1]); 
 factorise(n);
 return 0;
}
