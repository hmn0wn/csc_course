// PracticeConsoleApplications.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int foo(int n, int a, int b){
	if (n <= 0)
		return 1;
	else
		return (foo(n - 1, a, b) + a * foo(n / 2, a, b) + b);
}
int ex2(){
	printf("foo(7,1,1) = %d\n", foo(7, 1, 1));
	return 0;
}

void f(int a, int b, int c){
	if (a + c >= b){
		if (a + b <= c) printf("%d\n", a);
	}
	else if (a / 2 < c) {
		printf("%d\n", b);
	}
	else {
		printf("%d\n", c);
	}
}
void ex1(){
	f(6, 3, 2);
}


int _tmain(int argc, _TCHAR* argv[])
{
	ex1();
	ex2();
	return 0;
}

