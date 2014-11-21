	//r/dailyprogrammer challenge (easy) 94
	//breaking bad style elements
	
	#include<stdio.h>
	#include<ctype.h>
	#include<strings.h>
	#include<string.h>
	
	#define NUM_ELEMENTS 118
	
	char* elements_list[] = {"Ac","Ag","Al","Am","Ar","As","At","Au","B","Ba","Be","Bh","Bi",
       "Bk","Br","C","Ca","Cd","Ce","Cf","Cl","Cm","Cn","Co","Cr","Cs",
       "Cu","Db","Ds","Dy","Er","Es","Eu","F","Fe","Fl","Fm","Fr","Ga",
       "Gd","Ge","H","He","Hf","Hg","Ho","Hs","I","In","Ir","K","Kr","La",
       "Li","Lr","Lu","Lv","Md","Mg","Mn","Mo","Mt","N","Na","Nb","Nd","Ne",
       "Ni","No","Np","O","Os","P","Pa","Pb","Pd","Pm","Po","Pr","Pt","Pu",
       "Ra","Rb","Re","Rf","Rg","Rh","Rn","Ru","S","Sb","Sc","Se","Sg","Si","Sm",
       "Sn","Sr","Ta","Tb","Tc","Te","Th","Ti","Tl","Tm","U","Uuo","Uup","Uus","Uut",
       "V","W","Xe","Y","Yb","Zn","Zr"};
       
       void highlight_elements(char* str){
        int idx; char* c = NULL; int l; int s_l; 
        s_l = strlen(str);
       	for (int i = 0; i<NUM_ELEMENTS; i++){
       		l = strlen(elements_list[i]);
       		for(c = str; *c; c++){
	       		idx = strncasecmp(c, elements_list[i], l);
       			if (idx == 0){
       				int num_pre_chars = c-str;
       				int num_post_chars = s_l - num_pre_chars;
       				printf("%.*s[%.*s]%.*s\n",  num_pre_chars, str, l, elements_list[i], num_post_chars, str + num_pre_chars + l);
       			}
       		}	
       	}
       }
       
       int main(int argc, char* argv[]){
       	char* str = argv[1];
       	highlight_elements(str);
       	return 0;
       }
