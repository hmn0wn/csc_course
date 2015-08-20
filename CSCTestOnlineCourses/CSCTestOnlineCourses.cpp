// CSCTestOnlineCourses.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;


int _tmain(int argc, _TCHAR* argv[]){
	
		long a, b, c;
		long n, m;
		cin >> n >> m;
		

		a = 0;
		b = 1;

		for (int i = 2; i <= n; i++){
			c = a;
			a = b;
			b = (b + c) % 100000;
			cout << b << endl;
		}
		//cout << b;
		return 0;
}