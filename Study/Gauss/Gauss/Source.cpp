#include <iostream>
#include <fstream>
#include <math.h>
#include <string>


using namespace std;

void printm(double** matrix, int n, int m){
	cout << endl;
	for (int i = 0; i < n; i++){		
		for (int j = 0; j < m+1; j++){
			cout << ((fabs(matrix[i][j]) < 0.00000001) ? fabs(matrix[i][j]) : matrix[i][j]) << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void swap_(double &from, double &to){
	double tmp = from;
	from = to;
	to = tmp;
}

void exchange_row(double **matrix, int n, int m, int from, int to){	
	for (int j = 0; j < m + 1; j++){		
		swap_(matrix[from][j], matrix[to][j]);
	}
	//cout << "exchange_row: " << from << " and " << to << endl;
	//printm(matrix, n, m);
	
}

void exchange_col(double **matrix, int n, int m, int from, int to){
	for (int i = 0; i < n; i++){
		swap_(matrix[i][from], matrix[i][to]);
	}
	//cout << "exchange_col: " << from << " and " << to << endl;
	//printm(matrix, n, m);

}

void norm(double *row, int m, int positiony){
	//cout << "Norm: " << "?" << " " << positiony << endl;
	if (row[positiony] == 0) {
		//cout << "ZeroDiv\n\n";
		return;
	}
	double tmp = row[positiony];
	for (int j = 0; j < m + 1; j++){
		row[j] /= tmp;
		
		
	}
	
	

}

void matrix_vertical_inverse(double **matrix, int n, int m){
	for (int i = 0; i < n / 2; i++){
		exchange_row(matrix, n, m, i, n - 1 - i);
	}
}

void matrix_horizontal_inverse(double **matrix, int n, int m){
	for (int j = 0; j < (m-1) / 2; j++){
		exchange_col(matrix, n, m, j, m-1 - j);
	}
}

string kron_kop(double **matrix, int n, int m){
	int rank = 0;
	int ext_rank = 0;
	int end = (n > m) ? m : n;
	for (int i = 0; i < end; i++)
		if (fabs(matrix[i][i]) > 0.000001) rank++;
		else if (fabs(matrix[i][m])> 0.000001) ext_rank = 1;

	//ѕроблема, если ранг матрицы ј посчитать было просто, то ранг расширенной сложнее
	//у нас остаетс€ последний столбец, и его обрабатывать следует чуть иначе, нежели столбцы матрицы переменных
	//ѕоэтому, € сделаю обратный проход, но исключа€ нулевые позиции главной диагонали
	
	for (int i = end; i < n; i++)
		if (fabs(matrix[i][m])> 0.000001){ ext_rank = 1; break; }
	ext_rank += rank;

	//return to_string(rank) + " " + to_string(ext_rank);

	if (rank != ext_rank)  return "NO";

	else 
		if (rank < m) return "INF";
		else if (m = 0) return "NO";
			else return "YES";

}

void elimination(double **matrix, int n, int m){
	//ѕр€мой проход метода гаусса
	
	int positionx = 0, positiony = 0;//Ќачнем с левого верхнего угла
	while ((positiony < m) && (positionx<n)){
		//Ќаходим в столбце positiony ненулевой элемент и мен€ем эту строку с той на которой мы стоим
		for (int i = positionx;;){
			if (matrix[i][positiony] == 0) i++;
			else {
				exchange_row(matrix, n, m, positionx, i);//Ќашли ненулевой, мен€ем
				break;//¬ыходим из цикла
			};
			if (i == n) {//≈сли найти не можем, то выходим
				positiony++;
				break;
			}
		}

		//Ќормируем строку, которую вычетать будем из всех остальных
		//ƒелаем это относительно positiony в ней
		norm(matrix[positionx], m, positiony);
		//printm(matrix, n, m);

		//“еперь отнимем от всех остальных(нормиру€ их), что лежат ниже positionx эту строку 
		//умножив ее на соотв элемент в каждой строке под номером positiony
		//cout << "Work with: " << positionx << " " << positiony << endl;
		for (int i = positionx + 1; i < n; i++){
			if (matrix[i][positiony] == 0) continue;//„тобы из нулей не вычетать
			norm(matrix[i], m, positiony);
			//printm(matrix, n, m);
			for (int j = positiony; j < m + 1; j++){

				matrix[i][j] -= matrix[positionx][j];
			}
		}
		//cout << "Goal: " << endl;
		//printm(matrix, n, m);
		positionx++;//ѕереходим к следующей строке, ибо раз мы дошли до этой точки кода, то с текущей строкой все операции кончены
		positiony++;//ѕереходим к следующей переменной

		//cout << "___________________________" << endl << endl;
	}

}

void reverse_elimination(double **matrix, int n, int m){//type=0 если проход пр€мой. type=1 если проход обратный.
	//ѕр€мой проход метода гаусса

	//printm(matrix, n, m);
	//cout << "vert:" << endl;
	matrix_vertical_inverse(matrix, n, m);
	//cout << "hor:" << endl;
	matrix_horizontal_inverse(matrix, n, m);

	int positionx = 0, positiony = 0;//—двигаемс€
	if (n < m) positionx = m - n;
	if (n > m) positiony = n - m;


	while ((positiony < m) && (positionx<n)){
		if (fabs(matrix[positionx][positiony]) > 0.0000001){

			//Ќормируем строку, которую вычетать будем из всех остальных
			//ƒелаем это относительно positiony в ней
			norm(matrix[positionx], m, positiony);
			//printm(matrix, n, m);

			//“еперь отнимем от всех остальных(нормиру€ их), что лежат ниже positionx эту строку 
			//умножив ее на соотв элемент в каждой строке под номером positiony
			//cout << "Work with: " << positionx << " " << positiony << endl;
			for (int i = positionx + 1; i < n; i++){
				if (matrix[i][positiony] == 0) continue;//„тобы из нулей не вычетать
				norm(matrix[i], m, positiony);
				//printm(matrix, n, m);
				for (int j = positiony; j < m + 1; j++)
					matrix[i][j] -= matrix[positionx][j];
			}
			
			//cout << "Goal: " << endl;
			//printm(matrix, n, m);
		}
		positionx++;//ѕереходим к следующей строке, ибо раз мы дошли до этой точки кода, то с текущей строкой все операции кончены
		positiony++;//ѕереходим к следующей переменной

		//cout << "___________________________" << endl << endl;
	}
	//printm(matrix, n, m);
	//cout << "vert:" << endl;
	matrix_vertical_inverse(matrix, n, m);
	//cout << "hor:" << endl;
	matrix_horizontal_inverse(matrix, n, m);
	//printm(matrix, n, m);
}


void main(){
	ifstream in("in.txt");
	int n, m;//n-колличество уравнений, m-колличество неизвестных
	in >> n >> m;

	if (n == 0||m==0){
		cout << "NO" << endl; //≈сли уравнений нет, то независимо от колличества неизвестных, решени€ не будет.
		return;
	}

	double **matrix = new double*[n];
	
	for (int i = 0; i < n; i++){
		matrix[i] = new double[m + 1];
		for (int j = 0; j < m+1; j++){
			in >> matrix[i][j];
		}
	}
	//printm(matrix, n, m);
	
	elimination(matrix, n, m);
	printm(matrix, n, m);
	//cout << "___________________________" << endl << endl; 
	//cout << "___________________________" << endl << endl;
	reverse_elimination(matrix, n, m);
	//cout << "___________________________" << endl;
	//cout << "___________________________" << endl;
	//cout << "result of solution existing = " << kron_kop(matrix, n, m) << endl;
	
	string answer = kron_kop(matrix, n, m);
	cout << answer << endl;
	if (answer == "YES"){
		for (int i = 0; i < m; i++)
			cout << ((fabs(matrix[i][m]) < 0.00000001) ? fabs(matrix[i][m]) : matrix[i][m]) << " ";
		cout << endl;		
	}




	

}