#include <iostream>

using namespace std;


void main(){

	int m;
	unsigned long long n;
	cin >> n >> m;

	long long *fibs = new long long[10000000];
	int i = 3;
	fibs[1] = 0;
	fibs[2] = 1;
	fibs[3] = 1;

	do{		
		fibs[i + 1] = (fibs[i - 1] + fibs[i])%m;
		i++;

	} while ((fibs[i - 1] != 1 || fibs[i] != 1) && i<n);
		
	int l = i-3;//Получили длину последовательности остатков, которая повторяется

	cout << fibs[n%l + 1];
	
	/*for (int j = l; j>0; j--)	
		cout << "[" << j << "] = " << fibs[j] << endl;*/
}