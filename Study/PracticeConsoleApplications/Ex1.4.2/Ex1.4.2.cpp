// Ex1.4.2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int BinarySearch(int A[],int N, int k){
	int l, r;
	l = 0;
	r = N-1;
	int m;
	while (l<=r){
		m = (l + r) / 2;
		if (A[m] == k) return m;
		else if (A[m] < k) l = m + 1;
		else if (k < A[m]) r = m - 1;

	}
	return -1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int N;
	scanf_s("%i", &N);
	int A[100001];
	for (int i = 0; i < N; i++)
		scanf_s("%i", &A[i]);
	
	int K;
	scanf_s("%i", &K);
	int B[100001];
	for (int i = 0; i < K; i++)
		scanf_s("%i", &B[i]);
	
	
	for (int j = 0; j < K; j++)
		printf("%i ", BinarySearch(A, N, B[j]));

	return 0;
}

//массивы должны начинаться с 0, и время работы необходимо уменьшить.