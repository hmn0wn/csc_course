#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

size_t length_(size_t *b, size_t *e){
	return ((size_t)e - (size_t)b) / sizeof(size_t)+1;
}

void print(char label, size_t *A, size_t n){
	cout << label << ": ";
	for (size_t i = 0; i < n; i++)
		cout << A[i] << " ";
	cout << endl;
}

void mergeSort(size_t *b, size_t *e, size_t *tmp, size_t *inv){
	
	

	size_t length = length_(b,e);
	size_t *m = b + length / 2;
	print('x', b, length);
	if (b == e) return;
	
	mergeSort(b, m-1, tmp, inv);
	mergeSort(m, e, tmp, inv);

	size_t *i = b, *j = m, k = 0;
	while (i < m || j < e+1){

		if (i == m) {
			tmp[k++] = *(j++);
			continue;
		}
		if (j == e + 1){
			tmp[k++] = *(i++);
			
			continue;
		}

		if (*i <= *j){
			tmp[k++] = *(i++);
		}
		else{
			tmp[k++] = *(j++);
			(*inv)+=length_(i,m-1);
		}
	}

	for (size_t i = 0; i < length; i++)
		b[i] = tmp[i];

	

}



int main(){
	ifstream in("input.txt");
	
	size_t n, inv = 0;
	in >> n;

	size_t *A = new size_t[n + 1];
	size_t *tmp = new size_t[n + 1];
	size_t *B = new size_t[n + 1];



	for (size_t i = 0; i < n; i++){
		in >> A[i];
		B[i] = A[i];
	}

	
	print('A', A, n);
	mergeSort(B, B + n - 1, tmp, &inv);
	print('B', B, n);
	cout << "inv: " << inv << endl;


	


	

}