

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

char *karatsuba(char *x, char *y);
void strinvert(char *x);
char *add(char *x, char *y);
char *diff(char *x, char *y);
char *simplexy(char x, char y);
char *lshift(char *x, size_t n);
char *inttostr(size_t x);



void strinvert(char *x){
	size_t L = strlen(x);		
	char tmp;
	for (size_t i = 0; i < L / 2; i++){
		tmp = x[i];
		x[i] = x[L - i - 1];
		x[L - i - 1] = tmp;
	}
}

char *add(char *x, char *y){
	
	size_t N = strlen(x);													//Длинна без нулевого символа
	size_t M = strlen(y);													
	size_t L = N>M ? N+1 : M+1;											//На один больше, чтобы при сложнеии было где хранить единицу при увеличен разрядности.

	char *z = (char *)malloc(L+1);	
	z = (char *)memset(z, 0, L + 1);

	if (L == 1){
		z[1] = '0';
		return z;
	}
	if (N < M){
		char *tmp = y;
		y=x;
		x = tmp;
		M += N;
		N = M - N;
		M -= N;
	}

	for (size_t i = 0; i < M; i++){
		z[i + 1] = (z[i]+ x[i] + y[i] - 2 * '0') / 10;
		z[i] = (z[i] + x[i] + y[i] - 2 * '0') % 10 + '0';
		
	}

	for (size_t i = M; i < N; i++){
		z[i + 1] = (z[i] + x[i] - '0') / 10;
		z[i] = (z[i] + x[i] - '0') % 10 + '0';
	
	}

	//Почистим нули в конце.
	size_t i = L;
	while (i>0 && (z[i] == '0' || z[i] == 0))
		z[i--] = 0;

	if (z[N]) z[N] += '0';
	
	return z;
}

char *diff(char *x, char *y){															//Первое число априори больше второго, не забудь об этом, блджад!!!
	size_t N = strlen(x);
	size_t M = strlen(y);

	size_t L = N > M ? N : M;
	char *z = (char *)malloc(L + 1);
	z = (char *)memset(z, 0, L + 1);

	if (!M){
		z = strcpy(z, x);
		return z;
	}

	bool credit = 0;
	for (size_t i = 0; i < M; i++){
		if (x[i] - credit >= y[i]){
			z[i] = x[i] - y[i] - credit + '0';
			credit = 0;
		}

		else{
			z[i] = 10 + x[i] - y[i] - credit + '0';
			credit = 1;
		}
	}

	for (size_t i = M; i < N; i++){
		if (x[i] - credit >= '0'){
			z[i] = x[i] - credit;
			credit = 0;
		}
		else
			z[i] = 10 + x[i] - credit;

	}

	//Почистим нули вконце.
	size_t i = L;
	while (i>0 && (z[i] == '0' || z[i] == 0))
		z[i--] = 0;

	return z;
}

char *simplexy(char x, char y){
	if (x == 0) x = '0';
	if (y == 0) y = '0';
	char *z;
	size_t z_ = (x - '0')*(y - '0');
	if (z_>= 10){
		z = (char *)malloc(3);
		z[0] = z_ % 10 + '0';
		z[1] = z_ / 10 + '0';
		z[2] = 0;
	}
	else {
		z = (char *)malloc(2);
		z[0] = z_+'0';
		z[1] = 0;
	}

	return z;
}

char *karatsuba(char *x, char *y){
	size_t N = strlen(x);
	size_t M = strlen(y);

	size_t L = N > M ? N : M;
	size_t n_ = L/2;

	char *tmp, *tmp1, *tmp2; //Для отчистки памяти.
	
	if (L == 1) return simplexy(x[0], y[0]);

	//Укорачиваем дерево, производя умножение на ноль сразу.
	if (N == 0 || M == 0 || (N == 1 && x[0] == '0') || (M == 1 && y[0] == '0')) {
		char *z = (char *)malloc(2);
		z[0] = '0';
		z[1] = 0;
		return z;
	}

	size_t xln = (N > n_) ? N-n_ : 0;	//Индивидуальная длина левоко куска, если числа сильно разнятся по длине.
	char *xl = (char *)malloc(xln+1);
	for (size_t i = N - xln; i<N; i++)
		xl[i - N + xln] = x[i];
	xl[xln] = 0;

	size_t xrn = (N > n_) ? n_ : N;
	char *xr = (char *)malloc(xrn + 1);
	for (size_t i = 0; i<xrn; i++)
		xr[i] = x[i];
	xr[xrn] = 0;
	
	
	size_t yln = (M > n_) ? M - n_ : 0;
	char *yl = (char *)malloc(yln + 1);
	for (size_t i = M - yln; i<M; i++)
		yl[i - M + yln] = y[i];
	yl[yln] = 0;

	size_t yrn = (M > n_) ? n_ : M;
	char *yr = (char *)malloc(yrn + 1);
	for (size_t i = 0; i < yrn; i++)
		yr[i] = y[i];
	yr[yrn] = 0;
	


	char *p1 = (char *)malloc(xln + yln + 2);
	p1 = (char *)memset(p1, 0, xln + yln + 2);
	p1 = karatsuba(xl, yl);

	char *p2 = (char *)malloc(xrn + yln + 2);
	p2 = (char *)memset(p2, 0, xrn + yln + 2);
	p2 = karatsuba(xr, yr);
	
	size_t p3n = (xln > xrn ? xln : xrn) + (yln > yrn ? yln : yrn) + 3;
	char *p3 = (char *)malloc(p3n); //Максимально возможная длина, очевидно же.
	p3 = (char *)memset(p3, 0, p3n);
	tmp = add(xl, xr);
	free(xl);
	free(xr);
	tmp1 = add(yl, yr);
	free(yl);
	free(yr); // UNDONE: Программа валится
	p3 = karatsuba(tmp, tmp1);
	free(tmp);
	free(tmp1);

	char *z = (char *)malloc(N + M + 1);
	z = (char *)memset(z, 0, N + M + 1);

	

	tmp = diff(p3, p1);
	tmp1 = diff(tmp, p2);
	free(tmp);

	tmp = lshift(tmp1, n_);
	free(tmp1);

	tmp1 = lshift(p1, 2 * n_);
	tmp2 = add(tmp1, tmp);
	free(tmp);
	free(tmp1);

	z = add(tmp2, p2);
	free(tmp2); 
	
	


	
	free(p1);
	free(p2);
	free(p3);
	return z;


}

//Рассово верное умножение на основание системы счисления, сдвигом.
char *lshift(char *x, size_t n){
	size_t N = strlen(x);
	char *y = (char *)malloc(N + n + 1);
	y = (char *)memset(y, '0', N + n + 1);
	for (size_t i = 0; i <= N; i++)
		y[i + n] = x[i];
	return y;
}

char *inttostr(size_t x){
	char *y = (char *)malloc(6);
	y = (char *)memset(y, 0, 6);
	size_t i = 0;
	while (x > 0 || i==0){
		y[i] = x % 10+'0';
		x = x / 10;
		i++;
	}
	return y;
}


size_t main()
{

#pragma region Ввод
	/*char input[100001];
	scanf("%s", input);
	size_t N = strlen(input);
	char *x = (char *)malloc(sizeof(char)*N);
	x = (char *)memset(x, 0, N);
	x = strcpy(x, input);
	for (size_t i = 0; i < 10001; i++)
		input[i] = 0;

	scanf("%s", input);
	size_t M = strlen(input);
	char *y = (char *)malloc(sizeof(char)*M);
	y = (char *)memset(y, 0, M);
	y = strcpy(y, input);*/
	
#pragma endregion	

#pragma region Целевое действие.
	size_t N = 1000;
	char *x = (char *)malloc(N + 1);
	x = (char *)memset(x, '1', N);
	x[N] = 0;
	char *y = (char *)malloc(N + 1);
	y = (char *)memset(y, '1', N);
	y[N] = 0;
	
	
	char *z = karatsuba(x, y);
	strinvert(z);
	printf("%s\n", z);
#pragma endregion

	//Тестирование суммы, разности, инверсии и сдвига входных данных.
	/*char *x = (char *)malloc(2);
	x[0] = '0';
	x[1] = 0;
	

	char *y = (char *)malloc(2);
	y[0] = '0';
	y[1] = 0;

	printf("x = %s\n", x);
	printf("y = %s\n", y);
	
	char *z = add(x, y);
	printf("z = x + y = %s\n", z);
	free(z);

	z = (char *)diff(x, y);
	printf("z = x - y = %s\n", z);
	free(z);

	strinvert(x);
	strinvert(y);
	printf("inv x = %s\n", x);
	printf("inv y = %s\n", y);
	strinvert(x);
	strinvert(y);

	z = (char *)rshift(x, 1);
	printf("x rshift 1 = %s\n", z);
	free(z);

	z = (char *)rshift(y, 1);
	printf("y rshift 1 = %s \n", z);
	free(z);*/

	
	//Тестирование простого произведения перебором.
	/*for (size_t i = 0; i < 10; i++){
		for (size_t j = 0; j < 10; j++){
			printf("%d x %d = %s\n",i,j, simplexy(i + '0', j + '0'));

		}
	}*/

	//Тестирование суммы и произведения перебором.
	/*size_t z,z_;
	char *sz, *si, *sj;
	for (size_t i = 2; i < 1000; i++){
		for (size_t j = 14; j < 1000; j++){
			sz = (karatsuba(inttostr(i),inttostr(j)));
			strinvert(sz);
			z = atoi(sz);
			z_ = i*j;
			if(z!=z_)
				printf("%i * %i = %i / %s\n",i,j,z_,sz);
			free(sz);
			
		}
	}
	*/
	
	//Тестирование правого сдвига перебором.
		s = inttostr(i);
		for (size_t j = 0; j < 10; j++){
			s = rshift(s, j);
			printf("%i\t%i\t%s\n", i, j, s);
			//strinvert(s);
			//printf("%i\t%i\t%s\n", i, j, s);
		}
		free(s);
	}*/

	printf("run time = %i\n", clock() );
	return 0;


}

