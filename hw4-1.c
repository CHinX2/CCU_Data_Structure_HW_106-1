//==============================
// Homework 4 - 1
//==============================
// use circular linklist to store polynomial
// use available space list to erase polynimial efficiently
// pread() : read in element of polynomial(ordered by expon decreasing)
//			 a new space for a node can be created only if avail points to NULL
// pwrite() : output all nodes not in the available list space
//==============================
// belongs to CHinX2@20171130
//==============================
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int exp;  //exponent
	float coef; //coefficient
	node* next; //point to next node
}poly;

poly* avail = NULL;
poly* phead = NULL;
poly* ptail = NULL;

/*provide a node from avail to user*/
poly* getNode(void)
{
	poly* node;
	if (avail)
	{
		node = avail;
		avail = avail->link;
		return node;
	}
	node = (poly*)malloc(sizeof(poly));
	return node;
}

/*return a node to avail*/
void backNode(poly* node)
{
	node->next = avail;
	avail = node;
}

/*read in element of polynomial*/
poly* pread(poly* pnow, int exp, float coef)
{
	if (pnow == NULL)
	{
		poly* tmp = getNode();
		tmp->exp = exp;
		tmp->coef = coef;
		tmp->next = tmp;
		ptail = tmp;
		return tmp;
	}
	if (pnow->exp == exp)
	{
		pnow->coef += coef;
		return pnow;
	}
	else if (pnow == ptail)
	{
		if (pnow->exp > exp)
		{
			poly* tmp = getNode();
			tmp->exp = exp;
			tmp->coef = coef;
			pnow->next = tmp;
			tmp->next = phead;
			ptail = tmp;
			return pnow;
		}
		poly* tmp = getNode();
		tmp->exp = exp;
		tmp->coef = coef;
		tmp->next = pnow;
		return tmp;
	}
	else if (pnow->exp < exp)
	{
		poly* tmp = getNode();
		tmp->exp = exp;
		tmp->coef = coef;
		tmp->next = pnow;
		return tmp;
	}
	pnow->next = pread(pnow->next, exp, coef);
	return pnow;
}

/*write to element now in polynomial*/
void pwrite(poly* pnow)
{
	printf("%f X ^ %d",pnow->coef,pnow->exp);
	if (pnow == ptail)return;
	printf(" + ");
	pwrite(pnow->next);
	return;
}

int main()
{
	int exp;
	float coef;
	char state;
	while (1)
	{
		printf("========================\n");
		printf("= Please enter the state ")
		scanf("%c", &state);
	}
}