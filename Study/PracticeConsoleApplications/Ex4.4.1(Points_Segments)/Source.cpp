#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>

using namespace std;

size_t length_(size_t *b, size_t *e){
	return ((size_t)e - (size_t)b) / sizeof(size_t)+1;
}

template< typename T >
ostream &print(ostream &stream, T *array_, size_t length){
	for (size_t i = 0; i < length; i++)
		stream << array_[i] << " ";

	stream << endl;
	return stream;
}

#pragma region Queue_
class Queue_{//Очередь, че. Пишу как представляю.
private:
	struct node{
		size_t b;
		size_t e;
		size_t length;
		node *next;
		node *prev;
		node(size_t begin, size_t end) :b(begin), e(end), length(e-b+1), next(NULL), prev(NULL){}
		ostream &print(ostream &stream){
			stream << "[" << b << ".." << length << ".." << e << "] ";
			return stream;
		}
	};
	
public:
	
	size_t length;
	node *head;
	node *tail;

	Queue_();
	void enqueue(size_t begin, size_t end);//В очередь.
	void dequeue(size_t &begin, size_t &end);//Из очереди.
	ostream &print(ostream &stream);
	ostream &operator<<(node *n);
};
Queue_::Queue_():length(0),head(NULL),tail(NULL){}

void Queue_::enqueue(size_t begin, size_t end){
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

void Queue_::dequeue(size_t &begin, size_t &end){
	node *tmp = head;
	if(head && head->prev) head = head->prev;
	begin = tmp->b;
	end = tmp->e;
	delete(tmp);

}

ostream &Queue_::print(ostream &stream){
	node *iter = tail;
	while (iter){
		//stream << "[" << *iter->b << " : " << *iter->e << "] ";
		iter->print(stream);
		iter = iter->next;
	}
	
	stream << endl;
	stream << endl;
	return stream;
}


#pragma endregion

void merge_sort(size_t *a, char *b, size_t length){
	Queue_ merge_queue;
	size_t *tmpa = new size_t[length];
	char *tmpb = new char[length];
	for (size_t i = 0; i < length; i++)
		merge_queue.enqueue(i, i);

	size_t begin1, end1, begin2, end2, i, j, k;
	while (merge_queue.head){
		merge_queue.dequeue(begin1,end1);
		merge_queue.dequeue(begin2, end2);
		
		i = begin1;
		j = begin2;
		k = 0;
		
		while (i <= end1 || j <= end2){
			if (i > end1){
				tmpa[k] = a[j];
				tmpb[k++] = b[j++];
				continue;
			}
			if (j > end2){
				tmpa[k] = a[i];
				tmpb[k++] = b[i++];
				continue;
			}

			if (a[i] <= a[j]){
				tmpa[k] = a[i];
				tmpb[k++] = b[i++];

			}

			for (size_t i = begin1; i < (end1 - begin1 + 1) + (end2 - begin2 + 1); i++){
				a[i] = tmpa[i];
				b[i] = tmpb[i];
			}

			//Теперь добавим в очереть новый, объединенный массив.
			merge_queue.enqueue(begin1, end2);
			
		}

	}
	
	
		
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
		myqeue.enqueue(all[i*2], all[i*2+1]);
		borders[i * 2] = '[';
		borders[i * 2 + 1] = ']';
	}
	for (size_t i = 0; i < m; i++){
		in >> points[i];
		all[i + 2 * n] = points[i];
		borders[i + 2 * n] = '.';
	}

	merge_sort(all, borders, n*2+m);

}



