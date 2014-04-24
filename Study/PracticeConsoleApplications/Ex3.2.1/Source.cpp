#include <iostream>
//Реализация кучи через список, двоичное дерево общего вида.


class Heap{
	
private:
	struct node{
		int data;
		node *parent;
		node *leftc;
		node *rightc;

		node() :data(0), parent(NULL), leftc(NULL), rightc(NULL){};
		node(int d, node *p, node *l, node *r) :data(d), parent(p), leftc(l), rightc(r){};
	};
	node *head;



public:
	Heap();//
	~Heap();//
	
	void siftup(int d);
	void siftdown(node *n);
	void insert(int d);
	void extract();
	void delall(node *n);//
	void insertleft(int d);

	

};



Heap::Heap() :head(NULL){};
Heap::~Heap(){
	delall(head);
}

void Heap::delall(node *n){
	if (n){
		if (n->leftc) delall(n->leftc);
		if (n->rightc) delall(n->rightc);
		delete n;
	}
}

void Heap::insertleft(int d){
	if (!head){
		head = new node(d, NULL, NULL, NULL);
	}
	else
	{
		node *tmp = head;
		while (tmp->leftc)
			tmp = tmp->leftc;
		tmp->leftc = new node(d, tmp, NULL, NULL);
	}
}

void Heap::siftdown(node *n){
	
}

int main(){

	Heap myheap;
	for (int i = 0; i < 5; i++)
		myheap.insertleft(i);

	
	return 0;
}