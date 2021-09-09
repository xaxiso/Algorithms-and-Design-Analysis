#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int result[1000002];
int right[1000002];
int left[1000002];

typedef struct Stack{
	int STHtop;
	int RNGtop;
	int n;
	int *STH;
	int *RNG;
}Stack;

int isFull(Stack* stack){
	if(stack->RNGtop == stack->n-1 && stack->STHtop == stack->n-1){
		// printf("stack->STHtop: %d, stack->n-1: %d\n", stack->STHtop, stack->n-1);
    	return 1; 
	}
	else return 0;
} 
  
int isEmpty(Stack* stack){
	if(stack->RNGtop == -1 && stack->STHtop == -1)
    	return 1; 
    else return 0;
}

void pushSTH(Stack* stack, int item){ 
    if (isFull(stack)){ //possibly needs it in the future to know if stack is full
    	printf("FULL\n");
        return;
    }
    stack->STH[++stack->STHtop] = item; 
    printf("%d pushed to STH stack\n", item); 
}

void pushRNG(Stack* stack, int item) { 
    // if (isFull(stack)) 
    //     return; 
    stack->RNG[++stack->RNGtop] = item; 
    printf("%d pushed to RNG stack\n", item); 
} 

int popSTH(Stack* stack) { 
    if (isEmpty(stack)) 
        return INT_MIN; 
    return stack->STH[stack->STHtop--];
}

int popRNG(Stack* stack) { 
    if (isEmpty(stack)) 
        return INT_MIN; 
    return stack->RNG[stack->RNGtop--];
}

int main(){
	int i, n, temp;
	scanf("%d", &n);

	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->n = n;
	stack->STHtop = -1;
	stack->RNGtop = -1;
	stack->STH = (int*)malloc(n*sizeof(int));
	stack->RNG = (int*)malloc(n*sizeof(int));


	for(i=0;i<n;i++){
		scanf("%d", &temp);
		pushSTH(stack, temp);
	}

	for(i=0;i<n;i++){
		scanf("%d", &temp);
		pushRNG(stack, temp);
	}

	for(i=n-1;i>=0;i--){
		int sth = popSTH(stack);
		int rng = popRNG(stack);
		// printf("sth: %d, rng: %d\n", sth, rng);

		if(i==n-1)
	}

	return 0;
}