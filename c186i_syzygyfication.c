	//r/dailyprogrammer challenge 186 intermediate 
	//syzygyfication

	#include<stdio.h>	
	#include<stdlib.h>
	#include<math.h>
	
	#define NUM_PLANETS 8 // oh, pluto.
	#define FULL_CIRCLE 360
	#define HALF_CIRCLE 180
	#define MAX_ANG_POS_DIFF 1 //max degree difference tolerated
	
	char* planet_names[NUM_PLANETS] = {"mercury", "venus", "earth", "mars", "jupiter", "saturn", "uranus", "neptune"};
	float planet_radii[NUM_PLANETS] = {0.387, 0.723, 1, 1.524, 5.204, 9.582, 19.189, 30.071};
	float planet_years[NUM_PLANETS] = {0.241, 0.615, 1, 1.881, 11.862, 29.457, 84.017, 164.795};
	
	typedef struct _planet_{
		char* name;
		float radius;
		float ang_vel;
		float ang_pos;
	}planet;
	
	planet* init_planets(){
		planet* solar_system = malloc(NUM_PLANETS*sizeof(planet)); 
		
		for (int i = 0; i<NUM_PLANETS; i++){
			solar_system[i].name = 	planet_names[i];	
			solar_system[i].radius = planet_radii[i]; //redundant info! 
			solar_system[i].ang_pos = 0; //initial position is assumed to be same angle for all planets
		}
		
		return solar_system;
	}
	
	void get_angular_position(planet* solar_system, float years){
		
		for(int i = 0; i<NUM_PLANETS; i++){
			// angular_velocity = 360/T; therefore, angular_position = angular_velocity*years = 360/T*years;
			// normalize angular_position with complete circles removed (because 720 degrees = 360 degrees, angular position-wise) 
			float a = years/planet_years[i]; 
			(solar_system+i)->ang_pos = FULL_CIRCLE*(a - floor(a)); //how many degrees?
		}
		
		return; 
	}
	
	void syzygy(planet* solar_system){
		int syzygy[NUM_PLANETS] = {0}; //mark which planets are in syzygy
		float curr_ang_pos, comp_ang_pos, ang_pos_diff;
		
		for(int i = 0; i<NUM_PLANETS; i++){
			//syzygy[i] = -1 ==>the planet is already part of one syzygy. skip it. 
			if(syzygy[i]!=-1){
				syzygy[i] = 1; //current syzygy mark
			
				curr_ang_pos = (solar_system+i)->ang_pos;
				//check for syzygyfication and mark the ones that are syzygied with current planet
				for(int j = i+1; (j<NUM_PLANETS); j++){
					if(syzygy[j]!=-1){//of course, it shouldn't be part of another syzygy- check that.
						comp_ang_pos = (solar_system+j)->ang_pos;
						ang_pos_diff = abs(comp_ang_pos-curr_ang_pos);
						if((ang_pos_diff<MAX_ANG_POS_DIFF) || ((ang_pos_diff<HALF_CIRCLE+MAX_ANG_POS_DIFF) && (ang_pos_diff>HALF_CIRCLE-MAX_ANG_POS_DIFF))){
							syzygy[j] = 1;
						}
							
					}
				}
				
				int sum = 0;
				for (int j = 0; j<NUM_PLANETS; j++){
					if (syzygy[j]==1)
						sum++;
					
				}
				//it's a party only if there are two or more
				if (sum>=2){
					printf("Sun");
					for (int j = i; (j<NUM_PLANETS); j++){
						if(syzygy[j]==1){
							printf("-%s", solar_system[j].name);
							syzygy[j] = -1; //mark it unavailable for other syzygies
						}
					}
					printf(" are in syzygy\n");
				}
			
				for(int j= 0; j<NUM_PLANETS; j++){
					if(syzygy[j]!=-1)
						syzygy[j] = 0;	
				}
			}
			
		}
		
		return;
	}
	
	int main(int argc, char* argv[]){
		float T = atof(argv[1]);
		planet* solar_system = NULL;
		
		solar_system = init_planets();
		
		get_angular_position(solar_system, T);
	
		syzygy(solar_system); 
		
		return 0;	
	}
