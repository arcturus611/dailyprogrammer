	//r/dailyprogrammer challenge 186 intermediate 
	//syzygyfication

	#include<stdio.h>	
	#include<stdlib.h>
	#include<math.h>
	#include<stdbool.h>
	
	#define NUM_PLANETS 8 // oh, pluto.
	#define PI 3.14159
	#define TOL_LAMBDA_DIFF 0.005
	
	char* planet_names[NUM_PLANETS] = {"mercury", "venus", "earth", "mars", "jupiter", "saturn", "uranus", "neptune"};
	double planet_radii[NUM_PLANETS] = {0.387, 0.723, 1, 1.524, 5.204, 9.582, 19.189, 30.071};
	double planet_years[NUM_PLANETS] = {0.241, 0.615, 1, 1.881, 11.862, 29.457, 84.017, 164.795};
	
	typedef struct _celestial_body_{
		char* name;
		double radius;
		double angle;
		double x;
		double y;
	}celestial_body;
	
	celestial_body* init_celestial_bodies(){
		celestial_body* solar_system = malloc((1+NUM_PLANETS)*sizeof(celestial_body)); 
		
		solar_system[8].name = "sun";
		solar_system[8].radius = 0;
		solar_system[8].angle = 0;
		solar_system[8].x = 0;
		solar_system[8].y = 0;
		
		for (int i = 0; i<NUM_PLANETS; i++){
			solar_system[i].name = 	planet_names[i];	
			solar_system[i].radius = planet_radii[i]; 
			solar_system[i].angle = 0; //initial position is assumed to be same angle for all celestial_bodys
		}
		
		return solar_system;
	}
	
	void get_position(celestial_body* solar_system, double years){
		
		for(int i = 0; i<NUM_PLANETS; i++){
			// angular_velocity = 2*PI/T; therefore, angular_position = angular_velocity*years = (2*PI/T)*years;
			// normalize angular_position with complete circles removed (because 720 degrees = 360 degrees, angular position-wise) 
			double a = years/planet_years[i]; 
			(solar_system+i)->angle = 2*PI*a; //how many degrees?
			(solar_system+i)->x = ((solar_system+i)->radius)*cos((solar_system+i)->angle);
			(solar_system+i)->y = ((solar_system+i)->radius)*sin((solar_system+i)->angle);
		}
		
		return; 
	}
	
	bool check_collinearity(double x1, double y1, double x2, double y2, double x3, double y3){
		double lambda1 = (x1-x2)/(x2-x3);
		double lambda2 = (y1-y2)/(y2-y3);

		bool are_collinear = (fabs(lambda1-lambda2)<TOL_LAMBDA_DIFF); //for perfectly collinearity, this would be zero
		return are_collinear;
	}
	
	void print_syzygy(bool* s, celestial_body* solar_system){
		int syz = 0;
		for(int i= 0; i<NUM_PLANETS+1; i++)
			syz+=s[i];
			
		if(syz>=3){
			for(int i = 0; i<NUM_PLANETS+1; i++){
				if(s[i]==1)
					printf("%s-", (solar_system+i)->name);
			}
			printf(" are in syzygy\n");
		}
		return;
	}
	
	void syzygy(celestial_body* solar_system){
		bool syzygy_index[9] = {0}; 
		double x1, x2, x3;
		double y1, y2, y3;
		bool are_collinear;
		
		//check three celestial bodies
		for(int i= 0; i<NUM_PLANETS-1;i++){
		
			for(int j = i+1; j<NUM_PLANETS; j++){
			
				//if(i!=j){
				for(int k = j+1; k<NUM_PLANETS+1; k++){
					//if(k!=i && k!=j){
					are_collinear = false;
					//so darn ugly...
					x1 = (solar_system+i)->x;
					x2 = (solar_system+j)->x;
					x3 = (solar_system+k)->x;
					y1 = (solar_system+i)->y;
					y2 = (solar_system+j)->y;
					y3 = (solar_system+k)->y;
					
					are_collinear = check_collinearity(x1, y1, x2, y2, x3, y3);
						
					if(are_collinear){
						syzygy_index[i] = 1;
						syzygy_index[j] = 1;
						syzygy_index[k] = 1;				
					}
					//}
				}
				
				print_syzygy(syzygy_index, solar_system);
				//reset syzygy_index array
				for(int k = 0; k<NUM_PLANETS +1; k++)
					syzygy_index[k] = 0;
				//}	
			}
			
		}
		
		return;
	}
	
	int main(int argc, char* argv[]){
		double T = atof(argv[1]);
		celestial_body* solar_system = NULL;
		
		solar_system = init_celestial_bodies();
		
		get_position(solar_system, T);
			
		printf("\n");
	
		syzygy(solar_system); 
		
		return 0;	
	}
