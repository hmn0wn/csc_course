#include <fstream>
#include <iostream>
using namespace std;

template <class T>
void  fillarray(T *arr, T value, size_t size){
	for (size_t i = 0; i < size; i++) arr[i] = value;
}

template<class T>
ostream &printarray(ostream &stream, T *arr, size_t begin, size_t end){
	stream << endl;
	for (size_t i = begin; i <=end; i++)
		stream << arr[i] << " ";
	stream << endl;
	return stream;
}

class Graph{
private:
	struct node{
		size_t first_vertice;
		size_t second_vertice;
		int weight;
		node *next;
		node(size_t fir_v, size_t sec_v) 
			:first_vertice(fir_v), second_vertice(sec_v), next(NULL), weight(0){}
	};
	
	node *head;
public:
	size_t edges_num;
	size_t vertices_num;
		
	
	Graph() :head(NULL), edges_num(0), vertices_num(0) {}
	void add(size_t xv, size_t yv);
	void add(istream &in);
	void explore(size_t v, bool *visited);
	ostream &printadj(ostream & stream);

};

void Graph::add(size_t xv, size_t yv){
	
	if (head){
		node *tmp = head;
		while (tmp->next){
			if (tmp->first_vertice == xv && tmp->second_vertice == yv) return;
			tmp = tmp->next;
		}
		if (tmp->first_vertice == xv && tmp->second_vertice == yv) return;
		tmp->next = new node(xv, yv);
	}
	else head = new node(xv, yv);	
	edges_num++;
}

void Graph::add(istream &in){
	size_t xv, yv, vn, en;
	int w;
	in >> vn >> en;

	for (size_t i = 0; i < en; i++){
		in >> xv >> yv >> w;
		this->add(xv, yv);
		this->add(yv, xv);
	}
	this->vertices_num = vn;
	this->edges_num = en;
}

void Graph::explore(size_t v, bool *visited){
	visited[v] = true;
	node *tmp = head;
	while (tmp){
		if (tmp->first_vertice == v && !visited[tmp->second_vertice]) explore(tmp->second_vertice, visited);//Ныряем если можно и если не былы там.
		tmp = tmp->next;
	}
	//Функция для ориентированного ребра, а при вводе для неоориентированного нужно продублировать.

}

ostream &Graph::printadj(ostream &stream){
	node *tmp = head;
	while (tmp){
		stream << "(" << tmp->first_vertice << "," << tmp->second_vertice << ") - ";
		tmp = tmp->next;
	}
	stream << "NULL" << endl;
	return stream;
}




int main(){
	ifstream in("input.txt");
	Graph mygraph;
	for (size_t i = 0; i < 10; i++){
		mygraph.add(1, 1);
	}
	mygraph.printadj(cout);
	
	Graph mygraph_;
	mygraph_.add(in);
	mygraph_.printadj(cout);

	bool *visited = new bool[mygraph_.vertices_num+1];
	

	for (size_t i = 1; i < mygraph_.vertices_num+1; i++){
		cout << endl<<"explore[" << i << "]: ";
		fillarray(visited, false, mygraph_.vertices_num+1);
		mygraph_.explore(i, visited);
		printarray(cout, visited, 1, mygraph_.vertices_num);
	}
}
