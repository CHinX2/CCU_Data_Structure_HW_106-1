//==============================
// Homework 4 - 5
//==============================
// Sparse matrix (linked list system)
// mmult() : c = a * b
//==============================
// belongs to CHinX2@20171204
//==============================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50 //size of largest matrix

typedef struct matrixNode {
	struct matrixNode *down;
	struct matrixNode *right;
	int head; //head : 1 / entry : 0
	int col; //column
	int row; //row
	int val; //value
	struct matrixNode *next;
}mnode;

/*read in matrix A*/
mnode* mreadA(mnode *a[])
{
	int rowA, colA, termA, headA;
	int row, col, val, i;
	int nowR = 0; //current row
	mnode *tmp, *last;

	printf("Please enter the number of rows,columns,and number of nonzero terms in matrix A :\n");
	printf("limit : 0 < row=colume < 50 ; 0 <= terms < row*colume\n");
	scanf("%d%d%d", &rowA, &colA, &termA);
	headA = (colA > rowA) ? colA : rowA;

	mnode* node = (mnode*)malloc(sizeof(mnode));
	node->head = 0;
	node->row = rowA;
	node->col = colA;

	if (headA == 0)node->right = node;
	else {
		/*initailize header node*/
		for (i = 0; i < headA; i++)
		{
			tmp = (mnode*)malloc(sizeof(mnode));
			a[i] = tmp;
			a[i]->head = 1;
			a[i]->right = tmp;
			a[i]->next = tmp;
		}
		nowR = 0;
		last = a[0]; //last node in current row

		for (i = 0; i < termA; i++)
		{
			printf("Please enter row, colume, and value:\n");
			printf("format : [row(0~%d)] [col(0~%d)] [value]\n", rowA - 1, colA - 1);
			scanf("%d%d%d", &row, &col, &val);

			/*check if the inserted element is at the row we maintain now*/
			if (row > nowR) {
				/*close the current row as circular*/
				last->right = a[nowR];
				nowR = row;
				last = a[row];
				/*if a[nowR] has had linklist, find the tail */
				while (last->right != a[nowR])
					last = last->right;
			}
			else if (row < nowR)
			{
				last->right = a[nowR];
				nowR = row;
				last = a[row];
				/*if a[nowR] has had linklist, find the tail */
				while (last->right != a[nowR])
					last = last->right;
			}
			/*build new node*/
			tmp = (mnode*)malloc(sizeof(mnode));
			tmp->head = 0;
			tmp->row = row;
			tmp->col = col;
			tmp->val = val;
			/*link to row list*/
			last->right = tmp;
			last = tmp;
			/*link to col list*/
			a[col]->next->down = tmp;
			a[col]->next = tmp;
		}
		/*close last row as circular*/
		last->right = a[nowR];
		/*close all col lists as circular*/
		for (i = 0; i < colA; i++)
			a[i]->next->down = a[i];
		/*link all header nodes as circular*/
		for (i = 0; i < headA - 1; i++)
			a[i]->next = a[i + 1];
		a[headA - 1]->next = node;
		node->right = a[0];
	}
	return node; //return the matrix
}
/*read in matrix B as transpose form (row <-> col)*/
mnode* mreadB(mnode *a[])
{
	int rowA, colA, termA, headA;
	int row, col, val, i;
	int nowR = 0; //current row
	mnode *tmp, *last;

	printf("Please enter the number of rows,columns,and number of nonzero terms in matrix A :\n");
	printf("limit : 0 < row=colume < 50 ; 0 <= terms < row*colume\n");
	scanf("%d%d%d", &colA, &rowA, &termA); //change row <-> column
	headA = (colA > rowA) ? colA : rowA;

	mnode* node = (mnode*)malloc(sizeof(mnode));
	node->head = 0;
	node->row = rowA;
	node->col = colA;

	if (headA == 0)node->right = node;
	else {
		/*initailize header node*/
		for (i = 0; i < headA; i++)
		{
			tmp = (mnode*)malloc(sizeof(mnode));
			a[i] = tmp;
			a[i]->head = 1;
			a[i]->right = tmp;
			a[i]->next = tmp;
		}
		nowR = 0;
		last = a[0]; //last node in current row

		for (i = 0; i < termA; i++)
		{
			printf("Please enter row, colume, and value:\n");
			printf("format : [row(0~%d)] [col(0~%d)] [value]\n", colA - 1, rowA - 1);
			scanf("%d%d%d", &col, &row, &val); //change row <-> column

			/*check if the inserted element is at the row we maintain now*/
			if (row > nowR) {
				/*close the current row as circular*/
				last->right = a[nowR];
				nowR = row;
				last = a[row];
				/*if a[nowR] has had linklist, find the tail */
				while (last->right != a[nowR])
					last = last->right;
			}
			else if (row < nowR)
			{
				last->right = a[nowR];
				nowR = row;
				last = a[row];
				/*if a[nowR] has had linklist, find the tail */
				while (last->right != a[nowR])
					last = last->right;
			}
			/*build new node*/
			tmp = (mnode*)malloc(sizeof(mnode));
			tmp->head = 0;
			tmp->row = row;
			tmp->col = col;
			tmp->val = val;
			/*link to row list*/
			last->right = tmp;
			last = tmp;
			/*link to col list*/
			a[col]->next->down = tmp;
			a[col]->next = tmp;
		}
		/*close last row as circular*/
		last->right = a[nowR];
		/*close all col lists as circular*/
		for (i = 0; i < colA; i++)
			a[i]->next->down = a[i];
		/*link all header nodes as circular*/
		for (i = 0; i < headA - 1; i++)
			a[i]->next = a[i + 1];
		a[headA - 1]->next = node;
		node->right = a[0];
	}
	return node; //return the transpose matrix
}

mnode* mmult(mnode *a, mnode *b, mnode *c[])
{
	int termC = 0, headC;
	int row, col, val, i, j;
	row = col = val = 0;
	int nowR = 0; //current row
	mnode *tmp, *last;
	if (a->col != b->col) //check if it is a legal calculation
	{
		printf("fatal multiply!\n");
		return NULL;
	}

	headC = (a->row > b->row) ? a->row : b->row;

	mnode* node = (mnode*)malloc(sizeof(mnode));
	node->head = 0;
	node->col = b->row;
	node->row = a->row;

	if (headC == 0)node->right = node;
	else {
		/*initailize header node*/
		for (i = 0; i < headC; i++)
		{
			tmp = (mnode*)malloc(sizeof(mnode));
			c[i] = tmp;
			c[i]->head = 1;
			c[i]->right = tmp;
			c[i]->next = tmp;
		}
		nowR = 0;
		last = c[0]; //last node in current row

		mnode *tmpa, *tmpb;
		mnode *heada = a->right, *headb = b->right;

		for (i = 0; i < a->row; i++)
		{
			headb = b->right;
			for (j = 0; j < b->row; j++)
			{
				val = 0;
				row = i;
				col = j;
				tmpa = heada->right;
				tmpb = headb->right;
				while (tmpa != heada&&tmpb != headb)
				{
					if (tmpa->col == tmpb->col)
					{
						val += tmpa->val*tmpb->val;
						tmpa = tmpa->right;
						tmpb = tmpb->right;
					}
					else if(tmpa->col > tmpb->col)
						tmpb = tmpb->right;
					else if(tmpa->col < tmpb->col)
						tmpa = tmpa->right;
				}
		
				/*check if the inserted element is at the row we maintain now*/
				if (row > nowR) {
					/*close the current row as circular*/
					last->right = c[nowR];
					nowR = row;
					last = c[row];
					/*if a[nowR] has had linklist, find the tail */
					while (last->right != c[nowR])
						last = last->right;
				}
				else if (row < nowR)
				{
					last->right = c[nowR];
					nowR = row;
					last = c[row];
					/*if a[nowR] has had linklist, find the tail */
					while (last->right != c[nowR])
						last = last->right;
				}
				/*build new node for nonzero terms*/
				if (val != 0)
				{
					tmp = (mnode*)malloc(sizeof(mnode));
					tmp->head = 0;
					tmp->row = row;
					tmp->col = col;
					tmp->val = val;
					termC++; //calculate the number of nonzero terms
					/*link to row list*/
					last->right = tmp;
					last = tmp;
					/*link to col list*/
					c[col]->next->down = tmp;
					c[col]->next = tmp;
				}
				headb = headb->next; //next row of b
			}
			heada = heada->next; //next row of a
		}
		/*close last row as circular*/
		last->right = c[nowR];
		/*close all col lists as circular*/
		for (i = 0; i < node->col; i++)
			c[i]->next->down = c[i];
		/*link all header nodes as circular*/
		for (i = 0; i < headC - 1; i++)
			c[i]->next = c[i + 1];
		c[headC - 1]->next = node;
		node->right = c[0];
	}
	node->val = termC;
	return node;
}

/*print the sparse matrix*/
void mwrite(mnode* a)
{
	if (a == NULL)return;
	int i = 0;
	mnode *tmp, *head = a->right;

	/*print the element in each row*/
	printf("row\tcol\tval\n");
	printf("%d\t%d\t%d\n", a->row, a->col, a->val);
	for (i = 0; i < a->row; i++)
	{
		for (tmp = head->right; tmp != head; tmp = tmp->right)
		{
			if(tmp->val!=0)
				printf("%d\t%d\t%d\n", tmp->row, tmp->col, tmp->val);
		}
		head = head->next; //next row
	}
	printf("\n");
	return;
}

int main()
{
	char state;//state
	char t;
	mnode *hda[MAX], *hdb[MAX], *hdc[MAX];
	mnode *a, *b, *c;

	while (1)
	{
		/*state table*/
		printf("=========================================\n");
		printf("= Please enter the state                =\n");
		printf("= (a) read in each element of matrix a  =\n");
		printf("= (b) read in each element of matrix b  =\n");
		printf("= (m) print out each element of c(a*b)  =\n");
		printf("= (q) quit                              =\n");
		printf("=========================================\n");
		scanf("%c", &state);
		switch (state)
		{
		case 'a': //read in the element of polynimial a
			printf("=== read matrix A ===\n");
			a = mreadA(hda);
			t = getchar(); //remove '\n'
			break;
		case 'b': //read in the element of polynimial b
			printf("=== read matrix B ===\n");
			b = mreadB(hdb);
			t = getchar(); //remove '\n'
			break;
		case 'm': // print the polynomial
			t = getchar(); //remove '\n'
			printf("=== matrix C ===\n\n");
			c = mmult(a, b, hdc);
			mwrite(c);
			free(c);
			break;
		case 'q': //quit the function
			t = getchar(); //remove '\n'
			printf("=== quit ===\n");
			exit(0);
			break;
		default:
			break;
		}
	}
	return 0;
}
