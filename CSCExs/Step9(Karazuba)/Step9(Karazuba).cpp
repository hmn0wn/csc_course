// Step9(Karazuba).cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <stdlib.h>


using namespace std;
//Реализовать умножение длинных чисел алгоритмом Карацубы, задача на метод «Разделяй и властвуй»
//Длина чисел для умножения ограничени 50к символов.

class longn{
private:
	
void strinvert(string *s){
	int L = (*s).size();
	char tmp;
	for (int i = 0; i < L / 2; i++){
		tmp = (*s)[i];
		(*s)[i] = (*s)[L - i - 1];
		(*s)[L - i - 1] = tmp;
	}
}

public:
	vector<long> v;
	longn(string s);
	longn(int n);
	longn();

	void print();
	void invert();
	int length();
	void rshift(int n);

	longn operator+(longn y);
	longn operator-(longn y);
	longn operator*(longn y);
	

	

};

longn::longn(string s){
	strinvert(&s);
	int n = s.length();
	string tmp;
	for (int i = 0; i < n; i += 9){
		tmp = s.substr(i, 9);
		strinvert(&tmp);
		v.push_back(atol(tmp.c_str()));
	}
}
longn::longn(int n){
	v = vector<long>(n,0);
}
longn::longn(){};
void longn::print(){
	
	for (int i = v.size()-1; i>=0; i--){
		for (int j = 0; j < 8 - log10(v[i] != 0 ? v[i] : 1) && i != v.size() - 1; j++) cout << 0;//Вывод с учетом нулей в разрядах.
		cout << v[i] << "";
	}
	cout << endl;
}
void longn::invert(){
	vector<long>::iterator i = v.begin();
	vector<long>::iterator j = v.end();
	long tmp;
	j--;
	while (i < j){
		tmp = *i;
		*(i++) = *j;
		*(j) = tmp;
	}
}
int longn::length(){
	return v.size();
}
void longn::rshift(int n){
	v.insert(v.begin(), n, 0);
}
longn longn::operator+(longn y){
	
	longn x = *this;
	//Будем считать, что числа хранятся задом наперед.
	int n = x.length();
	int m = y.length();
	int l = n > m ? n + 1 : m + 1;
	longn res(l);

	//К большему прибавляем меньшее.
	if (l == 0) return res;
	if (n < m){
		longn tmp = x;
		x = y;
		y = tmp;
		m += n;
		n = m - n;
		m -= n;
	}

	for (int i = 0; i < m; i++){
		res.v[i + 1] = (res.v[i] + x.v[i] + y.v[i]) / 1000000000;
		res.v[i] = (res.v[i] + x.v[i] + y.v[i]) % 1000000000;
	}

	for (int i = m; i < n; i++){
		res.v[i + 1] = (res.v[i] + x.v[i]) / 1000000000;
		res.v[i] = (res.v[i] + x.v[i]) % 1000000000;
	}


//Подчистим нули вконце.
	int i = l-1;
	while (i>0 && (res.v[i] == 0)) {
		res.v.pop_back(); i--;
	}
	return res;
}
longn longn::operator-(longn y){

	longn x = *this;
	//Все еще считаем числа хранимыми задом наперед(по девять разрядов)

	int n = x.length();
	int m = y.length();
	int l = n > m ? n : m;

	longn res(l);// TODO : Возможна утечка памяти
	if (!m)  return x;

	bool credit = 0;

	for (int i = 0; i < m; i++){
		if (x.v[i] - credit >= y.v[i]){
			res.v[i] = x.v[i] - y.v[i] - credit;
			credit = 0;
		}
		else {
			res.v[i] = 1000000000 + x.v[i] - y.v[i] - credit;
			credit = 1;
		}
	}

	for (int i = m; i < n; i++){
		if (x.v[i] - credit >= 0){
			res.v[i] = x.v[i] - credit;
			credit = 0;
		}
		else
			res.v[i] = 1000000000 + x.v[i] - credit;
	}

	//Почистим нули вконце
	int i = l-1;
	while (i>0 && (res.v[i] == 0 || res.v[i] == 0))
	{
		res.v.pop_back(); i--;
	}

	return res;
}

longn longn::operator*(longn y){

	longn x = *this;

	int n = x.length();
	int m = y.length();

	int l = n > m ? n : m;
	int n_ = l / 2;

	//Укорачиваем дерево, производя умножение на нуль сразу.
	if (n == 0 || m == 0 || (n == 1 && x.v[0] == 0) || (m == 0 && y.v[0] == 0)){
		//TODO : Кажется, тут тоже возможна утечка.
		longn res(1);
		return res;
	}

	if (l == 1) {
		longn res;
		long long tmp = (long long)x.v[0] * y.v[0];
		res.v.push_back(tmp % 1000000000);
		if (tmp > 999999999) res.v.push_back(tmp / 1000000000);
		return res;
	}

	

	//Шаманим, короче со старого алгоритма. Рвем, выделяем части.
	int xln = (n > n_) ? n - n_ : 0;
	longn xl(xln);
	for (int i = n - xln; i < n; i++)
		xl.v[i - n + xln] = x.v[i];
	
	int xrn = (n>n_) ? n_ : n;
	longn xr(xrn);
	for (int i = 0; i < xrn; i++)
		xr.v[i] = x.v[i];

	int yln = (m>n_) ? m - n_ : 0;
	longn yl(yln);
	for (int i = m - yln; i < m; i++)
		yl.v[i - m + yln] = y.v[i];

	int yrn = (m>n_) ? n_ : m;
	longn yr(yrn);
	for (int i = 0; i < yrn; i++)
		yr.v[i] = y.v[i];

	//TODO : Тут похоже тоже много памяти отчистить нужно.
	longn p1 = xl*yl;
	longn p2 = xr*yr;
	longn p3 = (xl + xr)*(yl + yr);

	longn p4 = p3 - p1 - p2;

	p1.rshift(2*n_);
	p4.rshift(n_);

	longn res = p1 + p4 + p2;
	return res;	
}

int _tmain(int argc, _TCHAR* argv[])
{
	string input;
	cin >> input;
	longn x = longn(input);
	//x.print();
	
	cin >> input;
	longn y = longn(input);
	//y.print();

	longn z = x * y;
	z.print();
	
	




	return 0;
}

