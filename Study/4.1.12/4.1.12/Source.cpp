#include <iostream>
#include <vector>

using namespace std;

void rec(vector<int> A, int n){
	for (int i = 1; i <= A.size(); i++){
		for (int j = 1; j <= i; j++){
			A[A.size() - j] = A[A.size() - j] + 1;
			if (A[A.size() - j] == n) return;
		}
		for (int j = 0; j < A.size(); j++)
			cout << A[j] << ' ';

		cout << endl;
		rec(A,n);
	}
}

int translate(vector<int> &A, int num, int base){
	if (num > base){ 
		A.push_back(translate(A, num/base, base)); 
		return num % base;
	}
	return num;
}

int main(){
	int n = 0, k = 0, c = 1;

	cin >> n >> k;
	vector<int> ANS;
	ANS.reserve(k + 1);

	bool flag = false;
	do{
		flag = true;
		for (int i = 0; i < ANS.size(); i++)
			for (int j = i + 1; j < ANS.size(); j++)
				if (ANS[i] == ANS[j]) flag = false;

		


		if (flag){
			for (int i = 0; i < k - ANS.size(); i++)
				//cout << 0 << ' ';
				ANS.insert(ANS.begin(), 0);

			for (int j = 0; j < ANS.size(); j++)
				cout << ANS[j] << ' ';

			cout << endl;
		}
		ANS.clear();
		ANS.push_back(translate(ANS, c, n));
		c++;
	}while (ANS.size() <= k);
	return 0;
}