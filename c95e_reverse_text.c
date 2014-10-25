//r/dailyprogrammer
//challenge 95 (easy)
//reversing text in a file

// file in: reverse_text.txt
//file out: reverse_text_out.txt

//works!

#include<stdio.h>
#include<ctype.h>

#define MAX_CHARS 10
#define MAX_CHARS_IN_LINE 100
#define MAX_WORDS 50
#define MAX_LINES 100

void reverse_text(FILE* in, FILE* out){
 char line[MAX_CHARS_IN_LINE]; //  space for fgets
 char words[MAX_LINES][MAX_WORDS][MAX_CHARS];
 
 int word_count, char_count, line_count=0; int i, j; 
 int word_count_array[MAX_LINES]; 

 while (fgets(line, MAX_CHARS_IN_LINE, in)!=NULL){// do this for each line
   word_count = 0;
   i = 0; 
   while(line[i]!='\n'){ //until end of line is reached
    while(isspace(line[i]) && line[i]!='\n'){ // get rid of all initial/in-between spaces
     i++;
    }
    // word starts
    char_count= 0;
    while(isalpha(line[i]) || ispunct(line[i])){
     words[line_count][word_count][char_count++] = line[i++];
    }
    if (char_count>0){
     words[line_count][word_count][char_count] = '\0';
     printf("Word %d of line %d is %s\n", word_count, line_count, words[line_count][word_count]);  
     word_count++;
    }
  }
  word_count_array[line_count] = word_count-1;
  line_count++; 
 }

 for (i = line_count; i>=0; i--){
  for (j = word_count_array[i]; j>=0; j--){
   printf("%s ", words[i][j]); 
   fprintf(out, "%s ", words[i][j]); 
  }
  printf("\n"); 
  fprintf(out, "\n"); 
 }

}

int main(int argc, char* argv[]){
 FILE* fin = fopen("reverse_text.txt", "r"); 
 FILE* fout = fopen("reverse_text_out.txt", "w"); 

 if(fin == NULL){
  perror("Error opening input file\n"); 
  return(-1); 
 }
 else if (fout == NULL){
  perror("Error opening output file\n"); 
  return(-1); 
 }
 else
  reverse_text(fin, fout);
 
 fclose(fin); 
 fclose(fout); 
 
}
