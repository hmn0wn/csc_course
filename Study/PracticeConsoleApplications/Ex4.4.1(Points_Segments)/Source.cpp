#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>

using namespace std;

#pragma region Queue_
class Queue_{//Очередь, че. Пишу как представляю.
private:
	struct node{
		size_t *data;
		size_t length;
		node *next;
		node *prev;
		node(size_t *dat, size_t len) :data(dat), length(len), next(NULL), prev(NULL){}
		ostream &print(ostream &stream){
			stream << "[";
			for (size_t i = 0; i < length-1; i++)
				stream << data[i] << ",";
				
				stream <<data[length-1] <<  "] ";
			return stream;
		}
	};
	
public:
	
	size_t length;
	node *head;
	node *tail;

	Queue_();
	void enqueue(size_t *dat, size_t len);//В очередь.
	void dequeue(size_t **dat, size_t &len);//Из очереди.
	ostream &print(ostream &stream);
	ostream &operator<<(node *n);
};
Queue_::Queue_():length(0),head(NULL),tail(NULL){}

void Queue_::enqueue(size_t *dat, size_t len){
	node *tmp = new node(dat, len);
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

void Queue_::dequeue(size_t **dat, size_t &len){
	if (head){
		node *tmp = head;
		*dat = tmp->data;
		len = tmp->length;
		if (head->prev){
			head = head->prev;
			head->next = NULL;
		}
		else {
			head = NULL;
			tail = NULL;
		}
		delete(tmp);
	}
	
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

#pragma region Other

//Напишем вывод массива.
template< typename T >
ostream &print(ostream &stream, T *dat, size_t len){
	stream << "[";
	for (size_t i = 0; i < len - 1; i++)
		stream << dat[i] << ",";

	stream << dat[len - 1] << "]" << endl;
	return stream;
}

//Длина массива по началу и концу.
size_t length_(size_t *b, size_t *e){
	return ((size_t)e - (size_t)b) / sizeof(size_t)+1;
}

#pragma endregion

void merge_sort(size_t *data, size_t length){
	Queue_ merge_queue;

	
	size_t *tmp;
	for (size_t i = 0; i < length; i++){
		tmp = new size_t[1];
		tmp[0] = data[i];
		merge_queue.enqueue(tmp, 1);
		merge_queue.print(cout);
	}

	size_t *dat1, len1, *dat2, len2, i, j, k;

	while (merge_queue.head->prev){
		merge_queue.dequeue(&dat1,len1);
		merge_queue.dequeue(&dat2,len2);

		print(cout, dat1, len1);
		print(cout, dat2, len2);
		
		i = 0;
		j = 0;
		k = 0;
		tmp = new size_t[len1 + len2];

		while (i < len1 || j < len2){
			if (i == len1){
				tmp[k++] = dat2[j++];
				continue;
			}
			if (j == len2){
				tmp[k++] = dat1[i++];
				continue;
			}

			if (dat1[i] <= dat2[j]){
				tmp[k++] = dat1[i++];
			}
			else{
				tmp[k++] = dat2[j++];
			}
		}

		
		
		//Теперь очистим память массивов с которыми работали, и запишем в очереть новый массив, из них составленный.
		delete(dat1);
		delete(dat2);
		print(cout, tmp, len1 + len2);
		merge_queue.enqueue(tmp, len1+len2);
		merge_queue.print(cout);
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
		//myqeue.enqueue(all[i*2], all[i*2+1]);
		borders[i * 2] = '[';
		borders[i * 2 + 1] = ']';
	}
	for (size_t i = 0; i < m; i++){
		in >> points[i];
		all[i + 2 * n] = points[i];
		borders[i + 2 * n] = '.';
	}

	merge_sort(all, n*2+m);

}



