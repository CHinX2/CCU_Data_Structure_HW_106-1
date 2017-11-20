//==============================
// Homework 2 - 1
//==============================
// pmult() : A(x) * B(x) = D(x)
// A,B,and D are polynomials
//==============================
// belongs to CHinX2@20171107
//==============================
#include <stdio.h>
#include <stdlib.h>
#define MAX 250

typedef struct node {
	int exp;  //exponent
	float coef; //coefficient
}poly;

poly terms[MAX]; //to store A(x) ,B(x) ,C(x)
int avail = 0; //available in terms

int checkExp(int, int, int);
void pmult(int, int, int, int, int*, int*);


int main()
{
	int startA, finishA, startB, finishB;
	int startD, finishD;
	int e; //temp of exp value
	float c; //temp of coefficient value

	/*store A(x)*/
	startA = startB = finishA = finishB = 0;
	printf("叫块A(X)兜Ω盽计籔Ωよ计,ㄢ计丁フ筳秨:\n");
	printf("(兜Α经逼,盽计疊翴计,Ωよ计タ俱计)\n");
	printf("(斗X0Ωよ兜挡Ю)\n");
	do{
		scanf("%f %d",&c,&e);
		terms[avail].coef = c;
		terms[avail].exp = e;
		avail++;
	} while (e != 0);
	finishA = avail - 1;

	/*store B(x)*/
	startB = avail;
	printf("叫块B(X)兜Ω盽计籔Ωよ计,ㄢ计丁フ筳秨:\n");
	printf("(兜Α经逼,盽计疊翴计,Ωよ计タ俱计)\n");
	do{
		scanf("%f %d", &c, &e);
		terms[avail].coef = c;
		terms[avail].exp = e;
		avail++;
	} while (e != 0);
	finishB = avail - 1;

	/*calculate D(x) and store in array*/
	startD = avail;
	finishD = startD;
	pmult(startA, finishA, startB, finishB, &startD, &finishD); //A(x) * B(x) = D(x)

	/*print the array*/
	int i;
	printf("\n");
	for (i = 0; i < avail; i++)
	{
		printf("%.2f %d ", terms[i].coef, terms[i].exp);
	}

	/*print the array as polynomials A(x), B(x), D(x)*/
	/*unordered*/
	printf("\n\nA(x) : ");
	for (i = 0; i < finishA; i++)
	{
		printf("%.2f X^%d + ", terms[i].coef, terms[i].exp);
	}
	printf("%.2f X^%d", terms[finishA].coef, terms[finishA].exp);

	printf("\nB(x) : ");
	for (i = startB; i < finishB; i++)
	{
		printf("%.2f X^%d + ", terms[i].coef, terms[i].exp);
	}
	printf("%.2f X^%d", terms[finishB].coef, terms[finishB].exp);

	printf("\nD(x) : ");
	for (i = startD; i < finishD; i++)
	{
		printf("%.2f X^%d + ", terms[i].coef, terms[i].exp);
	}
	printf("%.2f X^%d", terms[finishD].coef, terms[finishD].exp);
	printf("\n");

	return 0;
}

/*check if the exponent has exist in array*/
int checkExp(int exp, int startD, int finishD)
{
	while (startD <= finishD)
	{
		if (terms[startD].exp == exp)return startD;
		startD++;
	}
	return avail;
}

/*multiply A and B then store in the tail of the same array as D*/
void pmult(int startA, int finishA, int startB, int finishB, int* startD, int* finishD)
{
	if (startA <= finishA && startB <= finishB)
	{
		int i, j;
		for (i = startA; i <= finishA; i++)
		{
			for (j = startB; j <= finishB; j++)
			{
				int en = terms[i].exp + terms[j].exp; //exp now
				float cn = terms[i].coef*terms[j].coef; //coeff now

				int check = checkExp(en, *startD, *finishD); //check if exp has existed
				if (check == avail) //exp is new in this array
				{
					terms[avail].coef = cn;
					terms[avail].exp = en;
					*finishD = avail;
					avail++;
				}
				else //exp has existed
				{
					terms[check].coef += cn;
				}
			}
		}
	}
}
