//==============================
// Homework 2 - 4
//==============================
// Sparse matrix representation:
// 2-dimensional array:bits[rows][columns]
// 1-dimensional array:value[num_of_nonzero_terms]
//==============================
// d = a + b
//==============================
// belongs to CHinX2@20171108
//==============================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 36 //max terms of matrix

typedef struct {
	int bits[6][6]; //use to store position in matrix
	int val[36]; //value
}term;

int matrixAdd(term*, term*, term*);

int main()
{
	term a[MAX], b[MAX];
	term d[MAX];
	int val;
	int i, j, numA, numB, numD;
	numB = 0; //count the non-0 term in b

	/*set matrix a*/
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 6; j++)a->bits[i][j] = 0;
	}
	a->bits[0][0] = a->bits[0][3] = a->bits[0][5] = 1;
	a->bits[1][1] = a->bits[1][2] = 1;
	a->bits[2][3] = a->bits[4][0] = a->bits[5][2] = 1;
	a->val[0] = 15;
	a->val[1] = 22;
	a->val[2] = -15;
	a->val[3] = 11;
	a->val[4] = 3;
	a->val[5] = -6;
	a->val[6] = 91;
	a->val[7] = 28;
	numA = 8;

	/*read in value of matrix b*/
	printf("請輸入6*6的矩陣,每項以空白或換行隔開:\n");
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 6; j++)
		{
			scanf("%d", &val);
			if (val != 0)
			{
				b->bits[i][j] = 1;
				b->val[numB] = val;
				numB++;
			}
		}
	}

	numD = matrixAdd(a, b, d); // d = a + b

	/*print the result as request format*/
	printf("[Matrix d]\n");
	printf("==bits-array==\n");
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 6; j++)
		{
			printf("%d ",d->bits[i][j]);
		}
		printf("\n");
	}
	printf("==value-array==\n");
	for (i = 0; i < numD; i++)
	{
		printf("%d\n", d->val[i]);
	}
	printf("\n");

	return 0;
}

/*do d = a + b ,and return num of value in matrix d*/
int matrixAdd(term* a, term* b, term* d)
{
	int i, j, k1, k2, k3; //use k to save the index of term react now
	i = j = k1 = k2 = k3 = 0;

	/*triverse the matrix and store the operating result in d*/
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 6; j++)
		{
			d->bits[i][j] = 0;
			if (a->bits[i][j] == 1) { //a exist at pos[i][j]
				d->bits[i][j] = 1;

				if (b->bits[i][j] == 1) { //b exist -> store a+b in d's value
					d->val[k3] = a->val[k1] + b->val[k2];
					k1++;
					k2++;
					k3++;
				}
				else { //store a's value in d's value
					d->val[k3] = a->val[k1];
					k1++;
					k3++;
				}
			}
			else if (b->bits[i][j] == 1) { //a = 0, but b exist
				d->bits[i][j] = 1;
				d->val[k3] = b->val[k2];
				k2++;
				k3++;
			}
		}
	}
	return k3; //non-0 terms in d
}

