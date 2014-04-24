#include <iostream>
#include <fstream>
#include <string.h>
#define SIZE 100000
using namespace std;



class Heap{

private:
	size_t heap[SIZE];//
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

Heap::Heap():length(0){
	for(size_t i = 0; i<SIZE; i++)
		heap[i] = 0;
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


void Heap::inserthead(size_t d){//зачем Я это написал Оо, нельзя добавлять в голову, это все ломает.
	
	for (size_t i = length+1; i > 0; i--)
		heap[i] = heap[i - 1];
	length++;
	heap[1] = d;
}

void Heap::inserttail(size_t d){
	heap[++length] = d;

}

void Heap::swap(size_t i, size_t j){
	size_t tmp = data(j);
	heap[j] = heap[i];
	heap[i] = tmp;
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

void Heap::insert(size_t d){
	inserttail(d);
	siftup(length);
}

size_t Heap::extract(){
	size_t tmp = heap[1];
	heap[1] = heap[length];
	heap[length] = 0;
	length--;
	siftdown(1);
	return(tmp);
}

void Heap::printheap(){
	cout << "___________________________" << endl << "[ ";
	for (size_t i = 1; i <= length; i++)
		cout << heap[i] << " ";
	cout << "]" << endl;
}

size_t Heap::getlength(){
	return length;
}


int main(){
	//ifstream in("input.txt");
	//fstream out("output.txt");
	Heap myheap;
	size_t n, input;
	char flag[10];
	cin >> n;
	for (size_t i = 0; i < n; i++){
		
		cin >> flag;
		if (!strcmp(flag, "Insert")){
			cin >> input; 
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