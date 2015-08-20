#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;
int MAX = powl(2, sizeof(int)* 8-1) - 1;


template <class T>
void  fillarray(T *arr, T value, size_t size){
	for (size_t i = 0; i < size; i++) arr[i] = value;
}

template<class T>
ostream &printarray(ostream &stream, T *arr, char label[100], size_t begin, size_t end){
	stream << endl;
	stream << label << ": ";
	for (size_t i = begin; i <= end; i++)
		stream << arr[i] << " ";
	stream << endl;
	return stream;
}

#pragma region Heap

class Heap{

private:
	struct node{
		size_t *key;
		size_t *data;
		node(size_t *k, size_t *d) : key(k), data(d){}
		node() :key(NULL), data(NULL){}
	};

	node **heap;//Ссылочный массив ссылок.
	size_t max_length;

public:
	size_t length;
	//TODO : запилить конструкторы, дефолтный и тот, что принимает на вход массивы
	Heap(size_t size);
	size_t data(size_t i);//
	size_t key(size_t i);
	size_t parent(size_t i);//
	size_t leftc(size_t i);//
	size_t rightc(size_t i);//


	void siftup(size_t i);//
	void siftdown(size_t i);//
	void swap(size_t i, size_t j);//	
	void inserttail(size_t *k, size_t *d);//
	void insert(size_t *k, size_t *d);//
	void changepriority(size_t i);
	size_t extractmin();//
	//TODO : add del to Dejkstra alg Heap
	//void del(size_t i);
	void printheap();//

	

};

Heap::Heap(size_t size) :length(0){//Этот ноль значит, что пока в массивеЛ(куче) нет элементов, хоть она и инециаллизирована
	max_length = size;
	heap = new node[100001];
	//Так, мы создаем кучу на заранее известное колличество мест, 
	//вставка не подразумевает создание новых объектов, только заполнение
	//изначально созданных.

	
	for (size_t i = 0; i < size; i++)
		heap[i] = new node();
	//TODO : ХУЛИ ОНО ПАДАЕТ, кажется мы не инициаллизиновали **heap, ой тут мы это и делаем, хм, что тогда с нодом не так
}

size_t Heap::data(size_t i){
	return *(heap[i]->data);
}

size_t Heap::key(size_t i) {
	return *(heap[i]->key);
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
	if (key(pi) > key(i)) {
		swap(i, pi);
		siftup(pi);
	}
}

void Heap::siftdown(size_t i){
	size_t li = leftc(i);
	size_t ri = rightc(i);
	//Я понял, тут нигде нет проверки на NULL, 
	//потому что я дерево изначально созадаю со всеми листьями и на много этажей вперед память выделяю.
	//и все заполняю сразу нулями, с которыми сравнение работае.
	//TODO : посмотреть конструктор кучи

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

void Heap::inserttail(size_t *k, size_t *d){
	heap[length]->key = k;
	heap[++length]->data = d;

}

void Heap::insert(size_t *k, size_t *d){
	if (length == max_length){
		cout << endl << "!!!HEAP OVERFLOW!!!" << endl;
		return;
	}
	inserttail(k, d);
	siftup(length);
}

void Heap::changepriority(size_t i){
	siftdown(i);
	siftup(i);
}

/*void Heap::changepriority(size_t *k, size_t v){
	size_t i = 1, li, ri;
	while (i <= length){
		li = leftc(i);
		ri = rightc(i);
		if (heap[i]<heap[li])
	}
}*/

size_t Heap::extractmin(){
	node *tmp = heap[1];
	heap[1] = heap[length];
	heap[length]->data = 0;
	heap[length]->key = 0;
	length--;
	siftdown(1);
	return *(tmp->data);
}

#pragma endregion

#pragma region Graph

class Graph{
private:
	struct node{
		size_t name;
		int weight;
		node *next;
		node() : name(0), weight(-1), next(NULL){}
		node(size_t nm, int w, node *n) : name(nm), weight(w), next(n) {}
	};

	class Queue__{
	private:
		node *head;
		node *tail;
	public:
		size_t size;

		Queue__() :head(NULL), tail(NULL), size(0){}
		void inject(size_t nm);
		size_t eject();
		void clr();
		ostream &print(ostream &stream);
	};

public:
	Queue__ Q;
	//Heap H;

	size_t e_num;
	size_t v_num;
	node *vertices;
	bool *visited;
	int *dist;
	size_t *prev;

	Graph() :e_num(0), v_num(0),  vertices(NULL), visited(NULL), dist(NULL), prev(NULL)/*, H(MAX) */{}

	void add(node *adj_array, size_t xv, size_t yv, int w);
	void add(istream &in, node **adj_array);

	void explore(size_t v, node *adj_array);
	void dfs(node *adj_array);
	void bfs(node *adj_array, size_t s);
	void relax(size_t u, size_t v);
	int weight(size_t u, size_t v);
	
	void clrvisited();
	ostream &print_adjacency(ostream &stream, node *adj_array);
	
};

void Graph::Queue__::inject(size_t nm){
	if (!head){
		tail = new node(nm, -1, NULL);
		head = tail;
	}
	else{
		tail->next = new node(nm, -1, NULL);
		tail = tail->next;
	}

}

size_t Graph::Queue__::eject(){
	
	if (head){
		size_t r = head->name;
		
		if (head->next){
			node *tmp = head->next;
			delete(head);
			head = tmp;			
		}
		else{
			delete(head);
			head = NULL;
			tail = NULL;
		}
		
		return r;
	}
	return 0;
}

void Graph::Queue__::clr(){
	while (eject() != 0){}
}

ostream &Graph::Queue__::print(ostream &stream){
	stream << endl << "queue: " << endl << endl;
	node *tmp = head;
	while (tmp){
		stream << "(" << tmp->name << ") - ";
		tmp = tmp->next;
	}
	stream << "NULL" << endl;
	stream << "______________________________________________________________________________________________________________________" << endl;
	return stream;
}

void Graph::add(node *adj_array, size_t xv, size_t yv, int w){

	node *tmp = &adj_array[xv];
	while (tmp->next && tmp->next->name < yv)
		tmp = tmp->next;
	tmp->next = new node(yv, w, tmp->next);//Вставляем сразу на нужное место
}

void Graph::add(istream &in, node **adj_array){
	size_t vn, en;
	in >> vn >> en;

	*adj_array = new node[vn + 1];
	this->v_num = vn;
	this->e_num = en;

	for (size_t i = 1; i <= vn; i++)
		(*adj_array)[i].name = i;

	visited = new bool[vn + 1];
	fillarray(visited, false, vn + 1);

	dist = new int[vn + 1];
	fillarray<int>(dist, -1, vn + 1);

	prev = new size_t[vn + 1];
	fillarray<size_t>(prev, 0, vn + 1);

	size_t xv, yv;
	int w;
	for (size_t i = 0; i < en; i++){
		in >> xv >> yv >> w;
		this->add(*adj_array, xv, yv, w);
		//this->add(*adj_array, yv, xv);//Неориентированный.
	}

}

void Graph::explore(size_t v, node *adj_array){

	visited[v] = true;

	node *tmp = &adj_array[v];
	while (tmp->next){
		tmp = tmp->next;
		
		//Переходим по следующему ребру, если еще не были в вершине, что на конце его.
		if (!visited[tmp->name])
			explore(tmp->name, adj_array);
	}
}

void Graph::dfs(node *adj_array){
	
	clrvisited();
	for (size_t i = 1; i <= this->v_num; i++)
	if (!visited[i]) {explore(i, adj_array); }
}

void Graph::bfs(node *adj_array, size_t s){
	
	dist[s] = 0;
	Q.inject(s);
	
	node *tmp;
	size_t u, v;
	while ((u = Q.eject()) != 0){
		tmp = &vertices[u];
		while (tmp->next){
			tmp = tmp->next;
			v = tmp->name;

			relax(u, v);
			//Просто поиск в ширину для невзвешенного графа.
			/*if (dist[v] == -1){
				Q.inject(v);
				dist[v] = dist[u]+1;
			}*/
		}
	}
}

void Graph::relax(size_t u, size_t v){
	int w = weight(u, v);
	//cout << "relax: (" << u << ") -> (" << v << ") [" << w <<"]" << endl;
	if (dist[v]== -1 || dist[v] > dist[u] + w) {
		Q.inject(v);
		dist[v] = dist[u] + w;
		prev[v] = u;
		
		//Q.print(cout);	
	}
		
}

int Graph::weight(size_t u, size_t v){
	node *tmp = &vertices[u];
	while (tmp->next){
		tmp = tmp->next;
		if (tmp->name == v) return tmp->weight;
	}
	return -1;
}

void Graph::clrvisited(){
	fillarray(visited, false, this->v_num + 1);
}

ostream &Graph::print_adjacency(ostream &stream, node *adj_array){
	stream << endl << "adjacency list: " << endl << endl;
	node *tmp;
	for (size_t v = 1;(adj_array) && (v <= this->v_num); v++){
		tmp = &adj_array[v];
		while (tmp){
			stream << "(" << tmp->name << ") - ";
			tmp = tmp->next;
		}
		stream << "NULL" << endl;
	}
	stream << "______________________________________________________________________________________________________________________" << endl;
	return stream;
}

#pragma endregion


int main(){

	ifstream in("input.txt");


	//Рандомное заполнение графа.
	/*size_t n = 100;
	out << n <<" "<< n << endl;
	for (size_t i = 1; i <= n; i++)
	out << (rand() % n) +1 << " " << (rand() % n) +1 << endl;*/

	//Graph g;
	//g.add(in, &g.vertices);//Разберись с сылками.
	//g.print_adjacency(cout, g.vertices);	

	//for (size_t i = 1; i < g.v_num; i++)
	//	g.Q.inject(i);

	//g.Q.print(cout);
	//g.Q.clr();
	//g.Q.print(cout);
	//g.dfs();

	size_t s, t;
	//in >> s >> t;

	//g.bfs(g.vertices, s);

	//printarray(cout, g.dist, "dist", 1, g.v_num);
	//cout << /*(g.dist[t] != -1 ? g.dist[t] : -1)*/g.dist[t] << endl;


	//Проверка измененной кучи, на массиве ключей и массиве информации.
#pragma region Создаем масивы ключей и данных
	size_t *tmpdata = new size_t[10];
	for (size_t i = 0; i < 10; i++)
		tmpdata[i] = (size_t)(abs( rand()) % 10)+100;

	size_t *tmpkey = new size_t[10];
	for (size_t i = 0; i < 10; i++)
		tmpkey[i] = (size_t)(abs(rand()) % 10);

	printarray<size_t>(cout, tmpdata, "tmpdata", 0, 9);
	printarray<size_t>(cout, tmpkey, "tmpkey", 0, 9);
#pragma endregion

#pragma region Проверяем кучу
	//TODO : почему мы объявляем и сразу, без new можем создавать экземпляры класса, пользовательского.
	Heap H(10);
	for (size_t i = 0; i < 10; i++)
		H.insert(&tmpkey[i], &tmpdata[i]);
#pragma endregion

	
}
