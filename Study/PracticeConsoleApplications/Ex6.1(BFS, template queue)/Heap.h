
//Задача одолела контест, но контейнер еще требует множества доработок.
#include <iostream>
#include <fstream>
#include <string.h>
#define SIZE 100000

using namespace std;



class Heap{

private:	
	struct node{
		size_t *key;
		size_t data;
		node(size_t *k, size_t d) : key(k), data(d){}
		node() :key(0), data(0){}
	};

	node **heap;//
	size_t max_length;

public:
	size_t length;

	Heap(size_t size);
	size_t data(size_t i);//
	size_t key(size_t i);
	size_t parent(size_t i);//
	size_t leftc(size_t i);//
	size_t rightc(size_t i);//

	
	void siftup(size_t i);//
	void siftdown(size_t i);//
	void swap(size_t i, size_t j);//	
	void inserttail(size_t *k, size_t d);//
	void insert(size_t *k, size_t d);//
	size_t search(size_t *k, size_t d);
	void changepriority(size_t *k, size_t v);
	size_t extractmin();//
	void del(size_t i);
	void printheap();
	

	

};

Heap::Heap(size_t size) :length(0){
	max_length = size;
	//Так, мы создаем кучу на заранее известное колличество мест, 
	//вставка не подразумевает создание новых объектов, только заполнение
	//изначально созданных.

	for (size_t i = 0; i<size; i++)
		heap[i] = new node();
}

size_t Heap::data(size_t i){
	return heap[i]->data;
}

size_t Heap::key(size_t i){
	return heap[i]->key;
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


void Heap::siftup(size_t i){
	size_t pi = parent(i);
	if (!pi) return;
	if (key(pi) < key(i)) {
		swap(i, pi);
		siftup(pi);
	}
}

void Heap::siftdown(size_t i){
	size_t li = leftc(i);
	size_t ri = rightc(i);

	if (length == 1) return;
	if (key(li) <= key(ri) && key(li) < key(i)){
		swap(i, li);
		siftdown(li);
	}
	else
	if (key(ri) < key(li) && key(ri) < key(i)){
		swap(i, ri);
		siftdown(ri);
	}
}

void Heap::swap(size_t i, size_t j){
	node *tmp = heap[i];
	heap[i] = heap[j];
	heap[j] = tmp;


	/*size_t tmp = data(j);
	heap[j] = heap[i];
	heap[i] = tmp;*/
}

void Heap::inserttail(size_t *k, size_t d){
	heap[length]->key = k;
	heap[++length]->data = d;

}

void Heap::insert(size_t *k, size_t d){
	if (length == max_length){
		cout << endl << "!!!HEAP OVERFLOW!!!" << endl;
		return;
	}
	inserttail(k, d);
	siftup(length);
}

/*size_t Heap::search(size_t *k, size_t d, size_t begin){
	
	
}*/

void Heap::changepriority(size_t *k, size_t v){
	size_t i = 1, li, ri;
	while (i <= length){
		li = leftc(i);
		ri = rightc(i);
		if (heap[i]<heap[li])
	}
}

size_t Heap::extractmin(){
	node *tmp = heap[1];
	heap[1] = heap[length];
	heap[length]->data = 0;
	heap[length]->key = 0;
	length--;
	siftdown(1);
	return(tmp->data);
}

void Heap::printheap(){
	cout << "___________________________" << endl << "[ ";
	for (size_t i = 1; i <= length; i++)
		cout << heap[i]->key << " : " << heap[i]->data << " ";
	cout << "]" << endl;
}



/*
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


	for (size_t i = 0; i < 100; i++)
	myheap.insert(rand()%100 + 1);

	for (size_t i = 0; i < myheap.getlength(); i++)
	cout << myheap.extract() << endl;


	return 0;
}*/