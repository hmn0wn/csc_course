#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
// Оценим сверху степенью двойки
#define SIZE 131072

using namespace std;


class segment_tree{
private:
	int *base_array = new int[131072];	
	int *tree_array = new int[2 * 131072 - 1];

public:
	size_t length_base_array;
	//
	size_t log2_length_base_array;
	size_t length_tree_array;
	
	segment_tree();
	segment_tree(int *array_, size_t n);
	
	void buildtree();//
	int Min(size_t L, size_t R);
	int Min_of_tree_segment(size_t L, size_t R);
	void Set(size_t I, int X);

	//Нормализуем, приводим к правильному виду, дерево начиная с положения I согласно абсолютной нумерации дерева, и заканчивая положением 1.
	void normalize(size_t I);//
	size_t pows_t(size_t x, size_t y);

	ostream &print_base_array(ostream &stream);
	ostream &print_tree_array(ostream &stream);
	
};

segment_tree::segment_tree() :length_base_array(0), log2_length_base_array(0), length_tree_array(0){};

segment_tree::segment_tree(int *array_, size_t n){
	for (size_t i = 0; i < n; i++)
		base_array[i] = array_[i];
	length_base_array = n;
	buildtree();
}

void segment_tree::buildtree(){
	//Приводим длину массива к степени двойки.
	log2_length_base_array = (size_t)log2(length_base_array);
	size_t new_length_base_array = pows_t(2, log2_length_base_array);
	
	
	if (new_length_base_array < length_base_array) {
		new_length_base_array *= 2;
		log2_length_base_array++;
	}
	
	//Заполняем доп. ячейки максимальным зничением int.
	for (size_t i = length_base_array; i < new_length_base_array; i++)
		base_array[i] = 2147483647;

	length_base_array = new_length_base_array;

	//Вычисляем длину массива-дерева(геометрическая прогрессия от степеней двойки в степени высоты).
	length_tree_array = pows_t(2, log2_length_base_array+1) - 1;
	//Временно.
	for (size_t i = 0; i < length_tree_array; i++)
		tree_array[i] = 0;
	//Заполняем листья(!!!ВАЖНО: массив-дерево пронумерован не с 1, а с 0).
	for (size_t i = 0; i < length_base_array; i++)
		tree_array[length_tree_array - length_base_array + i] = base_array[i];

	//Нормализуем дерево проходя по уровням.
	for (size_t j = log2_length_base_array; j>0; j--){
		size_t end = pows_t(2, j + 1) - 1;
		for (size_t i = pows_t(2, j) - 1; i < end; i += 2)
			tree_array[i / 2] = tree_array[i] < tree_array[i + 1] ? tree_array[i] : tree_array[i + 1];
	}

}

int segment_tree::Min(size_t L, size_t R){
	//-____-', быдлокод дофига.

	size_t length = R - L + 1;
	//Сразу обработали частный случай.
	if (length == 1) return base_array[R - 1];

	size_t log2_length = (size_t)log2(length);
	size_t level = log2_length_base_array - log2_length;
	 
	size_t pow2_length = pows_t(2, log2_length);
	//size_t pow2_L = pows_t(2, (size_t)log2(L));
	//size_t pow2_R = pows_t(2, (size_t)log2(R));

	if (length == pow2_length && !(R%pow2_length) ) return Min_of_tree_segment(L, R);

	//Локальное позиционирование
	size_t inside_point = length_base_array/2;
	size_t i = 2;
	while (inside_point < L || inside_point >= R){
		if(inside_point < L) inside_point += length_base_array / pows_t(2,i++);
		if (inside_point >= R) inside_point -= length_base_array / pows_t(2, i++);
	}
	
	
	int MIN = 2147483647;
	//Хаха, костыль, если отрезок из двух чисел и делить его уже не удается, то фигачим тупое сравнение.
	//if (length == 2 && (L != pow2_L || R != pow2_R)) return base_array[L + 1] < base_array[R + 1] ? base_array[L + 1] : base_array[R + 1];
	
	
	int tmp = Min(L, inside_point);
	if (tmp < MIN) MIN = tmp;

	tmp = Min(inside_point+1, R);
	if (tmp < MIN) MIN = tmp;
	return MIN;
}

int segment_tree::Min_of_tree_segment(size_t L, size_t R){
	//Границы используются умозрительные, сдвинуты относительно позиций массива на одну ячейку.
	//Коряво написано, но работает.
	size_t length = R - L + 1;
	size_t level = log2_length_base_array - (size_t)log2(length);
	size_t level_position = (size_t)R / (length) - 1;
	size_t abs_position = pows_t(2, level) - 1 + level_position;
	
	return tree_array[abs_position];
}

void segment_tree::Set(size_t I, int X){
	base_array[I - 1] = X;
	//Вставим в дерево.
	tree_array[length_tree_array - length_base_array + I-1] = X;
	normalize(length_tree_array - length_base_array + I-1);

}

void segment_tree::normalize(size_t I){
	size_t neighbour = (I % 2) ? I + 1 : I - 1;
	size_t parent = (I+1) / 2-1;//Начало позиционирования с нуля, поэтому и прибавляем единицу.
	int last_tree_array_parent_value = tree_array[parent];
	
	tree_array[parent] = (tree_array[I] < tree_array[neighbour]) ? tree_array[I] : tree_array[neighbour];
	if(tree_array[parent]!= last_tree_array_parent_value) normalize(parent);
	
	
}

size_t segment_tree::pows_t(size_t x, size_t y){
	size_t tmp = 1;
	while ((y--)>0)
		tmp *= x;
	return tmp;
}

ostream &segment_tree::print_base_array(ostream &stream){
	stream << "base_array: ";
	for (size_t i = 0; i < length_base_array; i++)
		stream << base_array[i] << " ";
	stream << endl;
	return stream;
}

ostream &segment_tree::print_tree_array(ostream &stream){
	stream << "length_tree_array: " << length_tree_array << endl;
	stream << "tree_array: " << endl;
	size_t end;
	for (size_t j = 0; j <= log2_length_base_array; j++){
		/*for (size_t i = (log2_length_base_array - j); i>0; i--)
			stream << "\t";*/

		end = pows_t(2, j + 1) - 1;
		for (size_t i = pows_t(2,j)-1; i < end; i++)
			stream << tree_array[i] << "\t";
		stream << endl;
		}
	stream << endl;
	return stream;
}


ostream &operator<<(ostream &stream, segment_tree s_tree){
	s_tree.print_base_array(stream);
	s_tree.print_tree_array(stream);
	return stream;
}


int main(){
	int *b_array = new int[131072];
	size_t n, m;
	/*ifstream in("input.txt");
	in >> n >> m;
	for (size_t i = 0; i < n; i++)
		in >> b_array[i];

	segment_tree s_tree(b_array, n);
	cout << s_tree << endl;

	s_tree.Set(3, 10);
	cout << s_tree << endl;
	for (size_t i = 1; i < s_tree.length_base_array; i++)
	for (size_t j = 1; j <= i; j++)
		cout <<"Min( "<< j << "," << i << "): "<< s_tree.Min(j,i) << endl;

	//cout << "Min( " << 3 << "," << 6 << "): " << s_tree.Min(3, 6) << endl;
	in.close();*/

	cin >> n >> m;
	for (size_t i = 0; i < n; i++)
		cin >> b_array[i];

	segment_tree s_tree(b_array, n);
	
	size_t I,L,R;
	int X;
	int *answers = new int[100000];
	size_t iter = 0;
	char command[4];
	for (size_t i = 0; i < m; i++){
		cin >> command;
		if (!strcmp(command, "Set")){
			cin >> I;
			cin >> X;
			s_tree.Set(I, X);
		}
		else{
			cin >> L;
			cin >> R;
			answers[iter++] = s_tree.Min(L, R);
		}
	}

	for (size_t i = 0; i < iter; i++)
		cout << answers[i] << endl;
	
}