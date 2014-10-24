//r/dailyprogrammer
//Easy, challenge 173
//Unit Calculator
// works!

#include<stdio.h>
#include<string.h>

#define NUM_UNITS 4
#define NUM_UNIT_TYPES 2

const char* units[NUM_UNIT_TYPES][NUM_UNITS] = {
{"metres", "inches", "miles", "attoparsecs"}, 
{"kilograms", "pounds", "ounces", "beryllium-hogsheads"}
};  

const float unit_conv[NUM_UNIT_TYPES][NUM_UNITS][NUM_UNITS]= {
{
 {1, 39.37, .00062, 32.41}, 
 {.0254, 1, .000016, .82315}, 
 {1609.34, 63360, 1, 52155.29}, 
 {.0308, 1.2148, .000019, 1}
}, //metres, inches, miles, attoparsecs
{
 {1, 2.2, 35.27, .0022}, 
 {.453, 1, 16, .0011}, 
 {.028, .0625, 1, .00006}, 
 {440.7, 971.6, 15545.2, 1}
}
}; //kilograms, pounds, ounces, beryllium-hogsheads

struct conv_data{
 double x, y; 
 char req_units[2][20]; // 2 strings will be saved
};

struct inferred_data{
 int req_unit_type[2]; 
 int req_unit_idx[2]; 
};

struct conv_data read_request(FILE* in){
 struct conv_data mydata = {0}; // http://stackoverflow.com/questions/9669206/how-to-initialize-members-of-an-array-of-struct-in-c
 fscanf(in, "%lf", &(mydata.x)); 
 fscanf(in, "%s to %s", mydata.req_units[0], mydata.req_units[1]); 
 return mydata;
}

void get_unit_types(struct conv_data* p, struct inferred_data* d){
 for(int data_unit_idx = 0; data_unit_idx< 2; data_unit_idx++){
  for(int cmp_unit_type =0; d->req_unit_type[data_unit_idx]==-1 && cmp_unit_type < NUM_UNIT_TYPES; cmp_unit_type++){
   for(int j = 0; j<NUM_UNITS ;j++){
    if(strcmp(p->req_units[data_unit_idx], units[cmp_unit_type][j])==0){
     d->req_unit_type[data_unit_idx] = cmp_unit_type;
     d->req_unit_idx[data_unit_idx] = j;
     break; 
    }
   }
  } 
 }
 
 return; 
}

void print_conv_data(struct conv_data *p, struct inferred_data* d){
 if (d->req_unit_type[0]==-1 || d->req_unit_type[1] == -1)
  printf("Invalid req units\n"); 
 else if (d->req_unit_type[0]!=d->req_unit_type[1])
  printf("%.1lf %s cannot be converted to %s\n", p->x, p->req_units[0], p->req_units[1]);
 else{
  p->y = p->x*unit_conv[d->req_unit_type[0]][d->req_unit_idx[0]][d->req_unit_idx[1]];
  printf("%.2lf %s is %.2lf %s\n", p->x, p->req_units[0], p->y, p->req_units[1]); 
 }
}


int main(int argc, char* argv[]){
 struct conv_data mydata = read_request(stdin);
 struct inferred_data about_mydata = {
  .req_unit_type = {-1, -1}, 
  .req_unit_idx = {-1, -1}
 };

 get_unit_types(&mydata, &about_mydata);
 print_conv_data(&mydata, &about_mydata);
 return 0;
}
