#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <iostream>

using namespace std;

#define N 10000

int main(int argc, char *argv[])
{
	double s = 0;
	int i;
	omp_set_dynamic(0);

	for (int j = 1; j < 8; j++){
#pragma omp parallel for reduction(+:s) num_threads(j)
		for (i = 0; i < N; i++)
			s = s + 1;

		cout << "sum = " << s << endl;
		s = 0;
	}
	return 0;
}