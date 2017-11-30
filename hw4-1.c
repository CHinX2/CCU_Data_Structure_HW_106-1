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
	struct node* next; //point to next node
}poly;

poly* avail = NULL; //available
poly* phead = NULL; //head of polynomial
poly* ptail = NULL; //tail of polynomial

/*provide a node from avail to user*/
poly* getNode(void)
{
	poly* node;
	/*if avail isn't null*/
	if (avail)
	{
		node = avail;
		avail = avail->next;
		return node;
	}
	node = (poly*)malloc(sizeof(poly)); //allocate a space to node
	return node;
}

/*read in element of polynomial ; recursive*/
poly* pread(poly* pnow, int exp, float coef)
{
	if (pnow == NULL) //first element
	{
		poly* tmp = getNode(); //require a space
		tmp->exp = exp;
		tmp->coef = coef;
		tmp->next = tmp; //point to itself -> circular
		ptail = tmp; //set the tail
		return tmp;
	}
	else if (pnow->exp == exp) //if the exp is existed, add the coefficient
	{
		pnow->coef += coef;
		return pnow;
	}
	else if (pnow == ptail) //if point to the last one of polynomial now
	{
		if (pnow->exp > exp) //the exp of insert element is smaller than the pointed one
		{
			poly* tmp = getNode();
			tmp->exp = exp;
			tmp->coef = coef;
			pnow->next = tmp;
			tmp->next = phead;
			ptail = tmp; //insert to the tail
			return pnow;
		}
		//the exp of insert element is bigger than the pointed one
		poly* tmp = getNode();
		tmp->exp = exp;
		tmp->coef = coef;
		tmp->next = pnow;
		return tmp;
	}
	else if (pnow->exp < exp) //the exp of insert element is bigger than the pointed one
	{
		poly* tmp = getNode();
		tmp->exp = exp;
		tmp->coef = coef;
		tmp->next = pnow;
		return tmp;
	}
	/*the exp of insert element is smaller then the pointed one, so check the next one*/
	pnow->next = pread(pnow->next, exp, coef);
	return pnow;
}

/*write to element now in polynomial*/
void pwrite(poly* pnow)
{
	if (pnow == NULL)return;
	printf("%.3f X ^ %d",pnow->coef,pnow->exp);
	if (pnow == ptail)
	{
		printf("\n\n");
		return;
	}
	printf(" + ");
	pwrite(pnow->next);
	return;
}

/*pread state*/
void stateR(void)
{
	int exp;
	float coef;
	while (1)
	{
		scanf("%d %f", &exp, &coef);
		if (exp == 0 && coef == 0)break; //ending case : 00
		phead = pread(phead, exp, coef); //insert element
	}
	return;
}

int main()
{
	char state; //state
	char c; //flush char
	while (1)
	{
		/*state table*/
		printf("==============================\n");
		printf("= Please enter the state     =\n");
		printf("= (r) read in each element   =\n");
		printf("= (w) print out each element =\n");
		printf("= (q) quit                   =\n");
		printf("==============================\n");
		scanf("%c", &state);
		switch (state)
		{
		case 'r': //read in the element of polynimial
			printf("=== pread ===\n");
			printf("please enter the exponent and coefficient for each existed element in polynomial\n");
			printf("format : exp+[space]+coef in a line\n");
			printf("if you want to leave this state, please enter 00\n\n");
			stateR();
			c = getchar(); //remove '\n'
			break;
		case 'w': // print the polynomial
			c = getchar(); //remove '\n'
			printf("=== pwrite ===\n\n");
			pwrite(phead);
			break;
		case 'q': //quit the function
			c = getchar(); //remove '\n'
			printf("=== quit ===\n");
			exit(0);
			break;
		default:
			break;
		}
		
	}
	return 0;
}