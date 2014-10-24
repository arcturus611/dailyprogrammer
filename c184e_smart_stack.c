	//r/dailyprogrammer
	//c184e
	//smart stack

	#include<stdio.h>
	#include<stdlib.h>
	#include<time.h>
	#define MIN_NUM 1
	#define MAX_NUM 50

	typedef struct smart_stack_{
		int data;
		struct smart_stack_* prevInStack;
		struct smart_stack_* nextInValue; // we are defining 'next value' to mean 'greater'
	}SmartStack;

	SmartStack* pTopOfStack;
	SmartStack* pSmallestValue; 

	void push_to_stack(int);
	void push_in_order(int);
	void display_stack();
	void display_ordered();
	void pop_from_stack();
	void pop_in_order();
	void display_stack_size();
	void remove_greater(int);

	void push_to_stack(int d){
		printf("Pushing to stack: %d\n", d);
		SmartStack* pNew = malloc(sizeof(SmartStack)); //allocating memory on the heap

		pNew->data = d;
		pNew->prevInStack = pTopOfStack;// pTopOfStack is global, hence this works
		pNew->nextInValue = NULL;

		pTopOfStack = pNew;

		push_in_order(d);

		return;
	}

	void pop_from_stack(){
		if (pTopOfStack==NULL){ 
			printf("Can't pop from empty stack!\n");
			return;
		}
		pop_in_order();
		SmartStack* pTemp = pTopOfStack;
		pTopOfStack = pTopOfStack->prevInStack;
		free(pTemp);
		printf("Popped!\n");
		return;
	}

	void push_in_order(int d){
		if (pSmallestValue==NULL){
			pSmallestValue = pTopOfStack;
		}
		else{
			SmartStack* pCounter = pSmallestValue;
			SmartStack* pLast = NULL;
			SmartStack* pTemp = NULL;

			while(pCounter!=NULL){
				if (d>pCounter->data){
					pLast = pCounter;
					pCounter = pCounter->nextInValue;
				}
				else break;
			}
			if (pLast==NULL){
				pTemp = pSmallestValue;
				pSmallestValue = pTopOfStack;
				pSmallestValue->nextInValue = pTemp;
				return;				
			}
			pLast->nextInValue = pTopOfStack;
			pTopOfStack->nextInValue = pCounter;
			return;
		}	
	}

	void pop_in_order(){
		SmartStack* pCounter = pSmallestValue;
		SmartStack* pLast = pCounter;
		while(pCounter!=pTopOfStack){
			pLast = pCounter;
			pCounter = pCounter->nextInValue;
		}
		pLast->nextInValue = pCounter->nextInValue;	
		if (pLast==pSmallestValue) pSmallestValue = pLast->nextInValue;
		return;
	}

	void display_stack(void){
		printf("Stack is...");
		if(pTopOfStack==NULL){
			printf("empty!\n");
			return;
		}
		else printf("%d", pTopOfStack->data);

		SmartStack* pCounter = pTopOfStack->prevInStack;
		while(pCounter!=NULL){
			printf(", %d", pCounter->data);
			pCounter = pCounter->prevInStack;
		}
		printf("\n");
		return;
	}

	void display_ordered(void){
		printf("Ordered stack is...");
		if(pSmallestValue==NULL){
			printf("empty!\n");
			return;
		}
		else printf("%d", pSmallestValue->data);
	
		SmartStack* pCounter = pSmallestValue->nextInValue;
		while(pCounter!=NULL){
			printf(", %d", pCounter->data);
			pCounter = pCounter->nextInValue;
		}
		printf("\n");
		return;
	}

	void display_stack_size(void){
		if(pTopOfStack==NULL) printf("Stack size zero!\n");
		else{
			int stack_size = 0;
			SmartStack* pCounter = pTopOfStack;
			while(pCounter!=NULL){	
				stack_size++;		
				pCounter = pCounter->prevInStack;	
			}
			printf("Stack size is %d\n", stack_size);		
		}
		return;
	}

	void remove_greater(int d){
		if (pTopOfStack==NULL){
			printf("Stack already empty!\n");
			return;
		}
		printf("Removing elements greater than %d\n", d);
		SmartStack* pCounter = pSmallestValue;
		SmartStack* pLast = NULL;
		while(pCounter!=NULL && d>pCounter->data){
			pLast = pCounter;
			pCounter = pCounter->nextInValue;
		}	
		if (pLast==NULL){// if d is the smallest value of all
			pSmallestValue = NULL;
			pTopOfStack = NULL;	
			return;
		}
		if(pCounter==NULL) {
			printf("No elements greater than %d\n", d);
			return;
		}

		pLast->nextInValue = NULL;

		pCounter = pTopOfStack;
		pLast = NULL;
		while(pCounter!=NULL){
			if(pCounter==pTopOfStack){
				if(d<=pCounter->data){
					pCounter = pCounter->prevInStack;
					pTopOfStack = pCounter;
				}else{
					pLast = pCounter;
					pCounter = pCounter->prevInStack;
				}
			}else{
				if(d<=pCounter->data){
					pLast->prevInStack = pCounter->prevInStack;
					pCounter = pCounter->prevInStack;
				}else{
					pLast = pCounter;
					pCounter = pCounter->prevInStack;
				}
			}
		}

		return;
	}

	int main(int argc, char* argv[]){
		pTopOfStack = NULL;
		pSmallestValue = NULL;

		display_stack_size();

		srand(time(NULL));
		int d;
	
		for (int i = 0; i<10; i++){
			d = MIN_NUM + rand()%(MAX_NUM-MIN_NUM+1);
			push_to_stack(d);
		}

		display_stack();

		display_ordered();

		push_to_stack(100);
		display_stack(); display_ordered();

		push_to_stack(99);
		display_stack(); display_ordered();

		pop_from_stack();
		display_stack(); display_ordered();

		display_stack_size();

		remove_greater(28);
		display_stack(); 
		display_ordered();
		display_stack_size();

		remove_greater(332);
		display_stack(); 
		display_ordered();
		display_stack_size();

		return 0;
	}
