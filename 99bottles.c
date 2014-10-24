//r/dailyprogrammer
//challenge 8 (easy)
//99 bottles of beer
//Aug23

#include<stdio.h>

void print_poem(){
 char* str[2] = {"bottle", "bottles"}; 
 char* print_str1; 
 char* print_str2; 
 for (int i = 99; i>=1; i--){
  if(i==2){
   print_str1= str[1]; 
   print_str2= str[0]; 
 }
  else if(i==1){
   print_str1= str[0]; 
   print_str2 = str[1]; 
 }
  else {
   print_str1 = str[1]; 
   print_str2 = str[1];
 }

  printf("%d %s of beer on the wall, %d %s of beer.\nTake one down and pass it around, %d %s of beer on the wall.\n\n", i, print_str1, i, print_str1, i-1, print_str2); 
 }
}

int main(int argc, char** argv){
 print_poem(); 
 return 0;
}
