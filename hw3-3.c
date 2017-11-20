//==============================
// Homework 3 - 3
//==============================
// implement n stacks over a one-dimensional array of the size m
// allow users to push an item to the i-th stack
// use stackFull() if stack i is full
//==============================
// belongs to CHinX2@20171119
//==============================
#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 100 //size of memory
#define MAX_STACK 10 //max num of stacks

int* memory; //memory
int top[MAX_STACK]; //store the top site of each stacks
int bound[MAX_STACK+1]; //store the bound of each stacks
int n = 1; // number of stacks entered by user
int times = 1; //times of memory size now

/*initialize memory with n stacks*/
void initM()
{
	int i;
	top[0] = bound[0] = -1;
	for (i = 1; i < n; i++)
	{
		top[i] = (MEMORY_SIZE / n)*i - 1;
		bound[i] = (MEMORY_SIZE / n)*i - 1;
	}
	bound[n] = MEMORY_SIZE - 1;
	return;
}

/*if the chosen stack is full, expand it*/
int stackFull(int i)
{
	int j, k;
	if (top[i] != bound[i + 1])return 0;

	/*find space in right*/
	for (j = i + 1; j < n; j++)
	{
		if (top[j] != bound[j + 1]) //stake j is not full
		{
			int newE = bound[j + 1]; // the new top of stake j
			int nowE = top[j];       // top of stack j now
			int mvRange = newE - nowE;	 // shift range

			/*shift right all the elements in stack (i+1)~j*/
			while (nowE > bound[i + 1])
			{
				memory[newE--] = memory[nowE--];
			}
			/*set the new bound and top of stack (i+1)~j*/
			for (k = i + 1; k <= j; k++)
			{
				bound[k] += mvRange;
				top[k] += mvRange;
			}

			printf("The %d stack is full, but we find a space from the %d stack, ", i, j);
			printf("and now the size of %d is %d, ", j, bound[j + 1] - bound[j]);
			printf("and the size of %d is %d\n", i, bound[i + 1] - bound[i]);
			return 0;
		}
	}
	/*find space in left*/
	for (j = i - 1; j >= 0; j--)
	{
		if (top[j] != bound[j + 1]) //stake j is not full
		{
			int nowE = bound[j + 1] + 1; // bound of stake j now
			int newE = top[j] + 1;       // the new bound of stack j
			int mvRange = nowE - newE;	 // shift range

			/*shift left all the elements in stack (j+1)~i*/
			while (nowE <= top[i])
			{
				memory[newE++] = memory[nowE++];
			}
			/*set the new bound and top of stack (j+1)~i*/
			for (k = i; k > j; k--)
			{
				bound[k] -= mvRange;
				top[k] -= mvRange;
			}

			printf("The %d stack is full, but we find a space from the %d stack, ", i, j);
			printf("and now the size of %d is %d, ", j, bound[j + 1] - bound[j]);
			printf("and the size of %d is %d\n", i, bound[i + 1] - bound[i]);
			return 0;
		}
	}
	/*memory is full*/
	printf("The %d stack is full and the array is also full, ", i);
	times++;
	int* mem2 = (int*)realloc(memory, sizeof(int)*MEMORY_SIZE*times); // reallocate memory

	if (mem2 != NULL) { // check if memory success to reallocate
		memory = mem2;
	}
	else {
		printf("Fail to resize memory\n");
		return 1;
	}
	printf("but we create a new space for %d, and now the size of %d is %d\n", i, i, bound[i + 1] - bound[i] + MEMORY_SIZE);
	bound[n] = MEMORY_SIZE*times - 1; //set the new bound of the last stack

	return stackFull(i); //check again
}

/*add an item into the i-th stack*/
void push(int i, int item)
{
	int check;
	if (top[i] == bound[i + 1]) //check if the i-th stack is full
		check = stackFull(i);

	if (check == 1) //fail to reallocate memory
	{
		exit(0);
	}
	memory[++top[i]] = item; //push
	return;
}

int main()
{
	/*initialize the memory*/
	memory = (int*)malloc(sizeof(int)*MEMORY_SIZE);
	do {
		if (n < 1 || n>10)printf("Fatal input!\n");
		printf("Please enter the number of stacks (limit : 1~10):\n");
		scanf("%d", &n);
	} while (n < 1 || n>10);
	initM();

	/*push items in chosing stack*/
	while (1)
	{
		int i;
		int item;
		/*input index of stack and value of item*/
		printf("Please enter the index of stack (limit : 0~%d):\n", n - 1);
		printf("(If you want to stop, please enter -1)\n");
		scanf("%d", &i);
		if (i == -1)break;
		if (i < 0 || i >= n)
		{
			printf("Out of range!\n");
			continue;
		}
		printf("Please enter the value of input item (datatype : int):\n");
		scanf("%d", &item);

		/*push item into i-th stack*/
		push(i, item);
	}

	return 0;
}
