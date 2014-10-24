// r/DailyProgrammer/#1
// ask users name, age, reddit username and print input back. log info in a file to be accessed later

#include<stdio.h>
#include<stdlib.h>

typedef struct uinfo{
 char* name; 
 int age; 
 char* redditname; 
}UInfo;

void get_user_info(UInfo* x){
 
 printf("\nWhat is your name?: "); 
 scanf("%s", x->name);
 
 printf("\nHow old are you (in years)?: "); 
 scanf("%d", &(x->age)); 

 printf("\nWhat is your reddit username?: "); 
 scanf("%s", x->redditname);  
 
}

void put_user_info(UInfo* x){

 FILE* fptr; 
 fptr = fopen("RedditUserInfo.txt", "w"); 

 printf("Your name is %s, you are %d years old, and your username is %s\n", x->name, x->age, x->redditname); 

 fprintf(fptr, "Your name is %s, you are %d years old, and your username is %s\n", x->name, x->age, x->redditname); 
 fclose(fptr);
 
}

int main(int argc, char** argv){
 UInfo* X = (UInfo *)malloc(sizeof(UInfo)); 
 X->name = (char *)malloc(100*sizeof(char)); 
 X->redditname = (char *)malloc(100*sizeof(char)); 

 get_user_info(X); 
 put_user_info(X);

 return 0;
}

//Useful links:
//http://stackoverflow.com/questions/10221537/segmentation-fault-when-trying-to-use-scanf-on-a-struct
