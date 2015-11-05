

#include <iostream>
#include <fstream>
using namespace std;

void mergeSort(int *p, size_t n, int *tmp){

	if (n == 1) return; 

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
	size_t N, i, K;
	int A[SIZE], tmp[SIZE];

	while (!in.eof()){

		in >> N;
		for (size_t i = 0; i < N; i++)
			in >> A[i];

		mergeSort((int *)A, N, (int *)tmp);



		i = N / 2, K = 1;
		while (i>0 && A[i - 1] == A[i--]) K++;
		i = N / 2;
		while (i < N - 1 && A[i++] == A[i + 1]) K++;


		out << "A : ";
		for (size_t i = 0; i < N; i++)
			out << A[i] << " ";

		out << endl << "K = " << K << endl;;

		if (K>N / 2) out << "True";
		else out << "False";
		out << endl;
	}

	in.close();
	out.close();
	

	return 0;
}