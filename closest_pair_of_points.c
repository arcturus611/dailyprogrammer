/*
My grandmother and I are moving to a new neighborhood. The houses haven't yet been built, but the map has been drawn. We'd like to live as close together as possible. She makes some outstanding cookies, and I love visiting her house on the weekend for delicious meals - my grandmother is probably my favorite cook!

Please help us find the two lots that are closest together so we can build our houses as soon as possible. 
*/

	#include<stdio.h>
	#include<stdlib.h>
	#include<math.h>
	#include<time.h>

        struct point{
		double x; 
		double y;
	}; 

	struct winner_info{
		float dist; 
		struct point W1;
		struct point W2; 
	};

	size_t parse_input(FILE* fp, struct point **inp){
		int N; 
		fscanf(fp, "%d\n", &N); 
		
		*inp = malloc(sizeof(**inp)*N); 
		
		for(int i = 0; i<N; i++)
			fscanf(fp, "(%lf, %lf)\n", &((*inp+i)->x), &((*inp+i)->y)); 
		
		return N;
	}
	
	int cmpfunc_x(const void* a, const void* b){
		float x1 = ((struct point *)a)->x; 
		float x2 = ((struct point *)b)->x; 
		return 1?(x1-x2)>0:0; 
	}
	
	int cmpfunc_y(const void* a, const void* b){
		float y1 = ((struct point *)a)->y;
		float y2 = ((struct point *)b)->y;
		return 1?(y1-y2)>0:0;  
	}
	
	float calc_euclidean_dist(struct point a, struct point b){
		float d = sqrt((a.x - b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
		return d;
	}
	
	int minimum_of(int x, int y){
		int m = (x?x<y:y);
		return m;
	}
	
	struct winner_info* brute_force_closest_pair(int n, struct point* P){
		float best_dist = 1000000.0;
		
		float curr_dist;
		struct point winning_points[2];
		struct winner_info* W  = malloc(sizeof(struct winner_info));
		
		for(int i= 0; i<=n-2; i++){
			for(int j = i+1; j<n; j++){
				curr_dist = calc_euclidean_dist(P[i], P[j]);
				if(curr_dist<best_dist){
					best_dist = curr_dist; 
					winning_points[0].x = P[i].x; 
					winning_points[0].y = P[i].y; 
					
					winning_points[1].x = P[j].x;
					winning_points[1].y = P[j].y; 
				}
			}
		}	
		
		W->dist = best_dist;
		W->W1 = winning_points[0];
		W->W2 = winning_points[1];
		
		return W;
	}
	
	struct winner_info* closest_split_pair(struct point* P, int N, float delta, float mid_x){
		float best_dist = 1000000.0; /*Arbitrary initial large value*/
		float curr_dist; 
		struct winner_info* W = malloc(sizeof(struct winner_info)); 
		W->dist = best_dist; 
		
		/*Determine the strip*/
		struct point* P_strip;
		int count = 0;
		for(int i = 0; i<N; i++){
			count = count + (P[i].x>=(mid_x-delta) && P[i].x<=(mid_x+delta));
		} /*So that we can malloc correctly*/
		
		P_strip = malloc(sizeof(struct point)*count);
		
		int j =0;
		for(int i = 0; i<N; i++){
			if((P[i].x>= (mid_x-delta)) && (P[i].x<= (mid_x+delta))){
				P_strip[j].x = P[i].x;
				P_strip[j].y = P[i].y;
				j++;
			}
		}
		
		/*Get closest split pair in strip*/
		for(int i = 0; i<count-1; i++){
			/*Watch Tim Roughgarden's coursera video for proof of the magic number 7. But in a nutshell, this is because we can have only 8 boxes around x_mid, each of length delta with at most one point per box. If you have more, then it'll follow that two points within the same side have distance less than delta, which goes against the definition of delta*/
			int j_max;
			if ((count - i - 1)>7) j_max = 7;
			else j_max = count - i - 1; 

			for(int j = 1; j<=j_max; j++){
				curr_dist = calc_euclidean_dist(P_strip[i], P_strip[i+j]); /*For each of the points in the strip we perform a constant number of operations*/

				if(curr_dist<best_dist){
					best_dist = curr_dist;
					W->dist =  best_dist;
					W->W1 = P_strip[i];
					W->W2 = P_strip[i+j];
				}
			}
		}
		
		return W;
	}
	
	struct winner_info* closest_pair(int N, struct point* Px, struct point* Py){
		struct winner_info* W_temp, *W; 
		
		/*base case*/
		if (N<=3){
			W = brute_force_closest_pair(N, Px);
			return W;
		}
		
		/*create the array of points sorted vertically that are on each half of the plane*/
		int mid = N/2;
		
		struct point* Pyl = malloc(sizeof(struct point)*mid); 
		struct point* Pyr = malloc(sizeof(struct point)*(N-mid)); 
		int li = 0, ri = 0;
		for(int i = 0; i<N; i++){
			if (Py[i].x<=Px[mid-1].x){
				Pyl[li].x = Py[i].x;
				Pyl[li].y = Py[i].y; 
				li++;
			}else{
				Pyr[ri].x = Py[i].x;
				Pyr[ri].y = Py[i].y;
				ri++;
			}
				
		}
		
		/*Recursive call to function on left half of points*/
		struct winner_info* L1 = closest_pair(mid, Px, Pyl); 

		/*Recursive call to function on right half of points*/
		struct winner_info* R1 = closest_pair(N-mid, Px+mid, Pyr); 
		
		/*Best out of the two halves*/
		if ((L1->dist) < (R1->dist))
			W_temp = L1; 
		else W_temp = R1; 

		/*Invoke closest split pair*/
		struct winner_info* S1 = closest_split_pair(Py, N, W_temp->dist, Px[mid-1].x);
		
		/*Best of all*/
		if((W_temp->dist)<(S1->dist))
			W = W_temp; 
		else W = S1; 
		  
		return W;
	}
	
	int main(int argc, char* argv[]){
		FILE* fp = fopen("grandma_coords.txt", "r"); 
		struct point* input_coords;
		size_t num_coords; 
		clock_t start, end; 
		double cpu_time_used; 
		
		num_coords = parse_input(fp, &input_coords); 
	
		/*creating two arrays sorted by x-coord and y-coord*/
		struct point* sorted_x_coords, *sorted_y_coords; 
		sorted_x_coords = malloc(sizeof(struct point)*num_coords);
		sorted_y_coords = malloc(sizeof(struct point)*num_coords);
		
		for(int i = 0; i<num_coords; i++){
			sorted_x_coords[i].x = input_coords[i].x; 
			sorted_x_coords[i].y = input_coords[i].y; 
			sorted_y_coords[i].x = input_coords[i].x; 
			sorted_y_coords[i].y = input_coords[i].y; 
		}
		
		qsort(sorted_x_coords, num_coords, sizeof(struct point), cmpfunc_x);
		qsort(sorted_y_coords, num_coords, sizeof(struct point), cmpfunc_y);		 
		
		/*Invoking the closest pair algo*/
		start = clock();
		struct winner_info* winner = closest_pair(num_coords, sorted_x_coords, sorted_y_coords);
		end = clock();
		cpu_time_used = ((double)(end-start))/CLOCKS_PER_SEC;
		printf("The winning points are (%lf, %lf) and (%lf, %lf)\n", (winner->W1).x, (winner->W1).y, (winner->W2).x, (winner->W2).y);
		printf("\n Time taken by program = %f\n", cpu_time_used);
		
		return 0;
	}
