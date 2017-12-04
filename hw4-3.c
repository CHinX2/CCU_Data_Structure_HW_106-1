//==============================
// Homework 4 - 3
//==============================
// pmult() : c = a * b
// pwrite() : enter value of X, print C(X)
//==============================
// belongs to CHinX2@20171202
//==============================
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node {
	int exp;  //exponent
	float coef; //coefficient
	int tail; //check if it is tail
	struct node* next; //point to next node
}poly;

poly* avail = NULL; //available a
poly* headA = NULL; //head of polynomial a
poly* headB = NULL; //head of polynomial b
poly* headC = NULL; //head of polynomial c


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
		tmp->tail = 1; //set the tail
		return tmp;
	}
	if (pnow->exp == exp) //if the exp is existed, add the coefficient
	{
		pnow->coef += coef;
		return pnow;
	}
	else if (pnow->tail == 1) //if point to the last one of polynomial now
	{
		if (pnow->exp > exp) //the exp of insert element is smaller than the pointed one
		{
			poly* tmp = getNode();
			tmp->exp = exp;
			tmp->coef = coef;
			tmp->next = pnow->next; //linked to head
			tmp->tail = 1; //set new tail
			pnow->next = tmp;
			pnow->tail = 0; //it is not the tail

			return pnow;
		}
		//the exp of insert element is bigger than the pointed one
		poly* tmp = getNode();
		tmp->exp = exp;
		tmp->coef = coef;
		tmp->next = pnow;
		tmp->tail = 0;
		return tmp;
	}
	else if (pnow->exp < exp) //the exp of insert element is bigger than the pointed one
	{
		poly* tmp = getNode();
		tmp->exp = exp;
		tmp->coef = coef;
		tmp->next = pnow;
		tmp->tail = 0;
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

	printf("%.3f X ^ %d", pnow->coef, pnow->exp);
	if (pnow->tail == 1)
	{
		printf("\n\n");
		return;
	}
	printf(" + ");
	pwrite(pnow->next);
	return;
}

/*pread state*/
poly* stateR(poly* phead)
{
	int exp;
	float coef;
	while (1)
	{
		scanf("%d %f", &exp, &coef);
		if (exp == 0 && coef == 0)break; //ending case : 0 0
		phead = pread(phead, exp, coef); //insert element
	}
	return phead;
}

/*multiple : c = a * b */
poly* pmult(poly* a, poly* b)
{
	poly *nowA = a;
	poly *nowB = b;
	poly* tmp = NULL; //point to the linklist of mult result

	do {
		nowB = b;
		do {
			float coef = nowA->coef * nowB->coef;
			int exp = nowA->exp + nowB->exp;

			tmp = pread(tmp, exp, coef); //link the new element

			if (nowB->tail == 1)break;
			nowB = nowB->next;
		} while (nowB != NULL);

		if (nowA->tail == 1)break;
		nowA = nowA->next;
	} while (nowA != NULL);

	return tmp; //return to c
}

/*to evaluate a(x)*/
float peval(poly* a, float x)
{
	poly *nowA = a;
	float res = 0; //the result of a(x)

	do {
		res += (nowA->coef*powf(x, nowA->exp));
		if (nowA->tail == 1)break;
		nowA = nowA->next;
	} while (nowA != NULL);

	return res; //return the result of a(x)
}

int main()
{

	char state; //state
	char c; //flush char
	float x = 0; //the constant x
	while (1)
	{
		/*state table*/
		printf("=======================================\n");
		printf("= Please enter the state              =\n");
		printf("= (a) read in each element of a       =\n");
		printf("= (b) read in each element of b       =\n");
		printf("= (x) read in the value of x          =\n");
		printf("= (w) print out c(x)                  =\n");
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
			headA = stateR(headA);
			c = getchar(); //remove '\n'
			break;
		case 'b': //read in the element of polynimial b
			printf("=== pread b ===\n");
			printf("please enter the exponent and coefficient for each existed element in polynomial B\n");
			printf("format : exp+[space]+coef in a line\n");
			printf("if you want to leave this state, please enter 0 0\n\n");
			headB = stateR(headB);
			c = getchar(); //remove '\n'
			break;
		case 'x': //read in the value of x
			x = 0;
			printf("=== given x ===\n");
			printf("please enter the value of X (default : X = 0)\n");
			printf("datatype : float\n");
			scanf("%f", &x);
			c = getchar(); //remove '\n'
			break;
		case 'w': // print the polynomial
			c = getchar(); //remove '\n'
			printf("=== pwrite ===\n\n");

			/*print polynomial a and b*/
			printf("A : ");
			pwrite(headA);
			printf("B : ");
			pwrite(headB);

			headC = pmult(headA, headB); // c = a * b
			/*print polynomial c*/
			printf("C : ");
			pwrite(headC);

			float result = peval(headC, x); //c(x)
			printf("C(%.3f) : %.3f\n\n", x, result);
			free(headC);
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