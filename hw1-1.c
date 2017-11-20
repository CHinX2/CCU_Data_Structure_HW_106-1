//------------------------------
// Homework 1 - 1
// Tower of Hanoi
//------------------------------
// Number of item = n
// Step = 2^n - 1 
// if n = 64, then step = 2^64-1 = 1.8446744e+19 
//------------------------------
// belongs to CHinX2 @ 20171030
//------------------------------
#include <stdio.h>
#include <stdlib.h>
#define MAX 64	//define the max number of item 
int step = 0;	//count the moving steps

//===Function List===
void moveS(int,char*,char*,char*);	//move items from stack to stack
//===Function List===

void moveS(int val,char* s1,char* s2,char* s3) //move items from stack to stack
{
	if (val == 0)return;
	if (val == 1) //the last item
	{
		step++;
		printf("%d : item with value %d, moves from %s to %s\n", step, val, s1, s3);
		return;
	}
	else {
		moveS(val - 1, s1, s3, s2); //deal to move items from s1 to s2
		step++;
		printf("%d : item with value %d, moves from %s to %s\n", step, val, s1, s3);
		moveS(val - 1, s2, s1, s3); //deal to move items from s2 to s3
		return;
	}
}


int main()
{
	char s1[3] = { "s1" };
	char s2[3] = { "s2" };
	char s3[3] = { "s3" };
	int val = MAX;
	
	moveS(val, s1, s2, s3);

	return 0;
}

