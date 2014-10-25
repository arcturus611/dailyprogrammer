//r/dailyprogrammer
//challenge 12 (easy)
//string permutations

#include<stdio.h>
#include<string.h>

void swap(char* x, char* y){
 char temp; 
 temp = *x ;
 *x = *y; 
 *y = temp; 
}

void print_perms(char* str, int start, int len){
 if(start==len)
  printf("%s\n", str); 
 else{
  for(int j = start; j<=len; j++){
   swap((str+start), (str+j));
   print_perms(str, start+1, len);
   swap((str+start), (str+j));
  }
 }

}

int main(int argc, char* argv[]){
 char* str = argv[1];
 printf("Given string is: %s\n", str); 
 int len = strlen(str);  
 print_perms(str, 0, len-1);
 return 0;
}
