// r/DailyProgrammer - August 10
// Convex Hull (Graham Scan)
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct Point{
 float x; //x-coordinate
 float y; //y-coordinate
 float theta; //angle between x-axis and vector from pt to ref pt
}pt;

float ccw(pt* p1, pt* p2, pt* p3){
 float x1 = p1->x; 
 float y1 = p1->y; 
 float x2 = p2->x; 	
 float y2 = p2->y; 
 float x3 = p3->x; 
 float y3 = p3->y;
 return (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1); 
}

void swapPoints(pt** P, int idx1, int idx2){
 pt* temp = (pt *)malloc(sizeof(pt));
 temp->x = (*(P+idx1))->x; 
 temp->y = (*(P+idx1))->y; 
 temp->theta = (*(P+idx1))->theta;

 (*(P+idx1))->x = (*(P+idx2))->x; 
 (*(P+idx1))->y = (*(P+idx2))->y; 
 (*(P+idx1))->theta = (*(P+idx2))->theta; 

 (*(P+idx2))->x = temp->x; 
 (*(P+idx2))->y = temp->y; 
 (*(P+idx2))->theta = temp->theta; 
}

void findLowestY(pt** P, int N){
 float y_lowest = (*P)->y; 
 float y_curr;
 int i;  
 for(i = 1; i<N; i++){
  y_curr = (*(P+i))->y;
  if(y_curr<y_lowest){
   swapPoints(P, 0, i); 
  }
 }

}

int cmpfunc(const void* a, const void* b){
 const pt* p1 = *(const pt**)a; 
 const pt* p2 = *(const pt**)b; 
 int d = p1->theta - p2->theta; 
 return d;
}

int main(int argc, char** argv){ 

 int nverts; 
 scanf("%d", &nverts); 
 
 pt* Point[nverts]; 

 for (int i = 0; i<nverts; i++){
  Point[i] = (pt *)malloc(sizeof(pt));
  scanf("%f, %f", &(Point[i]->x), &(Point[i]->y));
  Point[i]->theta = 0; 
 }

 findLowestY(Point, nverts); 

 Point[nverts] = (pt *)malloc(sizeof(pt)); 
 Point[nverts]->x = Point[0]->x;
 Point[nverts]->y = Point[0]->y; 
 Point[nverts]->theta = Point[0]->theta; 

 float x_temp, y_temp; 
 for (int i = 1; i<nverts; i++){
  y_temp = Point[i]->y-Point[0]->y; 
  x_temp = Point[i]->x - Point[0]->x; 
  Point[i]->theta = atan2(y_temp, x_temp);
 }
 
 qsort(Point, nverts, sizeof(pt *), cmpfunc); 

// M will denote the number of points on the convex hull.
 int nhull = 1; 
 for (int i = 2; i<=nverts; i++){
  // find next valid point on convex hull 
  while(ccw(*(Point+nhull-1), *(Point+nhull), *(Point+i))<=0){ 
  // clockwise turn of points means not on hull, so skip ahead.
   if(nhull>1){
    nhull-=1;
   }
   else if(i==nverts){
    break;
   }
   else {
    i += 1;
   }
  }
 
  nhull += 1;
  swapPoints(Point, nhull, i);  
 } 

 // print convex hull points
 printf("Points on convex hull are: \n");
 for (int i = 0; i<nhull; i++){
  printf("%f, %f\n", (*(Point+i))->x, (*(Point+i))->y);
 }

 return 0;
}
