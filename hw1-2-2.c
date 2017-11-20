//-------------------------------
// Homework 1 - 2 - 2
// Fibonacci numbers - iterative
//-------------------------------
// f(0) = 0 ; f(1) = 1
// f(i) = f(i-1) + f(i-2), i > 1
//-------------------------------
// belongs to CHinX2 @ 20171030
//-------------------------------
#include <stdio.h>
#include <stdlib.h>

int main()
{
	long long i, ans; //use datatype long long to avoid ans > 2^32-1
	long long i_1, i_2; //to store f(i-1) & f(i-2)
	scanf("%lld", &i); // input the number i for i-th value in Fibonacci numbers
	if (i == 0)ans = 0;
	else if (i == 1)ans = 1;
	else
	{
		int k;
		i_1 = 1; //feb(1) = 1
		i_2 = 0; //feb(0) = 0
		for (k = 2; k <= i; k++) //f(i) = f(i-1) + f(i-2)
		{
			ans = i_1 + i_2;
			i_2 = i_1;
			i_1 = ans;
		}
	}
	printf("Fib(%lld) = %lld\n", i, ans); //answer output
	return 0;
}