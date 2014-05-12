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
	bool *visited;
	size_t connected_component_count;
		
	
	Graph() :head(NULL), edges_num(0), vertices_num(0), visited(NULL), connected_component_count(0) {}
	void add(size_t xv, size_t yv);
	void add(istream &in);
	void explore(size_t v);
	void dfs();
	void clrvisited();
	ostream &print_adjacency(ostream & stream);

	void traverce_test();
	void path_check_test();

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
		if (this->vertices_num < xv) this->vertices_num = xv;
		if (this->vertices_num < yv) this->vertices_num = yv;
	}
	else head = new node(xv, yv);	
	delete(visited);//Быдлокод.
	visited = new bool[vertices_num];
	edges_num++;
}

void Graph::add(istream &in){
	size_t xv, yv, vn, en;
	int w;
	in >> vn >> en;

	for (size_t i = 0; i < en; i++){
		in >> xv >> yv/* >> w*/;
		this->add(xv, yv);
		this->add(yv, xv);
	}
	this->vertices_num = vn;
	this->edges_num = en;

	visited = new bool[vn];
	fillarray(visited, false, vn);
}

void Graph::explore(size_t v){
	visited[v-1] = true;
	node *tmp = head;
	while (tmp){
		if (tmp->first_vertice == v && !visited[tmp->second_vertice-1]) 
			explore(tmp->second_vertice);//Ныряем если можно и если не былы там.
		tmp = tmp->next;
	}
	//Функция для ориентированного ребра, а при вводе для неоориентированного нужно продублировать.

}

void Graph::dfs(){
	connected_component_count = 0;
	clrvisited();
	for (size_t i = 1; i <= this->vertices_num; i++)	
	if (!visited[i - 1]) { connected_component_count++; explore(i); }
}

void Graph::clrvisited(){
	fillarray(visited, false, this->vertices_num + 1);
}

ostream &Graph::print_adjacency(ostream &stream){
	stream << endl << "adjacency list: " <<endl <<endl ;
	node *tmp = head;
	while (tmp){
		stream << "(" << tmp->first_vertice << "," << tmp->second_vertice << ") - ";
		tmp = tmp->next;
	}
	stream << "NULL" << endl << "______________________________________________________________________________________________________________________" << endl;
	return stream;
}

void Graph::traverce_test(){
	cout << endl << "traverce test: " << endl ;
	//Тестируем обход.
	for (size_t i = 1; i < this->vertices_num+1; i++){
		cout << endl<<"explore[" << i << "]: ";
		this->clrvisited();
		this->explore(i);
		printarray(cout, this->visited, 0, this->vertices_num-1);

	}
	cout << endl << "______________________________________________________________________________________________________________________" << endl;
}

void Graph::path_check_test(){
	//Тестируем проверку пути.	
	cout << endl << "path check test: " <<endl;
	for (size_t x = 1; x <= this->vertices_num; x++){
		cout << endl;
		for (size_t y = 1; y <= this->vertices_num; y++){
			this->clrvisited();
			this->explore(x);
			cout << x << "->" << y << ": " << ((this->visited[y - 1]) ? "True" : "False") << endl;
		}
	}
	cout << endl << "______________________________________________________________________________________________________________________" << endl;
}


int main(){
	ifstream in("input.txt");
	/*Graph mygraph;
	for (size_t i = 1; i < 1001; i++){
		mygraph.add(i, i+1);
	}*/
	//mygraph.print_adjacency(cout);
	//mygraph.traverce_test();
	//mygraph.path_check_test();

	Graph mygraph_;
	mygraph_.add(in);
	//mygraph_.print_adjacency(cout);
	//mygraph_.traverce_test();
	//mygraph_.path_check_test();
	
	



	//Задача на проверку пути.
	size_t x, y;
	in >> x >> y;
	mygraph_.clrvisited();
	mygraph_.explore(x);
	cout << ((mygraph_.visited[y - 1]) ? "True" : "False" );
	




	//Задача на связность.
	//mygraph_.dfs();
	//cout << mygraph_.connected_component_count << endl;
	
}
