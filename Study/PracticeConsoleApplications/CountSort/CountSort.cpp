// CountSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int N = 0;
	int x = 0;
	int count_table[11];

	for (int i = 0; i <= 10; i++)
		count_table[i] = 0;

	scanf_s("%i", &N);

	for (int i = 0; i < N; i++){
		scanf_s("%i", &x);
		count_table[x]++;
	}
		
	for (int i = 0; i <= 10; i++){
		for (int j = 0; j < count_table[i]; j++)
			printf("%i ", i);
	}

	return 0;
}
