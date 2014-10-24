	//r/dailyprogrammer
	//challenge 183, easy, semantic version sort
	//gcc -std=c99 -g c183e_semver.c -o c183e_semver
	//Inputs: ./c183e_semver N
	#include<stdio.h>
	#include<string.h>
	#include<stdlib.h>
	#include<ctype.h>

	#define MAX_VER_LEN 20
	#define MAX_LABEL_LEN 20

	typedef	struct semver_{
		int major;
		int minor;
		int patch;
		char* label;
		char* ver_name;
	}semver;
	
	void get_version_parts(semver* s, char* line){
		s->ver_name = malloc(MAX_VER_LEN);
		strcpy(s->ver_name, line);

		char* p = line;
		s->major = atoi(p);

		while(isdigit(*p++));
		s->minor = atoi(p);

		while(isdigit(*p++));
		s->patch = atoi(p);

		while(isdigit(*p++)); p--;
		s->label = malloc(MAX_LABEL_LEN); // if you don't do this, trying to access s->label will result in a segmentation fault
		if(((*p) == '\n') || ((*p) == '+')) 
			s->label = NULL;
		else if ((*p) == '-'){
			strcpy(s->label, p+1);
		}

		return;
	}	

	semver* read_versions(int N){
		printf("Num of inputs: %d\n", N);
		semver* S = malloc(N*sizeof(semver)); // allocate space on heap
		char line[MAX_VER_LEN + 1]; //temporary array on stack
		char* p;
		for (int i = 0; i<N; i++){
			fgets(line, MAX_VER_LEN, stdin);
			line[strcspn(line, "\n")] = '\0';
			get_version_parts(&(S[i]), line);
		}
		return S;
	}

	int cmp_fnc(const void* a_, const void* b_){
		semver a = *(semver *)a_;
		semver b = *(semver *)b_;
		if(a.major<b.major)
			return -1;
		else if (a.major>b.major)
			return 1;
		
		if(a.minor<b.minor)
			return -1;
		else if (a.minor>b.minor)
			return 1;
		
		if(a.patch<b.patch)
			return -1;
		else if (a.patch>b.patch)
			return 1;

		if (a.label==NULL) return 1;
		if (b.label== NULL) return -1;
		return strcmp(a.label, b.label);
										
	}

	void sort_semantic_versions(semver* S, int N){
		qsort(S, N, sizeof(semver), cmp_fnc);
		printf("\n\nSorted semantic versions are...\n");
		for (int i = 0; i<N; i++){
			printf("%s\n", S[i].ver_name);
		}
		return;
	}

	int main(int argc, char* argv[]){
		int N = atoi(argv[1]);
		semver* S = read_versions(N);
		sort_semantic_versions(S, N);
		return 0;
	}
