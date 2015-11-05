
//Задача одолела контест, но контейнер еще требует множества доработок.
#include <iostream>
#include <fstream>
#include <string.h>
#define SIZE 100000

using namespace std;


template <size_t size = 100000>
class Heap{

private:
	size_t heap[size];//
	size_t length;//

public:
	Heap();
	void siftup(size_t i);//
	void siftdown(size_t i);//
	void swap(size_t i, size_t j);//
	size_t extract();//
	void insert(size_t d);//
	void inserthead(size_t d);//
	void inserttail(size_t d);//
	void del(size_t i);
	void printheap();
	size_t getlength();

	size_t data(size_t i);//
	size_t parent(size_t i);//
	size_t leftc(size_t i);//
	size_t rightc(size_t i);//
	
};

template <size_t size>
Heap<size>::Heap():length(0){
	for (size_t i = 0; i<size; i++)
		heap[i] = 0;
}
template <size_t size>
size_t Heap<size>::data(size_t i){
	return heap[i];
}
template <size_t size>
size_t Heap<size>::parent(size_t i){
	return (i / 2);
}
template <size_t size>
size_t Heap<size>::leftc(size_t i){
	return (2 * i);
}

template <size_t size>
size_t Heap<size>::rightc(size_t i){
	return (2 * i + 1);
}

template <size_t size>
void Heap<size>::inserthead(size_t d){//зачем Я это написал Оо, нельзя добавлять в голову, это все ломает.
	
	for (size_t i = length+1; i > 0; i--)
		heap[i] = heap[i - 1];
	length++;
	heap[1] = d;
}
template <size_t size>
void Heap<size>::inserttail(size_t d){
	heap[++length] = d;

}
template <size_t size>
void Heap<size>::swap(size_t i, size_t j){
	size_t tmp = data(j);
	heap[j] = heap[i];
	heap[i] = tmp;
}

template <size_t size>
void Heap<size>::siftup(size_t i){
	size_t pi = parent(i);
	if (!pi) return;
	if (data(pi) < data(i)) {
		swap(i, pi);
		siftup(pi);
	}
}
template <size_t size>
void Heap<size>::siftdown(size_t i){
	size_t li = leftc(i);
	size_t ri = rightc(i);

	if (length == 1) return;
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
template <size_t size>
void Heap<size>::insert(size_t d){
	inserttail(d);
	siftup(length);
}
template <size_t size>
size_t Heap<size>::extract(){
	size_t tmp = heap[1];
	heap[1] = heap[length];
	heap[length] = 0;
	length--;
	siftdown(1);
	return(tmp);
}
template <size_t size>
void Heap<size>::printheap(){
	cout << "___________________________" << endl << "[ ";
	for (size_t i = 1; i <= length; i++)
		cout << heap[i] << " ";
	cout << "]" << endl;
}
template <size_t size>
size_t Heap<size>::getlength(){
	return length;
}


int main(){
	ifstream in("input.txt");
	fstream out("output.txt");
	Heap<SIZE> myheap;
	size_t n, input;
	char flag[10];
	in >> n;
	for (size_t i = 0; i < n; i++){
		
		in >> flag;
		if (!strcmp(flag, "Insert")){
			in >> input; 
			myheap.insert(input);
		}
		else cout << myheap.extract() << endl;
	}
	

	/*for (size_t i = 0; i < 100; i++)
		myheap.insert(rand()%100 + 1);

	for (size_t i = 0; i < myheap.getlength(); i++)
		cout << myheap.extract() << endl;*/
	
	
	return 0;
}