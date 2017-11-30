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
#define MAXAVAIL 20

typedef struct node {
	int exp;  //exponent
	float coef; //coefficient
	node* next; //point to next node
}poly;

poly* avail = NULL;
poly* phead = NULL;

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
	if (pnow == phead)
	{
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
	if (pnow->next == phead)return;
	printf(" + ");
	pwrite(pnow->next);
	return;
}

int main()
{
	avail = initAvail(avail);
	phead = (poly*)malloc(sixeof(poly));
	phead->next = phead;

}