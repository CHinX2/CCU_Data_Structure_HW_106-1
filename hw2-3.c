//==============================
// Homework 2 - 3
//==============================
// invMatrix() to get inverse of invertible matrix
// by the formula : inverse(A) = adjoint(A) / determiniant(A)
//==============================
// belongs to CHinX2@20171108
//==============================
//Warning : 1.Please use Code::Blocks to compile&run
//			  it may has some strange error on Visual Studio 2017
//            (sub-function can't return to main-function)
//			2.This program is unfinished, still has lots of bug
//==============================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 37 //max num of terms +1

typedef struct {
	int col; //column
	int row; //row
	float val; //value
}term;

term invA[MAX];
int nowA = 1;
term res[MAX];

void fastTranspose(term*, term*);
int invMatrix(term*);
int det(term*);
int poww(int);
void cofactor(term*);
int minor(term*, int, int);

int main()
{
	term a[MAX];
	float val;
	int det;
	int i, j, num, checkR, checkC;
	num = 0; //count the non-0 term
	checkR = checkC = 15;
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
			scanf("%f", &val);
			if (val != 0)
			{
				a[num + 1].row = i;
				a[num + 1].col = j;
				a[num + 1].val = val;
				checkR -= i;
				checkC -= j;
				num++;
			}
		}
	}
	a[0].val = num; //the number of non-0 terms

	if (checkR > 0 || checkC > 0)printf("The matrix is non - invertible.\n");
	else {
		det = invMatrix(a); //inverse matrix a, store in invA, return determinant

		if (det == 0)printf("The matrix is non - invertible.\n");
		else {
			printf("%d\n",det);
			/*print the transposed matrix*/
			printf("	row	col	value\n");
			for (i = 0; i < nowA; i++)
			{
				printf("a[%d]\t%d\t%d\t%.2f\n", i, invA[i].row, invA[i].col, invA[i].val);
			}
		}
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

/*determinant*/
int det(term* a)
{
	int i, col, row;
	int d = 0;
    col = a[1].col;
	for (i = 1; i <= a[0].val; i++)
	{
        if(a[i].col==col)
		{
		    row = a[i].row;
            int c = poww(col + row)*minor(a, row, col); //cofactor C-ij
            d += (a[i].val*c);
		}
	}
	return d;
}

int poww(int n)  // (-1)^(row+col)
{
	int k = n%2;
	if(k==0)return 1;
	return -1;
}

int minor(term* a, int row, int col) //find M-ij
{
	term b[MAX];
	int i,j;
	int detV = 0;
	j = 1;
	b[0].row = a[0].row - 1;
	b[0].col = a[0].col - 1;
	b[0].val = 0;

	/*build the sub matrix*/
	for (i = 1; i <= a[0].val; i++)
	{
		if (a[i].row != row&&a[i].col != col)
		{
			if (a[i].row > row)b[j].row = a[i].row - 1;
			else b[j].row = a[i].row;
			if (a[i].col > col)b[j].col = a[i].col - 1;
			else b[j].col = a[i].col;
			b[j].val = a[i].val;
			j++;
		}
	}
	b[0].val = j - 1;

	if (b[0].row == 1)
	{
		return b[1].val;
	}
	else {
        int cl = b[1].col;
		for (i = 1; i <= b[0].val; i++)
		{
			if(b[i].col==cl)
			{
			    int rw = b[i].row;
                int c = poww(cl+rw)*minor(b, rw, cl); //cofactor C-ij
                //printf("%d,%d  %d\n",rw,cl,c);
                detV += (b[i].val*c);
			}
		}
	}

	return detV;
}

int minor2(term* a, int row, int col) //for cofactor
{
	term b[MAX];
	int i,j;
	int checkR[a[0].row-1],checkC[a[0].col-1];
	int detV = 0;
	j = 1;
	b[0].row = a[0].row - 1;
	b[0].col = a[0].col - 1;
	b[0].val = 0;

	for(i=0;i<b[0].row;i++)
    {
        checkR[i]=0;
        checkC[i]=0;
    }

	/*build the sub matrix*/
	for (i = 1; i <= a[0].val; i++)
	{
		if (a[i].row != row&&a[i].col != col)
		{
			if (a[i].row > row)b[j].row = a[i].row - 1;
			else b[j].row = a[i].row;
			if (a[i].col > col)b[j].col = a[i].col - 1;
			else b[j].col = a[i].col;
			b[j].val = a[i].val;

			/*add check point*/
			checkR[b[j].row]++;
			checkC[b[j].col]++;

			j++;
		}
	}
	b[0].val = j - 1;

	for(i=0;i<b[0].row;i++) //check if if there has one row/col with no non-0 value
    {
        if(checkR[i]==0)return 0;
        if(checkC[i]==0)return 0;
    }

	if (b[0].row == 1)
	{
		return b[1].val;
	}
	else {
        int cl = b[1].col;
		for (i = 1; i <= b[0].val; i++)
		{
			if(b[i].col==cl)
			{
			    int rw = b[i].row;
                int c = poww(cl+rw)*minor(b, rw, cl); //cofactor C-ij
                //printf("%d,%d  %d\n",rw,cl,c);
                detV += (b[i].val*c);
			}
		}
	}

	return detV;
}

void cofactor(term* a) //to fill adjoint(a) with cofactor c-ij
{
    int col,row;
    for (row = 0; row <6; row++)
	{
	    for(col=0;col<6;col++)
	    {
            int c = poww(row+col)*minor2(a, row, col); //cofactor C-ij
            printf("%d,%d  %d\n",row,col,c);
            if (c != 0) {
                res[0].val++;
                res[nowA].row = row;
                res[nowA].col = col;
                res[nowA].val = c;
                nowA++;
            }
	    }
    }
}

int invMatrix(term* a) // inverse(A) = adj(A)/det(A)
{
	res[0].col = 6;
	res[0].row = 6;
	res[0].val = 0;
	cofactor(a);
	int detV = det(a); //get determiniant
	if (detV == 0)return 0;
	fastTranspose(res,invA); //transpose the result array
	int i;
	for (i = 1; i <= invA[0].val; i++)invA[i].val /= detV; // all element in result / det(A)
	return detV;
}
