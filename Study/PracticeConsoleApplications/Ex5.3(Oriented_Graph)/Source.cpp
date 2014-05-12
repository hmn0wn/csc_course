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
	for (size_t i = begin; i <= end; i++)
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
	size_t *first_time;
	size_t *last_time;
	size_t connected_component_count;

	size_t timer;
	bool circle;


	Graph() :head(NULL), edges_num(0), vertices_num(0), visited(NULL), connected_component_count(0), timer(0), first_time(NULL), last_time(NULL), circle(false) {}
	void add(size_t xv, size_t yv);
	void add(istream &in);
	void merge_sort(node *begin, size_t size);
	void bubble_sort();
	void swap(node *x, node *y);
	void explore(size_t v);
	void dfs();
	void clrvisited();
	ostream &print_adjacency(ostream &stream);
	ostream &print_time_segments(ostream &stream);

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
	
	//Быдлокод.
	delete(visited);
	visited = new bool[vertices_num];
	delete(first_time);
	first_time = new size_t[vertices_num];
	fillarray<size_t>(first_time, 0, vertices_num);
	delete(last_time);
	last_time = new size_t[vertices_num];
	fillarray<size_t>(last_time, 0, vertices_num);

	edges_num++;
}

void Graph::add(istream &in){
	size_t xv, yv, vn, en;
	int w;
	in >> vn >> en;

	for (size_t i = 0; i < en; i++){
		in >> xv >> yv/* >> w*/;
		this->add(xv, yv);
		
	}
	this->vertices_num = vn;
	this->edges_num = en;

	visited = new bool[vn];
	fillarray(visited, false, vn);

	first_time = new size_t[vn];
	fillarray<size_t>(first_time, 0, vn);

	last_time = new size_t[vn];
	fillarray<size_t>(last_time, 0, vn);
}

/*void Graph::merge_sort(node **head, node *begin, size_t size){

	if (size == 1) return;
	node *begin1 = begin, *begin2 = begin1;
	size_t size1 = size / 2, size2 = size - size1;
	
	for (size_t i = 0; i < size1; i++) begin2 = begin2->next;
	merge_sort(begin1, size1);
	merge_sort(begin2, size2);

	//Отсортировали подсписки, теперь сливаем.
	
	
	

	node *tmp;//А итерироватья будем уже ранее созданными begin1, begin2.
	size_t i = 0, j = 0;
	//Так, для начала нам необходимо зафиксировать самое начало, выбрать из двух первых элементов списков самый маленький элемент.
	if (begin1->first_vertice < begin2->first_vertice){
		begin
	}
	
	while (i < size1 && j < size2){
		
		if (begin1->first_vertice < begin2->first_vertice){
			//tmp->next///
		}
	}


}*/

void Graph::bubble_sort(){

	if (edges_num <= 1) return;//Нечего сортировать.
	node *ni, *nj;
	for (size_t i = edges_num-1; i > 0; i--){
		ni = head;
		nj = head->next;
		for (size_t j = 0; j < i; j++){

			if (ni->first_vertice > nj->first_vertice) swap(ni, nj);
			else 
			if (ni->first_vertice == nj->first_vertice)
			if (ni->second_vertice > nj->second_vertice) swap(ni, nj);
			
			ni = nj;
			nj = nj->next;
			

		}
	}
}

void Graph::swap(node *x, node *y){
	size_t tmp = x->first_vertice;
	x->first_vertice = y->first_vertice;
	y->first_vertice = tmp;

	tmp = x->second_vertice;
	x->second_vertice = y->second_vertice;
	y->second_vertice = tmp;

	//Вес у всех пока нулевой, так что не меняю.
}

void Graph::explore(size_t v){
	//Кажется, что этот массив больше не нужен.
	visited[v - 1] = true;
	//Записываем время начала обработки вершины.
	first_time[v - 1] = ++timer;
	node *tmp = head;
	while (tmp){
		if (tmp->first_vertice == v){
			//Провека на обратные и перекрестные ребра.
			if (first_time[tmp->second_vertice - 1] > 0 && last_time[tmp->second_vertice-1] == 0) {
				circle = true;
				//cout << endl << "circle: " << tmp->second_vertice << endl;
				//cout << "time: " << timer << endl;
			}
			//Переходим по следующему ребру, если еще не были в мершине, что на конце его.
			if (!visited[tmp->second_vertice - 1])
				explore(tmp->second_vertice);
		}
			tmp = tmp->next;		
	}
	//Рекурсия втягивается, пройдя по всем возможным ребрам исходящим из вершины, мы в нее возвращаемся и записываем конец временного отрезка обработки.
	last_time[v - 1] = ++timer;

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
	stream << endl << "adjacency list: " << endl << endl;
	node *tmp = head;
	while (tmp){
		stream << "(" << tmp->first_vertice << "," << tmp->second_vertice << ") - ";
		tmp = tmp->next;
	}
	stream << "NULL" << endl << "______________________________________________________________________________________________________________________" << endl;
	return stream;
}

ostream &Graph::print_time_segments(ostream &stream){

	stream << endl << "time segments: " << endl << endl;
	for (size_t v = 1; v <= vertices_num; v++){
		stream << "[" << v << "]: " /*<< first_time[v-1] << " "<<last_time[v-1] <<"): " <<endl*/;
		for (size_t t = 0; t <= timer; t++)
			stream << ((t<first_time[v - 1] || t>last_time[v - 1]) ? " " : "_");
		stream << endl;
	}

	stream << endl << "______________________________________________________________________________________________________________________" << endl;
	return stream;
}

void Graph::traverce_test(){
	cout << endl << "traverce test: " << endl;
	//Тестируем обход.
	for (size_t i = 1; i < this->vertices_num + 1; i++){
		cout << endl << "explore[" << i << "]: ";
		this->clrvisited();
		this->explore(i);
		printarray(cout, this->visited, 0, this->vertices_num - 1);

	}
	cout << endl << "______________________________________________________________________________________________________________________" << endl;
}

void Graph::path_check_test(){
	//Тестируем проверку пути.	
	cout << endl << "path check test: " << endl;
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
	//printarray(cout, mygraph_.first_time, 0, mygraph_.vertices_num - 1);
	//printarray(cout, mygraph_.last_time, 0, mygraph_.vertices_num - 1);
	//mygraph_.print_adjacency(cout);
	mygraph_.bubble_sort();
	//mygraph_.print_adjacency(cout);
	mygraph_.dfs();
	//mygraph_.traverce_test();
	//mygraph_.path_check_test();
	//printarray(cout, mygraph_.first_time, 0, mygraph_.vertices_num-1);
	//printarray(cout, mygraph_.last_time, 0, mygraph_.vertices_num-1);
	//mygraph_.print_time_segments(cout);
	cout << /*"circle: " <<*/ ((mygraph_.circle) ? "True" : "False" )<<endl;





	//Задача на проверку пути.
	/*size_t x, y;
	in >> x >> y;
	mygraph_.clrvisited();
	mygraph_.explore(x);
	cout << ((mygraph_.visited[y - 1]) ? "True" : "False");*/





	//Задача на связность.
	//mygraph_.dfs();
	//cout << mygraph_.connected_component_count << endl;

}
