

#include <iostream>
#include <fstream>
using namespace std;

void mergeSort(size_t *p, size_t n, size_t *tmp){

	if (n == 1) return; //Попробуем сначала так, а после убрав следующий блок.

	if (n == 2){
		if (p[0] > p[1]){
			tmp[0] = p[1];
			p[1] = p[0];
			p[0] = tmp[0];
		}
		return;
	}

	size_t m = n / 2;
	mergeSort(p, m, tmp);
	mergeSort(p + m, n - m, tmp);

	size_t i = 0, j = m;

	for (size_t k = 0; k < n; k++){
		if (i == m) {
			tmp[k] = p[j++]; continue;
		}
		if (j == n){
			tmp[k] = p[i++]; continue;
		}

		if (p[i] < p[j]) tmp[k] = p[i++];
		else tmp[k] = p[j++];
		

	}
	
	for (size_t i = 0; i < n; i++)
		p[i] = tmp[i];
	
}

int main(){

	ifstream in;
	in.open("input.txt", ios::in);
	

	ofstream out("output.txt");
		
	size_t const SIZE = 100000;
	size_t N;
	in >> N;
	int A[SIZE], tmp[SIZE];

	for (size_t i = 0; i < N; i++)
		in >> A[i];
	
	mergeSort((size_t *)A, N, (size_t *)tmp);

	for (size_t i = 0; i < N; i++)
		out << A[i] << endl;

	

	in.close();
	out.close();
	

	return 0;
}