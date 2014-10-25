//r/dailyprogrammer
//challenge 178 (easy)
//transforming matrices
//skeeto's solution 

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct command {
 double args[3]; 
 char name[15];
};

// struct is like any other built-in C datatype and hence can be returned directly
struct command command_read(FILE* fp){

 struct command current_command = { {0} }; 
 //after initializing a struct, we modify its fields using pointers
 char* name = current_command.name; 
 while((*name = fgetc(fp))!= '(')
  name++; 
 *name = '\0'; 

 ungetc('(', fp); // if you don't do this, in the next for loop's condition, fgetc will eat up the first digit after the '('. 
 for(double* args = current_command.args; fgetc(fp)!=')' ; args++){
  fscanf(fp, "%lf", args);// fp is incremented after the condition check in the for loop and also after the scanf. 
 }
 
 while(fgetc(fp)!='\n'); 
 return current_command;

}

struct point{
 double x, y; 
};

struct point point_read(FILE* fp){
 struct point pt = { 0 }; 
 fscanf(fp, "(%lf, %lf)\n", &(pt.x), &(pt.y));
 return pt; 
}


void translate_op(struct point* pt, double dx, double dy){
 pt->x += dx; 
 pt->y += dy; 
}

void finish_op(struct point* pt){
 printf("The new point is %lf, %lf\n", pt->x, pt->y);
 exit(0);
}

const struct table{
 const char* name; 
 void (*op)(); 
}OPERATIONS[] = {
 {"translate", translate_op}, 
 {"finish", finish_op}
}; // basically we have a const array of structs here, and are initializing each of the elements of the array. The second field is a fntion pointer, so you match the parsed command with one of the name strings (first field) and hook it up with the corresponding fnction. 

//void rotate_op

void point_exec(struct point* pt, struct command* cmd){
 for (int i = 0; i<sizeof(OPERATIONS)/sizeof(OPERATIONS[0]); i++){
  if (strcmp(OPERATIONS[i].name, cmd->name)==0){
   OPERATIONS[i].op(pt, cmd->args[0], cmd->args[1], cmd->args[2]);
   return; 
  }
 }

}

int main(int argc, char** argv){
 struct point pt = point_read(stdin);  
 while(1){
  struct command cmd = command_read(stdin);
  point_exec(&pt, &cmd);
 //printf("Now the point is at: %lf, %lf\n", pt.x, pt.y);
 }
 return 0; 
}
