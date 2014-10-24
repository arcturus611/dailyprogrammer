	//r/dailyprogrammer easy challenge 181, basic equations
	//using pcre. god help me. (oct 18)
	// gcc -std=c99 -g -Wall c181e_basic_equations.c -o c181e_basic_equations -lpcre

	#include "pcre.h"            	/* PCRE lib        NONE  */
	#include <stdio.h>              /* I/O lib         C89   */
	#include <stdlib.h>             /* Standard Lib    C89   */
	#include <string.h>             /* Strings         C89   */

	#define EQ_LEN 20
	
	typedef struct eq_{
		float y_coef;
		float x_coef;
		float bias_value;
	}Eq;

	Eq* read_eq_coeffs(char* testStrings[]){ 
	  Eq* equation_set = malloc(2*sizeof(Eq));
	  pcre *reCompiled;
	  pcre_extra *pcreExtra;
	  int pcreExecRet;
	  int subStrVec[30];
	  const char *pcreErrorStr;
	  int pcreErrorOffset;
	  char *aStrRegex;
	  char **aLineToMatch;
	  const char *psubStrMatchStr;
	  int j;

	  aStrRegex = "(\\d*\\.?\\d*)[a-z]?\\s*=\\s*(\\-?)(\\d*\\.?\\d*)[a-z]?\\s*(\\+?\\-?)\\s*(\\d*\\.?\\d*)";  

	  // First, the regex string must be compiled.
	  reCompiled = pcre_compile(aStrRegex, PCRE_EXTENDED, &pcreErrorStr, &pcreErrorOffset, NULL);

	  // pcre_compile returns NULL on error, and sets pcreErrorOffset & pcreErrorStr
	  if(reCompiled == NULL) {
	    printf("ERROR: Could not compile '%s': %s\n", aStrRegex, pcreErrorStr);
	    exit(1);
	  } /* end if */

	  // Optimize the regex
	  pcreExtra = pcre_study(reCompiled, 0, &pcreErrorStr);

	  /* pcre_study() returns NULL for both errors and when it can not optimize the regex.  The last argument is how one checks for errors (it is NULL if everything works, and points to an error string otherwise. */
	  if(pcreErrorStr != NULL) {
	    printf("ERROR: Could not study '%s': %s\n", aStrRegex, pcreErrorStr);
	    exit(1);
	  } /* end if */

	  int line_idx = 0;
	  for(aLineToMatch=testStrings; *aLineToMatch != NULL; aLineToMatch++) {
	    /* Try to find the regex in aLineToMatch, and report results. */
	    pcreExecRet = pcre_exec(reCompiled,
		                    pcreExtra,
		                    *aLineToMatch, 
		                    strlen(*aLineToMatch),  // length of string
		                    0,                      // Start looking at this point
		                    0,                      // OPTIONS
		                    subStrVec,
		                    30);                    // Length of subStrVec

	    // Report what happened in the pcre_exec call..
	    if(pcreExecRet < 0) { // Something bad happened..
	      switch(pcreExecRet) {
	      case PCRE_ERROR_NOMATCH      : printf("String did not match the pattern\n");        break;
	      case PCRE_ERROR_NULL         : printf("Something was null\n");                      break;
	      case PCRE_ERROR_BADOPTION    : printf("A bad option was passed\n");                 break;
	      case PCRE_ERROR_BADMAGIC     : printf("Magic number bad (compiled re corrupt?)\n"); break;
	      case PCRE_ERROR_UNKNOWN_NODE : printf("Something kooky in the compiled re\n");      break;
	      case PCRE_ERROR_NOMEMORY     : printf("Ran out of memory\n");                       break;
	      default                      : printf("Unknown error\n");                           break;
	      } /* end switch */
	    } else {
	    //  printf("Result: We have a match!\n");
		
	      // At this point, rc contains the number of substring matches found...
	      if(pcreExecRet == 0) {
		printf("But too many substrings were found to fit in subStrVec!\n");
		// Set rc to the max number of substring matches possible.
		pcreExecRet = 30 / 3;
	      } /* end if */

	      // PCRE contains a handy function to do the above for you:
	      float y_coef, x_coef, bias_value;
	      int x_coef_sign, bias_value_sign; 
	      for(j=0; j<pcreExecRet; j++) {
		pcre_get_substring(*aLineToMatch, subStrVec, pcreExecRet, j, &(psubStrMatchStr));
	
		switch(j){
			case 0:
				break;
			case 1: 
				if (strlen(psubStrMatchStr)==0)
					y_coef = 1;
				else y_coef = atof(psubStrMatchStr);
				break;
			case 2: 
				if (strlen(psubStrMatchStr)==0)
		                  x_coef_sign = 1;
				else if (strcmp(psubStrMatchStr, "+")==0)
				  x_coef_sign = 1;
				else if (strcmp(psubStrMatchStr, "-")==0)
		                  x_coef_sign = -1;
				break;
			case 3: 
				if (strlen(psubStrMatchStr)==0)
					x_coef = 1;
				else x_coef = atof(psubStrMatchStr);
				break;
			case 4: 
				if (strlen(psubStrMatchStr)==0)
		                  bias_value_sign = 0;
				else if (strcmp(psubStrMatchStr, "+")==0)
				  bias_value_sign = 1;
				else if (strcmp(psubStrMatchStr, "-")==0)
		                  bias_value_sign = -1;
				break;
		                  
			case 5:	
				if (strlen(psubStrMatchStr)==0)
					bias_value = 0;
				else bias_value = atof(psubStrMatchStr);
				break;	
		}
	      } /* end for */
	      
	      equation_set[line_idx].y_coef = y_coef;
	      equation_set[line_idx].x_coef = x_coef_sign*x_coef;
	      equation_set[line_idx].bias_value = bias_value_sign*bias_value;	
		
	      // Free up the substring
	      pcre_free_substring(psubStrMatchStr);
	    }  /* end if/else */
	    line_idx++;
	      
	  } /* end for */
	  
	  // Free up the regular expression.
	  pcre_free(reCompiled);
	      
	  // Free up the EXTRA PCRE value (may be NULL at this point)
	  if(pcreExtra != NULL)
	    pcre_free(pcreExtra);

	  return equation_set;

	}

	void solve_equations(Eq* read_equations){
	 float m[2];
	 float c[2];
	 for (int i= 0; i<2; i++){
	   read_equations[i].x_coef /= read_equations[i].y_coef;
	   m[i] = read_equations[i].x_coef;
	   read_equations[i].bias_value /= read_equations[i].y_coef;
	   c[i] = read_equations[i].bias_value;
	   read_equations[i].y_coef = 1; 
	 }
	 
	 if(m[0] == m[1]){
	   if(c[0] == c[1]){
	    printf("Infinite solutions\n");
	    return;
	   }else{
	    printf("No solution \n");
	    return;
	   }
	 }else{
	   float x = (c[1]-c[0])/(m[0]-m[1]);
	   float y = m[0]*x + c[0];
	   printf("Solution is--- (%.2f, %.2f)\n", x, y);
	 }
	return;
	}
		
	char** get_equations(){
		char** equations = malloc(2*sizeof(char*));
		for (int i = 0;i<2; i++){
			equations[i] = malloc(EQ_LEN*sizeof(char)); 
			fgets(equations[i], EQ_LEN, stdin);
			char* ret_char = strchr(equations[i], '\n');
			equations[ret_char-equations[0]] = '\0';
		}
		return equations;
	}

	int main(int argc, char *argv[]) {

		char** equations = NULL;//malloc(2*sizeof(char*)); ?No need to malloc here since we are malloc'ing inside function?
		equations = get_equations();
		
		Eq* read_equations = NULL; //malloc(2*sizeof(Eq));
	  	read_equations =  read_eq_coeffs(equations); 
	        printf("Stored values: %.1f, %.1f, %.1f\n", read_equations[0].y_coef, read_equations[0].x_coef, read_equations[0].bias_value);
		printf("Stored values: %.1f, %.1f, %.1f\n", read_equations[1].y_coef, read_equations[1].x_coef, read_equations[1].bias_value);

	     	solve_equations(read_equations);
	     	
	     	for (int i = 0; i<2; i++)
	     		free(equations[i]);
	     	free(equations);
	  	free(read_equations);
	  	
	  	return 0;

	} /* end func main */

