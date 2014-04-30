


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>

using namespace std;

//char *strinvert(char *x){
//	int L = strlen(x);														//Длинна без нулевого символа.
//	char *y = (char *)malloc(L + 1);												//Добавляеме разряд для нулевого символа.
//	y = (char *)memset(y, 0, L + 1);
//	for (int i = 0; i < L; i++)														//Пишу без хаков с адресной арифметикой, так как плохо ей владею.
//		y[L - i - 1] = x[i];														//Вычитание единицы, как поправка на начало массива с нуля.
//
//	free(x);
//	return y;
//}

//void invert(char *str){
//	int n = strlen(str);
//	char tmp;
//	for (int i = 0; i < n/2; i++){
//		tmp = str[i];
//		str[i] = str[n - i-1];
//		str[n - i-1] = tmp;
//	}
//	
//}

long long log_factorial(long long n){
	long long s = 0;
	for (long long i = 1; i < n; i++)
		s += (log10(i)) / log10(2);
	return s;
}
long long factorial(long long n){
	return n>1 ? n*factorial(n - 1) : 1;
}

int main(){

	//Объявим строку и запишем в нее "Crocus"


	//printf("%s\n", str);
	//invert(str);
	//printf("%s\n", str);
	//printf("%s\n", str);
	//gets_s(str);
	//printf("%s\n", str);

	//printf("%c\n", *str);


	//Попробуем наконец воспользоваться динамической памятью


	/*char *p;
	for (int i = 1; i < 1000; i++){
	p = (char *)malloc(sizeof(char));
	printf("%i\n", p);
	free(p);
	}*/


	////В качестве кульминации, создадим массив при помощи malloc

	//char str_[7] = "Crocus";
	//char *str = (char *)malloc(sizeof(char)*2);
	//for (int i = 0; i < 7; i++)
	//	str[i] = str_[strlen(str_) - 1 - i];

	////printf("size char = %i\n", sizeof(char));	
	////printf("sizeof int = %i\n", sizeof(int));

	//printf("len str_ = %i\n", strlen(str_));
	//printf("len str = %i\n", strlen(str));
	//
	////printf("sizeof char * = %i\n", sizeof(char *));
	////printf("sizeof str = %i\n", sizeof(str));
	////printf("sezeof size_t = %i\n", sizeof(size_t));
	//	


	/*unsigned int N = 5;
	char *str = (char *)malloc(N);
	str = (char *)memset(str, '1', N-1);
	str[N-1] = '\0';

	char str_[6] = "12345";
	
	
	printf("str = %s\n", str);
	printf("strlen(srt) = %d\n", strlen(str));

	printf("str_ = %s\n", str_);
	printf("strlen(srt_) = %d\n", strlen(str_));*/

	/*char c = '2';
	printf("%d\n", !c);
	return 0;
*/

	/*int N = 5;
	char *x = (char *)malloc(sizeof(char)*N);
	x = (char *)memset(x, 0, N);
	x = strcpy(x, "99");
	x = strinvert(x);*/

	//printf("len of epmty = %i\n", strlen(""));

	/*char *buf = (char *)malloc(10);
	char str[5] = "Hell";

	buf = strncpy(buf, str, strlen(str));*/
	
	
	

	long long n = 100, a = 1, b =1;
	for (long long i = 2; i < n; i += 1){
		a = powl(i, i);
		b = powl(2, powl(2,i));
		cout << "i: " << i << "\t" << a << "\t"<< b << "\t" << a/b << "\t" << endl;
	}
}