//==============================
// Homework 2 - 2
//==============================
// fastTranspose() to transpose matrix
//==============================
// belongs to CHinX2@20171108
//==============================
//Warning : Please use Code::Blocks to compile&run
//			it may has some strange error on Visual Studio 2017 
//          (sub-function can't return to main-function)
//==============================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 37 //max num of terms +1

typedef struct {
	int col; //column
	int row; //row
	int val; //value
}term;

void fastTranspose(term*, term*);

int main()
{
	term a[MAX],b[MAX];
	int val;
	int i, j, num;
	num = 0; //count the non-0 term

	/*initial size of matrix*/
	a[0].col = 6;
	a[0].row = 6;
	a[0].val = 0;

	/*read in value of matrix*/
	printf("請輸入6*6的矩陣,每項以空白或換行隔開:\n");
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 6; j++)
		{
			scanf("%d", &val);
			if (val != 0)
			{
				a[num+1].row = i;
				a[num+1].col = j;
				a[num+1].val = val;
				num++;
			}
		}
	}
	a[0].val = num; //the number of non-0 terms

	fastTranspose(a, b); //transpose matrix a and store in b

	/*print the transposed matrix*/
	printf("[Transpose Matrix a\n");
	printf("	row	col	value\n");
	for (i = 0; i <= num; i++)
	{
		printf("a[%d]\t%d\t%d\t%d\n", i, b[i].row, b[i].col, b[i].val);
	}
	return 0;
}

/*transpose matrix a and store in b*/
void fastTranspose(term* a, term* b) 
{
	/*store num of column,row,and terms in b[0]*/
	b[0].col = a[0].col;
	b[0].row = a[0].row;
	b[0].val = a[0].val;

	int num = a[0].val;
	int pos[7]; //use to store the transpose position of terms
	int i, j;
	for (i = 0; i < 7; i++)pos[i] = 1; //initialize
	for (i = 1; i <= num; i++)
	{
		//calculate the terms at cloumn(i) in a,and store in prefix sum form from pos(i+1) to end
		for (j = a[i].col; j < 7; j++)
			pos[j + 1]++;
	}
	int nVal;
	for (i = 1; i <= num; i++)
	{
		//value in pos(i) use to be index of each terms that have new-row(i) as ole-col(i)
		nVal = pos[a[i].col];

		b[nVal].col = a[i].row;
		b[nVal].row = a[i].col;
		b[nVal].val = a[i].val;
		pos[a[i].col]++;
	}
	return;
}
