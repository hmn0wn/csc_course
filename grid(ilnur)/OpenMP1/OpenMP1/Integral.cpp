#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <iostream>

using namespace std;

#define N 100000000

double f(double x){
	return exp(x)/x;
}

int main(int argc, char *argv[])
{
	double total = 0;
	int i;
	int a(1), b(5);
	double h = (double)(b-a)/(double)N;
	omp_set_dynamic(0);
	double wall_timer;

	for(int t = 1; t <= 8; t++){
		total = 0;
		wall_timer = omp_get_wtime();
#pragma omp parallel for private(i) num_threads(t) reduction(+:total)
		for (i = 0; i < N; i++){
			total = total + f(h*(double(i+1)));
		}
		wall_timer = omp_get_wtime() - wall_timer;

		cout << h*total << " | ";

		cout << "time on wall: " << wall_timer << "\n";
	}

	return 0;
}