
//Задача одолела контест, но контейнер еще требует множества доработок.
#include <iostream>
#include <fstream>
#include <string.h>
#define SIZE 100001

using namespace std;



class Heap{

private:
	size_t *heap;//
	size_t length;//

public:
	Heap();
	Heap(size_t *arr, size_t len);
	size_t data(size_t i);//
	size_t parent(size_t i);//
	size_t leftc(size_t i);//
	size_t rightc(size_t i);//
	void inserttail(size_t d);//
	void insert(size_t *arr, size_t len);//Позиционирование по правилу кучи.

	void siftup(size_t i);//
	void siftdown(size_t i);//
	void sort();
	void build_heap();

	size_t extract();//	
	ostream &printheap(ostream &stream);
	void swap(size_t i, size_t j);//
};

Heap::Heap():length(0){//Прошло более недели, и у меня возиникает справедливый вопрос: КАКОГО ХУЯ НЕТ КОММЕНТОВ!!!
	//И с какого элемента начало массива? с 1 или с 0???
	//Посмотри на печать, понятно, что с 1, это упрощает позиционирование.)
	//Ублюдок
	//ага :D
	heap = new size_t[100001+1];
	for(size_t i = 0; i<=100001; i++)
		heap[i] = 0;
}

Heap::Heap(size_t *arr, size_t len){
	heap = arr;
	length = len;
}
	
size_t Heap::data(size_t i){
	return heap[i];
}

size_t Heap::parent(size_t i){
	return (i / 2);
}

size_t Heap::leftc(size_t i){
	return (2 * i);
}

size_t Heap::rightc(size_t i){
	return (2 * i + 1);
}

void Heap::inserttail(size_t d){
	heap[++length] = d;

}

void Heap::insert(size_t *arr, size_t len){
	for (size_t i = 1; i <= len; i++)
	heap[i] = arr[i];
	length = len;
}


void Heap::siftup(size_t i){
	size_t pi = parent(i);
	if (!pi) return;
	if (data(pi) < data(i)) {
		swap(i, pi);
		siftup(pi);
	}
}

void Heap::siftdown(size_t i){
	

	size_t li = leftc(i);
	size_t ri = rightc(i);

	//Проверять необходимо не только на правильность подкучи, но и невыход детей за пределы массива.
	if (length == 1) return;

	if (li > length && ri > length) return; //Сразу уваливаем, если сравнивать нечего

	if (li <= length && ri > length)
		if(heap[li] > heap[i]){
			swap(i, li);
			siftdown(li);
		}
		else return;
	
	else
	if (li > length && ri <= length)
		if(heap[ri] > heap[i]){
			swap(i, ri);
			siftdown(ri);
		}
		else return;
	else
	
		if (heap[li] >= heap[ri] && heap[li] > heap[i]){
			swap(i, li);
			siftdown(li);
		}
		else
			if (heap[ri] > heap[li] && heap[ri] > heap[i]){
				swap(i, ri);
				siftdown(ri);
			}

	

}

void Heap::sort(){
	size_t len = length;
	while (length > 1){
		swap(1, length);
		length--;
		siftdown(1);
	}
	length = len;
}

void Heap::build_heap(){
	size_t n = (length % 2) ? length / 2 + 1 : length / 2;
	for (size_t i = n; i >= 1; i--)
		siftdown(i);
}

size_t Heap::extract(){
	size_t tmp = heap[1];
	heap[1] = heap[length];
	heap[length] = 0;
	length--;
	siftdown(1);
	return(tmp);
}

ostream &Heap::printheap(ostream &stream){
	//stream << "___________________________" << endl << "[ ";
	for (size_t i = 1; i <= length; i++)
		stream << heap[i] << " ";
	stream <</* "]" <<*/ endl;
	return stream;
}

void Heap::swap(size_t i, size_t j){
	size_t tmp = data(j);
	heap[j] = heap[i];
	heap[i] = tmp;
}

ostream &operator<<(ostream &stream, Heap h){
	h.printheap(stream);
	return stream;
}


int main(){
	ifstream in("input.txt");
	fstream out("output.txt");	
	size_t n;
	in >> n;
	size_t *input = new size_t[100001 + 1];
	for (size_t i = 1; i <= n; i++)
		in >> input[i];
	

	
	Heap myheap(input,n);
	//myheap.printheap();
	//myheap.build_heap();
	//myheap.printheap();
	//myheap.sort();
	//myheap.printheap(out);
		

	

	for (size_t n = 1; n < 10; n++){
		for (size_t i = 1; i <= n; i++)
			input[i] = (rand() % 100 + 1);

		myheap.insert(input, n);
		cout << myheap;
		myheap.build_heap();
		cout << myheap;
		myheap.sort();
		cout<<myheap << endl;
	}

	
	return 0;
}