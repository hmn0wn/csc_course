#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>

using namespace std;

#pragma region Queue_
class Queue_{//Очередь, че. Пишу как представляю.
private:
	struct node{
		int *data;
		char *shadow_data;
		size_t length;
		node *next;
		node *prev;
		node(int *dat, char *sh_dat, size_t len) :data(dat), shadow_data(sh_dat), length(len), next(NULL), prev(NULL){}
		ostream &print_data(ostream &stream){
			stream << "[";
			for (size_t i = 0; i < length-1; i++)
				stream << data[i] << " ";
				
				stream <<data[length-1] <<  "] ";
			return stream;
		}
		ostream &print_shadow_data(ostream &stream){
			stream << "[";
			for (size_t i = 0; i < length - 1; i++)
				stream << shadow_data[i] << " ";

			stream << shadow_data[length - 1] << "] ";
			return stream;
		}
	};
	
public:
	
	size_t length;
	node *head;
	node *tail;

	Queue_();
	void enqueue(int *dat, char *sh_dat, size_t len);//В очередь.
	void dequeue(int **dat, char **sh_dat, size_t &len);//Из очереди.
	ostream &print(ostream &stream);
	ostream &operator<<(node *n);
};
Queue_::Queue_():length(0),head(NULL),tail(NULL){}

void Queue_::enqueue(int *dat, char *sh_dat, size_t len){
	node *tmp = new node(dat, sh_dat, len);
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

void Queue_::dequeue(int **dat, char **sh_dat, size_t &len){
	if (head){
		node *tmp = head;
		*dat = tmp->data;
		*sh_dat = tmp->shadow_data;
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
	node *iter = head;
	stream << "  Q: ";
	while (iter){
		//stream << "[" << *iter->b << " : " << *iter->e << "] ";
		iter->print_data(stream);
		iter = iter->prev;
	}
	stream << endl;
	
	iter = head;
	stream << "S_Q: ";
	while (iter){
		//stream << "[" << *iter->b << " : " << *iter->e << "] ";
		iter->print_shadow_data(stream);
		iter = iter->prev;
	}
	stream << endl;
	stream << endl;
	return stream;
}


#pragma endregion

#pragma region Other

//Напишем вывод массива.
template< typename T >
ostream &print(ostream &stream, char label[10], T *dat, size_t len){
	stream <<label << ": [";
	for (size_t i = 0; i < len - 1; i++)
		stream << dat[i] << " ";

	stream << dat[len - 1] << "]" << endl;
	return stream;
}

//Длина массива по началу и концу.
size_t length_(size_t *b, size_t *e){
	return ((size_t)e - (size_t)b) / sizeof(size_t)+1;
}

#pragma endregion

void merge_sort(int **data, char **shadow_data, size_t length){
	Queue_ merge_queue;

	int *tmp;
	char *sh_tmp;
	for (size_t i = 0; i < length; i++){
		tmp = new int[1];
		sh_tmp = new char[1];
		tmp[0] = (*data)[i];
		sh_tmp[0] = (*shadow_data)[i];
		merge_queue.enqueue(tmp, sh_tmp, 1);
		//merge_queue.print(cout);
	}

	int *dat1, *dat2;
	size_t len1, len2, i, j, k;
	char *sh_dat1, *sh_dat2;

	while (merge_queue.head->prev){
		merge_queue.dequeue(&dat1,&sh_dat1,len1);
		merge_queue.dequeue(&dat2,&sh_dat2,len2);

		
		//print(cout, "   dat1", dat1, len1);
		//print(cout, "sh_dat1", sh_dat1, len1);
		//print(cout, "   dat2", dat2, len2);
		//print(cout, "sh_dat2", sh_dat2, len2);
		
		i = 0;
		j = 0;
		k = 0;
		tmp = new int[len1 + len2];
		sh_tmp = new char[len1 + len2];


		while (i < len1 || j < len2){
			//cout << "i: " << i << endl << "j: "<< j << endl;
			if (i == len1){
				tmp[k] = dat2[j];
				sh_tmp[k++] = sh_dat2[j++];
				continue;
			}
			if (j == len2){
				tmp[k] = dat1[i];
				sh_tmp[k++] = sh_dat1[i++];
				continue;
			}

#pragma region Сортировка двух элементов по двум параметрам, первый из которых имеет два значения, второй три.
			if (dat1[i] < dat2[j]){
				tmp[k] = dat1[i];
				sh_tmp[k++] = sh_dat1[i++];

			}
			else{//Случай равенства по значению.
				if (dat1[i] == dat2[j]){//Точки должны быть внутри отрезков, даже, если они на границе, и плюс стабильность(одинаковые элементы сохраняют порядок следования).
					if (sh_dat1[i] == '{'){
						tmp[k] = dat1[i];
						sh_tmp[k++] = sh_dat1[i++];
					}
					else{
						if (sh_dat2[j] == '{')
						{
							tmp[k] = dat2[j];
							sh_tmp[k++] = sh_dat2[j++];
						}
						else{
							if (sh_dat1[i] == '.'){
								tmp[k] = dat1[i];
								sh_tmp[k++] = sh_dat1[i++];
							}
							else{
								if (sh_dat2[j] == '.'){
									tmp[k] = dat2[j];
									sh_tmp[k++] = sh_dat2[j++];
								}
								else{
									tmp[k] = dat1[i];
									sh_tmp[k++] = sh_dat1[i++];
								}
							}
						}
					}
				}
				else{
					tmp[k] = dat2[j];
					sh_tmp[k++] = sh_dat2[j++];
				}
			}
#pragma endregion
		}


		
		
		//Теперь очистим память массивов с которыми работали, и запишем в очереть новый массив, из них составленный.
		delete(dat1);
		delete(dat2);
		//print(cout, "   tmp", tmp, len1 + len2);
		//print(cout, "sh_tmp", sh_tmp, len1 + len2);
		merge_queue.enqueue(tmp,sh_tmp, len1+len2);
		//merge_queue.print(cout);
	}

	*data = merge_queue.head->data;
	*shadow_data = merge_queue.head->shadow_data;
}

size_t bin_search(int *data, char *shadow_data, size_t length, int point){
	
	size_t begin =0, mid = 0, end = length-1;
	
	while ((data[mid] != point || shadow_data[mid] != '.') && begin<=end)
	{
		length = length / 2;
		mid = begin + length;
		
		//cout << " begin: " << begin << endl;	
		//cout << "   mid: " << mid << endl;
		//cout << "   end: " << end << endl;
		//cout << "length: " << length << endl<<endl;
		

		if (point < data[mid] ) { end = mid; continue; }
		if (data[mid] < point ) { begin = mid + 1; continue; }
		if (shadow_data[mid] == '}') { end = mid; continue; }
		if (shadow_data[mid] == '{') { begin = mid + 1; continue; }
		
	}
	//cout << "  rmid: " << mid << endl;
	return mid;
}



int main(){
	ifstream in("input.txt");
	Queue_ myqeue;
	int b,e;
	size_t n, m;

	in >> n >> m;
	int *all = new int[n * 2 + m];//Тут все, и точки и концы отрезков.
	char *brackets = new char[n * 2 + m];//Графические обозначения точек и гнаниц.
	size_t *count = new size_t[n * 2 + m];//Вложенность.
	int *points = new int[m];//Точки.
	
	for (size_t i = 0; i < n; i++){
		in >> b >> e;
		all[i * 2] = b;
		all[i * 2 + 1] = e;
		
		brackets[i * 2] = '{';
		brackets[i * 2 + 1] = '}';
	}
	for (size_t i = 0; i < m; i++){
		in >> points[i];
		all[i + 2 * n] = points[i];
		brackets[i + 2 * n] = '.';
	}

	
	merge_sort(&all,&brackets, n*2+m);
	//cout << "       i: [";
	//for (size_t i = 0; i < n * 2 + m-1; i++)
		//cout << i << " ";
	//cout <<2*n+m-1 << "]" << endl;
	print(cout, "  points", points, m);
	print(cout, "     all", all, 2 * n + m);
	print(cout, "brackets", brackets, 2 * n + m);
	

	//Теперь подсчитаем вложенность для всех элементов.
	size_t COUNT = 0;
	for (size_t i = 0; i < n * 2 + m; i++)
	if (brackets[i] == '{') count[i] = ++COUNT;
	else if (brackets[i] == '}') count[i] = --COUNT;
	else count[i] = COUNT;

	print(cout, "   count", count, 2 * n + m);
	
	//cout << endl << "p_count: ";
	//Поиск по точкам.(Для начала не бинарный, ибо лень, авось пройдет.)
	for (size_t i = 0; i < m; i++)
		cout << count[bin_search(all, brackets, n * 2 + m, points[i])] << " ";
	
	cout << endl;
	

	


}



