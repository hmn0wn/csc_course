#include <fstream>
#include <iostream>
using namespace std;



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

#pragma region Queue_
template <class T>
class Queue_{
private:
	struct node{
		T *data;
		node *next;
		node(T *d, node *n) :data(d), nest(n){}
	};
	T *head;
	T *tail;
	

public:
	size_t size;
	
	Queue_() : head(NULL), tail(NULL), size(0) {}
	
	void Inject(T *e);
	T* Eject();
	void clr();
};
template <class T>
void Queue_::Inject(T *e){
	
	if (!this->tail){
		tail = e;
		head = e;
	}
	else{
		
	}
}

#pragma endregion 

#pragma region Graph

class Graph{
private:
	struct node{
		size_t name;
		node *next;
		node() : name(0), next(NULL){}
		node(size_t nm, node *n) : name(nm), next(n){}
	};

public:
	size_t e_num;
	size_t v_num;
	node *vertices;
	bool *visited;

	Graph() :e_num(0), v_num(0),  vertices(NULL), visited(NULL){}

	void add(node *adj_array, size_t xv, size_t yv);
	void add(istream &in, node *adj_array);

	void explore(size_t v, node* adj_array);
	void dfs(node *adj_array);	
	
	void clrvisited();
	ostream &print_adjacency(ostream &stream, node *adj_array);
	
};

void Graph::add(node *adj_array, size_t xv, size_t yv){
	node *tmp = &adj_array[xv];
	while (tmp->next && tmp->next->name < yv)
		tmp = tmp->next;
	tmp->next = new node(yv, tmp->next);//Вставляем сразу на нужное место
}

void Graph::add(istream &in, node *adj_array){
	size_t xv, yv, vn, en;
	in >> vn >> en;

	adj_array = new node[vn + 1];
	this->v_num = vn;
	this->e_num = en;

	for (size_t i = 1; i <= vn; i++)
		adj_array[i].name = i;

	visited = new bool[vn + 1];
	fillarray(visited, false, vn + 1);

	for (size_t i = 0; i < en; i++){
		in >> xv >> yv;
		this->add(adj_array, xv, yv);
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

void Graph::clrvisited(){
	fillarray(visited, false, this->v_num + 1);
}

ostream &Graph::print_adjacency(ostream &stream, node *adj_array){
	stream << endl << "adjacency list: " << endl << endl;
	node *tmp;
	for (size_t v = 1; v <= this->v_num; v++){
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
	ofstream out("output.txt");

	//Рандомное заполнение графа.
	/*size_t n = 100;
	out << n <<" "<< n << endl;
	for (size_t i = 1; i <= n; i++)
	out << (rand() % n) +1 << " " << (rand() % n) +1 << endl;*/

	Graph g;
	g.add(in, g.vertices);

	//g.print_adjacency(cout, g.vertices);	
	//g.dfs();
	
}
