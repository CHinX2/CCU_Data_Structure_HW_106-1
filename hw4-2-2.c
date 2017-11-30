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
poly* headA = NULL; //head of polynomial a
poly* tailA = NULL; //tail of polynomial a
poly* headB = NULL; //head of polynomial b
poly* tailB = NULL; //tail of polynomial b
poly* headC = NULL; //head of polynomial c
poly* tailC = NULL; //tail of polynomial c

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
poly* pread(poly* pnow,poly* ptail, int exp, float coef)
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
			tmp->next = ptail->next;
			pnow->next = tmp;

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
	pnow->next = pread(pnow->next,ptail, exp, coef);
	return pnow;
}

/*write to element now in polynomial*/
void pwrite(poly* pnow,poly* ptail)
{
	if (pnow == NULL)return;
	printf("%.3f X ^ %d",pnow->coef,pnow->exp);
	if (pnow == ptail)
	{
		printf("\n\n");
		return;
	}
	printf(" + ");
	pwrite(pnow->next,ptail);
	return;
}

/*pread state*/
void stateA(void)
{
	int exp;
	float coef;
	while (1)
	{
		scanf("%d %f", &exp, &coef);
		if (exp == 0 && coef == 0)break; //ending case : 00
		headA = pread(headA,tailA, exp, coef); //insert element
	}
	return;
}

void stateB(void)
{
	int exp;
	float coef;
	while (1)
	{
		scanf("%d %f", &exp, &coef);
		if (exp == 0 && coef == 0)break; //ending case : 00
		headB = pread(headB,tailB, exp, coef); //insert element
	}
	return;
}

void pmult(poly* c, poly* ctail, poly* a, poly* b)
{
	poly *nowA = a;
	poly *nowB = b;

	do {
		float coef = nowA->coef;
		int exp = nowA->exp;
		nowB = b;
		do {
			coef *= nowB->coef;
			exp += nowB->exp;

			c = pread(c, ctail, exp, coef);

			nowB = nowB->next;
		} while (nowB != b);
		nowA = nowA->next;
	} while (nowA != a);

	return;
}

int main()
{
	char state; //state
	char c; //flush char
	while (1)
	{
		/*state table*/
		printf("=======================================\n");
		printf("= Please enter the state              =\n");
		printf("= (a) read in each element of a       =\n");
		printf("= (b) read in each element of b       =\n");
		printf("= (w) print out each element of a,b,c =\n");
		printf("= (q) quit                            =\n");
		printf("=======================================\n");
		scanf("%c", &state);
		switch (state)
		{
		case 'a': //read in the element of polynimial a
			printf("=== pread a ===\n");
			printf("please enter the exponent and coefficient for each existed element in polynomial A\n");
			printf("format : exp+[space]+coef in a line\n");
			printf("if you want to leave this state, please enter 00\n\n");
			stateA();
			c = getchar(); //remove '\n'
			break;
		case 'b': //read in the element of polynimial b
			printf("=== pread b ===\n");
			printf("please enter the exponent and coefficient for each existed element in polynomial B\n");
			printf("format : exp+[space]+coef in a line\n");
			printf("if you want to leave this state, please enter 00\n\n");
			stateB();
			c = getchar(); //remove '\n'
			break;
		case 'w': // print the polynomial
			c = getchar(); //remove '\n'
			printf("=== pwrite ===\n\n");

			/*print polynomial a and b*/
			printf("A : ");
			pwrite(headA, tailA);
			printf("B : ");
			pwrite(headB, tailB);

			pmult(headC, tailC, headA, headB); // c = a * b
											   /*print polynomial c*/
			printf("C : ");
			pwrite(headC, tailC);
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