//-------------------------------
// Homework 1 - 2 - 1
// Fibonacci numbers - recursive
//-------------------------------
// f(0) = 0 ; f(1) = 1
// f(i) = f(i-1) + f(i-2), i > 1
//-------------------------------
// belongs to CHinX2 @ 20171030
//-------------------------------
#include <stdio.h>
#include <stdlib.h>

//===Function List===
long long feb(long long); //Fibonacci recursive function
//===Function List===

long long feb(long long i) //Fibonacci recursive function
{
	//initial addition
	if (i == 0)return 0;
	if (i == 1)return 1;

	return feb(i - 1) + feb(i - 2); //resursive : f(i)=f(i-1)+f(i-2)
}

int main()
{
	long long i,ans; //use datatype long long to avoid ans > 2^32-1
	scanf("%lld", &i); // input the number i for i-th value in Fibonacci numbers
	ans = feb(i);
	printf("Fib(%lld) = %lld\n", i, ans); //answer output
	return 0;
}
