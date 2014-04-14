#define RF
#ifdef RF
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

#endif