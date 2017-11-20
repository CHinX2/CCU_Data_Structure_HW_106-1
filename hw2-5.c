//==============================
// Homework 2 - 5
//==============================
// strinins(string s, string t,int i)
// t is inserted to s starting at the i-th position
//==============================
// belongs to CHinX2@20171108
//==============================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strinins(char*, char*, int*);

int main()
{
	/* initialize string s, t and int i */
	char s[200] = { '\0' };
	char t[200] = { '\0' };
	int i = 0;
	/*string insert function*/
	strinins(s, t, &i);

	return 0;
}

/*read in string s & t,then insert t to s[i]*/
void strinins(char* s, char* t, int* i)
{
	printf("請輸入字串s(長度<100):");
	scanf("%s", s);
	printf("請輸入字串t(長度<100):");
	scanf("%s", t);
	printf("請輸入整數i(0~100):");
	scanf("%d", i);

	printf("%s\n", s); //print string s
	printf("%s\n", t); //print string t

	int tLen = strlen(t); //tLen = length of t
	int sLen = strlen(s); //sLen = length of s
	if (sLen < *i)printf("ERROR!\n"); //check if i is fatal number that is bigger than length of s
	else {
		int k;
		for (k = 0; k <= (sLen - *i); k++) //add s[i~sLen] to the tail of t
			t[tLen + k] = s[*i + k];
		s[*i] = '\0';
		strcat(s, t);//add t to the tail of s
	}
	printf("%s\n", s);
}