#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>

using namespace std;

#pragma region Queue_
class Queue_{//�������, ��. ���� ��� �����������.
private:
	struct node{
		size_t *data;
		char *shadow_data;
		size_t length;
		node *next;
		node *prev;
		node(size_t *dat, char *sh_dat, size_t len) :data(dat), shadow_data(sh_dat), length(len), next(NULL), prev(NULL){}
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
	void enqueue(size_t *dat, char *sh_dat, size_t len);//� �������.
	void dequeue(size_t **dat, char **sh_dat, size_t &len);//�� �������.
	ostream &print(ostream &stream);
	ostream &operator<<(node *n);
};
Queue_::Queue_():length(0),head(NULL),tail(NULL){}

void Queue_::enqueue(size_t *dat, char *sh_dat, size_t len){
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

void Queue_::dequeue(size_t **dat, char **sh_dat, size_t &len){
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
	node *iter = tail;
	stream << "  Q: ";
	while (iter){
		//stream << "[" << *iter->b << " : " << *iter->e << "] ";
		iter->print_data(stream);
		iter = iter->next;
	}
	stream << endl;
	
	iter = tail;
	stream << "S_Q: ";
	while (iter){
		//stream << "[" << *iter->b << " : " << *iter->e << "] ";
		iter->print_shadow_data(stream);
		iter = iter->next;
	}
	stream << endl;
	stream << endl;
	return stream;
}


#pragma endregion

#pragma region Other

//������� ����� �������.
template< typename T >
ostream &print(ostream &stream, char label[10], T *dat, size_t len){
	stream <<label << ": [";
	for (size_t i = 0; i < len - 1; i++)
		stream << dat[i] << " ";

	stream << dat[len - 1] << "]" << endl;
	return stream;
}

//����� ������� �� ������ � �����.
size_t length_(size_t *b, size_t *e){
	return ((size_t)e - (size_t)b) / sizeof(size_t)+1;
}

#pragma endregion

void merge_sort(size_t *data, char *shadow_data, size_t length){
	Queue_ merge_queue;

	size_t *tmp;
	char *sh_tmp;
	for (size_t i = 0; i < length; i++){
		tmp = new size_t[1];
		sh_tmp = new char[1];
		tmp[0] = data[i];
		sh_tmp[0] = shadow_data[i];
		merge_queue.enqueue(tmp, sh_tmp, 1);
		merge_queue.print(cout);
	}

	size_t *dat1, len1, *dat2, len2, i, j, k;
	char *sh_dat1, *sh_dat2;

	while (merge_queue.head->prev){
		merge_queue.dequeue(&dat1,&sh_dat1,len1);
		merge_queue.dequeue(&dat2,&sh_dat2,len2);

		
		print(cout, "   dat1", dat1, len1);
		print(cout, "sh_dat1", sh_dat1, len1);
		print(cout, "   dat2", dat2, len2);
		print(cout, "sh_dat2", sh_dat2, len2);
		
		i = 0;
		j = 0;
		k = 0;
		tmp = new size_t[len1 + len2];
		sh_tmp = new char[len1 + len2];


		while (i < len1 || j < len2){
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

			if (dat1[i] < dat2[j]){
				tmp[k] = dat1[i];
				sh_tmp[k++] = sh_dat1[i++];

			}
#pragma region ���������� ���� ��������� �� ���� ����������, ������ �� ������� ����� ��� ��������, ������ ���.
			else{
				if (dat1[i] = dat2[i]){//����� ������ ���� ������ ��������, ����, ���� ��� �� �������, � ���� ������������(���������� �������� ��������� ������� ����������).
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


		
		
		//������ ������� ������ �������� � �������� ��������, � ������� � ������� ����� ������, �� ��� ������������.
		delete(dat1);
		delete(dat2);
		print(cout, "   tmp", tmp, len1 + len2);
		print(cout, "sh_tmp", sh_tmp, len1 + len2);
		merge_queue.enqueue(tmp,sh_tmp, len1+len2);
		merge_queue.print(cout);
	}

}

int main(){
	ifstream in("input.txt");
	Queue_ myqeue;
	size_t n, m, iter = 0, b,e;

	in >> n >> m;
	size_t *all = new size_t[n * 2 + m];//��� ���, � ����� � ����� ��������.
	char *brackets = new char[n * 2 + m];//����������� ����������� ����� � ������.
	size_t *count = new size_t[n * 2 + m];//�����������.
	size_t *points = new size_t[m];//�����.
	
	for (size_t i = 0; i < n; i++){
		in >> b >> e;
		all[i * 2] = b;
		all[i * 2 + 1] = e;
		//myqeue.enqueue(all[i*2], all[i*2+1]);
		brackets[i * 2] = '{';
		brackets[i * 2 + 1] = '}';
	}
	for (size_t i = 0; i < m; i++){
		in >> points[i];
		all[i + 2 * n] = points[i];
		brackets[i + 2 * n] = '.';
	}

	print(cout,"all", all, 2 * n + m);
	print(cout, "brackets", brackets, 2 * n + m);
	merge_sort(all,brackets, n*2+m);

}



