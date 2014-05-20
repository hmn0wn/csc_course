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

	size_t e_num;
	size_t v_num;
	node *vertices;
	bool *visited;
	int *dist;
	size_t *prev;

	Graph() :e_num(0), v_num(0),  vertices(NULL), visited(NULL), dist(NULL), prev(NULL) {}

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

	Graph g;
	g.add(in, &g.vertices);//Разберись с сылками.
	//g.print_adjacency(cout, g.vertices);	

	//for (size_t i = 1; i < g.v_num; i++)
	//	g.Q.inject(i);
	
	//g.Q.print(cout);
	//g.Q.clr();
	//g.Q.print(cout);
	//g.dfs();

	size_t s, t;
	in >> s >> t;

	g.bfs(g.vertices, s);

	//printarray(cout, g.dist, "dist", 1, g.v_num);
	cout << /*(g.dist[t] != -1 ? g.dist[t] : -1)*/g.dist[t] << endl;
	
	
}
