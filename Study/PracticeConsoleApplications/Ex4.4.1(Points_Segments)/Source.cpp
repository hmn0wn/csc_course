#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>

using namespace std;

size_t length_(size_t *b, size_t *e){
	return ((size_t)e - (size_t)b) / sizeof(size_t)+1;
}

class Queue_{//Очередь, че. Пишу как представляю.
private:
	struct node{
		size_t *b;
		size_t *e;
		size_t length;
		node *next;
		node *prev;
		node(size_t *begin, size_t *end) :b(begin), e(end), length(length_(b, e)), next(NULL), prev(NULL){}
		ostream &print(ostream &stream){
			stream << "[" << *b << " , " << *e << "]" << "(" << length << ") ";
			return stream;
		}
	};
	
public:
	
	size_t length;
	node *head;
	node *tail;

	Queue_();
	void enqueue(size_t *begin, size_t *end);//В очередь.
	node *dequeue();//Из очереди.
	ostream &print(ostream &stream);
	ostream &operator<<(node *n);
};
Queue_::Queue_():length(0),head(NULL),tail(NULL){}

void Queue_::enqueue(size_t *begin, size_t *end){
	node *tmp = new node(begin, end);
	if (!tail){
		head = tmp;
		tail = tmp;
	}
	else{
		tmp->next = tail;
		tail->prev = tmp;
		tail = tmp;
	}
	length++;
}

Queue_::node *Queue_::dequeue(){
	node *tmp = head;
	if(head && head->prev) head = head->prev;
	return tmp;
}

ostream &Queue_::print(ostream &stream){
	node *iter = tail;
	while (iter){
		//stream << "[" << *iter->b << " : " << *iter->e << "] ";
		iter->print(stream);
		iter = iter->next;
	}
	
	stream << endl;
	iter = head;
	while (iter){
		//stream << "[" << *iter->b << " : " << *iter->e << "]";
		iter->print(stream);
		iter = iter->prev;
	}
	stream << endl;
	return stream;
}

template< typename T >
ostream &print(ostream &stream, T *array_, size_t length){
	for (size_t i = 0; i < length; i++)
		stream << array_[i] << " ";
	
	stream << endl;
	return stream;
}

void merge_sort(size_t *a, size_t *b, size_t length){
	Queue_ merge_queue, merge_queue_borders;
	for (size_t i = 0; i < length; i++){
		merge_queue.enqueue(&a[i], &a[i]);
		
}

int main(){
	ifstream in("input.txt");
	Queue_ myqeue;
	size_t n, m, iter = 0, b,e;

	in >> n >> m;
	size_t *all = new size_t[n * 2 + m];//Тут все, и точки и концы отрезков.
	char *borders = new char[n * 2 + m];//Графические обозначения точек и гнаниц.
	size_t *count = new size_t[n * 2 + m];//Вложенность.
	size_t *points = new size_t[m];//Точки.
	
	for (size_t i = 0; i < n; i++){
		in >> b >> e;
		all[i * 2] = b;
		all[i * 2 + 1] = e;
		myqeue.enqueue(&all[i*2], &all[i*2+1]);
		borders[i * 2] = '[';
		borders[i * 2 + 1] = ']';
	}
	for (size_t i = 0; i < m; i++){
		in >> points[i];
		all[i + 2 * n] = points[i];
		borders[i + 2 * n] = '.';
	}

	cout << "all: ";
	print<size_t>(cout, all, 2 * n + m);
	cout << "borders: ";
	print<char>(cout, borders, 2*n+m);
	myqeue.print(cout);

}



