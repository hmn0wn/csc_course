


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char *strinvert(char *x){
	int L = strlen(x);														//������ ��� �������� �������.
	char *y = (char *)malloc(L + 1);												//���������� ������ ��� �������� �������.
	y = (char *)memset(y, 0, L + 1);
	for (int i = 0; i < L; i++)														//���� ��� ����� � �������� �����������, ��� ��� ����� �� ������.
		y[L - i - 1] = x[i];														//��������� �������, ��� �������� �� ������ ������� � ����.

	free(x);
	return y;
}

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

int main(){

	//������� ������ � ������� � ��� "Crocus"


	//printf("%s\n", str);
	//invert(str);
	//printf("%s\n", str);
	//printf("%s\n", str);
	//gets_s(str);
	//printf("%s\n", str);

	//printf("%c\n", *str);


	//��������� ������� ��������������� ������������ �������


	/*char *p;
	for (int i = 1; i < 1000; i++){
	p = (char *)malloc(sizeof(char));
	printf("%i\n", p);
	free(p);
	}*/


	////� �������� �����������, �������� ������ ��� ������ malloc

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

	char *buf = (char *)malloc(10);
	char str[5] = "Hell";

	buf = strncpy(buf, str, strlen(str));
	
}