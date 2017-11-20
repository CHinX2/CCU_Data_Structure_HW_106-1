//==============================
// Homework 3 - 2
//==============================
// convert from infix expression to postfix notation
// support : &&, !!, <<, >>, <=, >=, !=, <, >, +, -, *, /, %
//==============================
// belongs to CHinX2@20171114
//==============================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*index symbols by precedence*/
#define lparen 0	// (
#define rparen 1	// )
#define nots 2		// !
#define times 3		// *
#define divide 4	// /
#define mod 5		// %
#define plus 6		// +
#define minus 7		// -
#define shiftR 8	// >>
#define shiftL 9	// <<
#define bigger 10	// >
#define smaller 11	// <
#define bigEql 12	// >=
#define smaEql 13	// <=
#define notEql 14	// !=
#define aand 15		// &
#define EOS 16
#define operand 17

/*array stored each symbol indexed by the define use to print out the symbol*/
char symbol[][3] = { "(",")","!!","*","/","%","+","-",">>","<<",">","<",">=","<=","!=","&&" };
/*in-stack precedence*/
int isp[] = { 0,19,18,14,14,14,11,11,8,8,3,3,3,3,2,1,0 };
/*incoming precedence*/
int icp[] = { 20,19,18,14,14,14,11,11,8,8,3,3,3,3,2,1,0 };

char a[105] = { '\0' }; //use to store input string
char* str = a; // a pointer point to the head of array which store the input string
int stack[105]; // an array use to be a stack
int sLen = 0; // number of in-stack items now

/*get the next token*/
int getToken(char* symbol)
{
	*symbol = *str++;
	while(*symbol==' ')*symbol = *str++; //check if symbol is point to space
	switch (*symbol)
	{
		case '(':
			return lparen;
		case ')':
			return rparen;
		case '+':
			return plus;
		case '-':
			return minus;
		case '*':
			return times;
		case '/':
			return divide;
		case '%':
			return mod;
		case '!':
			return nots;
		case '<':
			return smaller;
		case '>':
			return bigger;
		case '&':
			return aand;
		case '\0':
			return EOS;
		case '\n':
			return EOS;
		default:
			return operand;
	}
}
/*get the next token of < */
int getNext1(char* symbol)
{
	*symbol = *str++;
	while (*symbol == ' ')*symbol = *str++; //check if symbol is point to space
	switch (*symbol)
	{
		case '<':			// <<
			return shiftL;
		case '=':			// <=
			return smaEql;
		case '\0':
			return EOS;
		default:
			str--;
			return smaller;
	}
}
/*get the next token of > */
int getNext2(char* symbol)
{
	*symbol = *str++;
	while (*symbol == ' ')*symbol = *str++; //check if symbol is point to space
	switch (*symbol)
	{
	case '>':			// >>
		return shiftR;
	case '=':			// >=
		return bigEql;
	case '\0':
		return EOS;
	default:
		str--;
		return bigger;
	}
}
/*get the next token of ! */
int getNext3(char* symbol)
{
	*symbol = *str++;
	while (*symbol == ' ')*symbol = *str++; //check if symbol is point to space
	switch (*symbol)
	{
		case '!':			// !!
			return nots;
		case '=':			// !=
			return notEql;
		case '\0':
			return EOS;
		default:
			str--;
			return nots;
	}
}

void postfix(void) // convert infix to postfix
{
	char c;
	int token; // precedence check
	stack[0] = EOS; // use to check if stack is void
	sLen++;

	/*read in the input string and check it by char til the end of string*/
	while ((token = getToken(&c))!=EOS)
	{
		if (token == operand) //token is not precedence
		{
			printf("%c", c);
		}
		else if (token == rparen) // token is )
		{
			/*print out items in stack til meet the symbol (*/
			while (stack[sLen-1] != lparen)
			{
				printf("%s",symbol[stack[--sLen]]);
			}
			sLen--; // pop ( in stack ; do not print it
		}
		else {
			/*check the next symbol of <, >, !, &*/
			if (token == smaller)token = getNext1(&c); // < or << or <=
			else if (token == bigger)token = getNext2(&c); // > or >> or >=
			else if (token == nots)token = getNext3(&c); // !! or !=
			if (token == aand)str++; // &&

			/*precedence check : if the top one in stack is bigger than token, pop & print out the top one*/
			while (isp[stack[sLen-1]] >= icp[token])
			{
				printf("%s", symbol[stack[--sLen]]);
			}

			stack[sLen] = token; // push token in stack
			sLen++;
		}
	}
	/*if there still has symbols in stack, print them out*/
	while (stack[sLen-1]!= EOS)
	{
		printf("%s", symbol[stack[--sLen]]);
	}
	printf("\n");
}

int main()
{
	/*read in the input string from standard unput and store in array a*/
	printf("請輸入運算式(infix expression),總長度小於100:\n");
	fgets(a, 105, stdin);

	/*convert to postfix*/
	printf("The postfix expression:\n");
	postfix();

	return 0;
}