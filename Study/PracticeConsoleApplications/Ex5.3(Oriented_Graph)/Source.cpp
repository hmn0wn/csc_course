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
	size_t c_c_count;
	size_t timer;
	bool circle;

	node *vertices;
	node *r_vertices;
	size_t *tsorted_vertices;
	node *last_time_sorted_vertices;
	bool l_t_s_v;
	bool *visited;
	
	size_t *indegree;
	size_t *f_time;
	size_t *l_time;
	

	Graph() :e_num(0), v_num(0), c_c_count(0),timer(0), circle(false), vertices(NULL), visited(NULL),  f_time(NULL), l_time(NULL), tsorted_vertices(NULL), r_vertices(NULL), last_time_sorted_vertices(NULL), l_t_s_v(false){}

	void add(node *adj_array, size_t xv, size_t yv);
	void add(istream &in);
	
	void explore(size_t v, node* adj_array);
	void dfs(node *adj_array);
	void scc();
	void top_sort(node *adj_array);
	void reverse();

	void clrvisited();
	ostream &print_adjacency(ostream &stream, node *adj_array);
	ostream &print_time_segments(ostream &stream);
	ostream &print_l_t_s_v(ostream &stream);

	void traverce_test();
	void path_check_test();

};

void Graph::add(node *adj_array, size_t xv, size_t yv){
	node *tmp = &adj_array[xv];
	while (tmp->next && tmp->next->name < yv) 
		tmp = tmp -> next;
	tmp->next = new node(yv, tmp->next);//Вставляем сразу на нужное место
}

void Graph::add(istream &in){
	size_t xv, yv, vn, en;
	in >> vn >> en;

	vertices = new node[vn+1];
	this->v_num = vn;
	this->e_num = en;

	for (size_t i = 1; i <= vn; i++)
		vertices[i].name = i;

	visited = new bool[vn+1];
	fillarray(visited, false, vn+1);

	f_time = new size_t[vn+1];
	fillarray<size_t>(f_time, 0, vn+1);

	l_time = new size_t[vn+1];
	fillarray<size_t>(l_time, 0, vn+1);
	
	tsorted_vertices = new size_t[vn + 1];
	fillarray<size_t>(tsorted_vertices, 0, vn+1);

	indegree = new size_t[vn + 1];
	fillarray<size_t>(indegree, 0, vn + 1);

	for (size_t i = 0; i < en; i++){
		in >> xv >> yv;
		this->add(vertices, xv, yv);
		indegree[yv]++;
		
	}
	
}

void Graph::explore(size_t v, node *adj_array){
	
	visited[v] = true;
	
	f_time[v] = ++timer;//Записываем время начала обработки вершины.

	node *tmp = &adj_array[v];
	while (tmp->next){
		tmp = tmp->next;
		if (f_time[tmp->name] > 0 && l_time[tmp->name] == 0) {//Провека на обратные и перекрестные ребра.
			circle = true;
			//cout << endl << "circle: " << tmp->name << endl;
			//cout << "time: " << timer << endl;
		}

		//Переходим по следующему ребру, если еще не были в вершине, что на конце его.
		if (!visited[tmp->name])
			explore(tmp->name, adj_array);
	}
					
		//Рекурсия втягивается, пройдя по всем возможным ребрам исходящим из вершины, мы в нее возвращаемся и записываем конец временного отрезка обработки.
	l_time[v] = ++timer;

	//Если список не построен, строим.
	if(!l_t_s_v) last_time_sorted_vertices = new node(v, last_time_sorted_vertices);

}

void Graph::dfs(node *adj_array){
	c_c_count = 0;
	this->timer = 0;
	clrvisited();
	for (size_t i = 1; i <= this->v_num; i++)
	if (!visited[i]) { c_c_count++; explore(i, adj_array); }
}

void Graph::scc(){

	
	this->reverse();
	this->dfs(this->r_vertices);
	//Говорим експлору, что список по времени окончания строить не нужно.
	this->l_t_s_v = true;

	c_c_count = 0;
	this->timer = 0;
	clrvisited();

	size_t v;
	node *tmp = last_time_sorted_vertices;
	while (tmp){
		v = tmp->name;
		tmp = tmp->next;
		if (!visited[v]){ c_c_count++; explore(v, vertices); }
	}

}

void Graph::top_sort(node *adj_array){

	size_t iter = 1, jter = 1;
	node *tmp;
	for (size_t i = 1; i <= v_num; i++)
	if (!indegree[i]) tsorted_vertices[jter++] = i;

	while (iter <= v_num){
		//printarray(cout, indegree, "indegree", 1, v_num);
		//printarray(cout, tsorted_vertices, "topological sorted graph", 1, v_num);

		tmp = &adj_array[tsorted_vertices[iter++]];
		while (tmp->next){
			tmp = tmp->next;
			indegree[tmp->name]--;
			if(!indegree[tmp->name]) tsorted_vertices[jter++] = tmp->name;
		}
	}

	

}

void Graph::reverse(){
	
	node *tmp;
	r_vertices = new node[v_num+1];
	for (size_t v = 1; v <= v_num; v++)
		r_vertices[v].name = v;

	for(size_t v = 1; v <= v_num; v++){
		tmp = &vertices[v];
		while (tmp->next){
			tmp = tmp->next;
			this->add(r_vertices, tmp->name, v);
			
		}
	}
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

ostream &Graph::print_time_segments(ostream &stream){

	stream << endl << "time segments: " << endl << endl;
	for (size_t v = 1; v <= v_num; v++){
		stream << "[" << v << "]: " << f_time[v] << " "<<l_time[v] <<"): " <<endl;
		for (size_t t = 0; t <= timer; t++)
			stream << ((t<f_time[v] || t>l_time[v]) ? " " : "_");
		stream << endl;
	}

	stream << endl << "______________________________________________________________________________________________________________________" << endl;
	return stream;
}

ostream &Graph::print_l_t_s_v(ostream &stream){
	stream << endl << "last time sorted list: " << endl << endl;
	node *tmp = last_time_sorted_vertices;
	while (tmp){
		stream <<"("<< tmp->name << ") - ";
		tmp = tmp->next;
	}
	stream << "NULL" << endl;
	stream << "______________________________________________________________________________________________________________________" << endl;
	return stream;
}

int main(){
	
	ifstream in("input.txt");
	ofstream out("output.txt");
	/*size_t n = 100;
	out << n <<" "<< n << endl;
	for (size_t i = 1; i <= n; i++)
		out << (rand() % n) +1 << " " << (rand() % n) +1 << endl;*/
	
	Graph g;
	g.add(in);

	//g.print_adjacency(cout, g.vertices);
	g.scc();
	//g.print_adjacency(cout, g.r_vertices);
	//g.dfs();
	//g.top_sort();
	//printarray(cout, g.f_time, "first time", 1, g.v_num);
	//printarray(cout, g.l_time, "last time", 1, g.v_num);
	//g.print_l_t_s_v(cout);
	cout << g.c_c_count << endl;
	//printarray(cout, g.indegree, "  indegree", 1, g.v_num);
	//printarray(cout, g.tsorted_vertices, "topological sorted graph", 1, g.v_num);
	//g.print_time_segments(cout);
	//cout << "circle: " << ((g.circle) ? "True" : "False" )<<endl;

	



	//Задача на проверку пути.
	/*size_t x, y;
	in >> x >> y;
	g.clrvisited();
	g.explore(x);
	cout << ((g.visited[y - 1]) ? "True" : "False");*/





	

}
