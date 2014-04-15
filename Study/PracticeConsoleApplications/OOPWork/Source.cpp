#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string.h>
using namespace std;

class comp_component{
public:
	virtual ostream &show_properties(ostream &stream) = 0;
};

class computer_screen : public comp_component{
public:
	computer_screen(){
		strcpy(type, "");
		colors = 0;
		x_resolution = 0;
		y_resolution = 0;
	}
	computer_screen(char *, long, int, int);
	ostream &show_properties(ostream &stream);

private:
	char type[32];
	long colors;
	int x_resolution;
	int y_resolution;
};

computer_screen::computer_screen(char *type, long colors, int x_res, int y_res){
	strcpy(computer_screen::type, type);
	computer_screen::colors = colors;
	computer_screen::x_resolution = x_res;
	computer_screen::y_resolution = y_res;
}

ostream &computer_screen::show_properties(ostream &stream){
	stream << "Type of screen:\t" << type << endl;
	stream << "Colors:\t" << colors << endl;
	stream << "Resolution:\t" << x_resolution << " x " << y_resolution << endl;
	return stream;
}

class mother_board : public comp_component{
public:
	mother_board(){
		processor = 0;
		speed = 0;
		RAM = 0;
	}
	mother_board(int, int, int);
	ostream &show_properties(ostream &stream);

private:
	int processor;
	int speed;
	int RAM;
};

mother_board::mother_board(int processor, int speed, int ram){
	mother_board::processor = processor;
	mother_board::speed = speed;
	mother_board::RAM = ram;
}

ostream & mother_board::show_properties(ostream &stream){
	stream << "Processor:\t" << processor << endl;
	stream << "Speed:\t" << speed << " Mz" << endl;
	stream << "RAM:\t" << RAM << " Mb" << endl;
	return stream;
}

class computer : public computer_screen, public mother_board{

public:
	computer();
	computer(int, char *, long, int, int, int, int, int);
	ostream &show_properties(ostream &stream);

private:
	int hard_disc;	
};
computer::computer(){
	hard_disc = 0;
}

computer::computer(int hard_disc, char *screen_type, long colors, int x_res, int y_res, int processor, int speed, int ram) :
computer_screen(screen_type, colors, x_res, y_res), mother_board(processor, speed, ram){
	computer::hard_disc = hard_disc;
	
}

ostream &computer::show_properties(ostream &stream){
	computer_screen::show_properties(stream);
	mother_board::show_properties(stream);
	stream << "Hard drive:\t" << hard_disc << endl;
	return stream;
}

class pc :public computer{

public:
	pc(int, int, char *, long, int, int, int, int, int);
	ostream &show_properties(ostream &stream);
private:
	int mouse_dpi;
};

pc::pc(int m_dpi, int hard_disc, char *screen_type, long colors, int x_res, int y_res, int processor, int speed, int ram) :
computer(hard_disc, screen_type, colors, x_res, y_res, processor, speed, ram){
pc:mouse_dpi = m_dpi;
}

ostream & pc::show_properties(ostream &stream){
	computer::show_properties(stream);
	stream << "Mouse dpi:\t" << mouse_dpi << endl;
	return stream;
}

class laptop :public computer{

public:
	laptop(bool, int, char *, long, int, int, int, int, int);
	ostream &show_properties(ostream &stream);
private:
	bool touchpad;
};

laptop::laptop(bool tch, int hard_disc, char *screen_type, long colors, int x_res, int y_res, int processor, int speed, int ram) :
computer(hard_disc, screen_type, colors, x_res, y_res, processor, speed, ram){
	laptop:touchpad = tch;
}

ostream & laptop::show_properties(ostream &stream){
	computer::show_properties(stream);
	stream << "Touchpad:\t" << ((touchpad) ? "yes" : "no") << endl;
	return stream;
}

#pragma region List
class List{
	
public:
	List();
	~List();
	void appendNode(int value);
	void print_all();
	void clean();
	size_t getcount();

private:
	struct ListNode {
		int data;
		ListNode *next;
		ListNode(int value, ListNode *n) : data(value), next(n) {}
	};
	ListNode *first;
	size_t count;

};

List::List() : count(0), first(NULL){
}
List::~List(){
	clean();
}

//Добавление записи в конец списка.
void List::appendNode(int value){
	if (first == NULL){
		first = new ListNode(value, NULL);
		return;
	}
	ListNode *tmp = first;
	while (tmp->next != NULL)
		tmp = tmp->next;
	
	tmp-> next = new ListNode(value, NULL);
	count++;
	 
}

void List::print_all(){
	ListNode *tmp;
	tmp = first;
	size_t i = 1;
	while (tmp != NULL){
		cout << "List[" << i++ << "]: " << tmp->data << endl;
		tmp = tmp->next;
	}
	
}

void List::clean(){
	ListNode *tmp = first;
	while (first != NULL){
		tmp = first->next;
		delete(first);
		first = tmp;
	}
	count = 0;
}

size_t List::getcount(){
	return count;
}
#pragma endregion 

#pragma region TemplateArray
const size_t SIZE = 10;
template <class T>
class _array{
public:
	T element[SIZE];
	_array();
	void add(T value);
	virtual void print_all();
	void clean();
	size_t getcount();
private:
	size_t count;
};

template <class T>
_array<T>::_array(){
	/*for (size_t i = 0; i < SIZE; i++)
		element[i] = NULL;*/
	count = 0;
}

template <class T>
void _array<T>::add(T value){
	if (count == SIZE) {
		cout << "Overflow" << endl;
		return;
	}
	element[count] = value;
	count++;
}

template <class T>
void _array<T>::print_all(){
	cout << "Print all" << endl;
}

template <class T>
void _array<T>::clean(){
	for (size_t i = 0; i < count; i++)
		element[i] = NULL;
	count = 0;
}

template <class T>
size_t _array<T>::getcount(){
	return count;
}
#pragma endregion


class server : public computer, public _array <computer>{
	
public:
	server(char *, int, char *, long, int, int, int, int, int);
	ostream &print_all(ostream &stream);

private:
	char ip[16];
};

server::server(char *ip, int hard_disc, char *screen_type, long colors, int x_res, int y_res, int processor, int speed, int ram) :
computer(hard_disc, screen_type, colors, x_res, y_res, processor, speed, ram)/*, _array<computer>::_array()*/{
	strcpy(server::ip, ip);
}

ostream &server::print_all(ostream &stream){
	for (size_t i = 0; i < getcount(); i++){
		stream << "Comp[" << i + 1 << "]:" << endl;
		element[i].show_properties(stream);
		stream << endl;
	}
	
	return stream;
}

ostream &operator<<(ostream &stream, server serv){
	serv.print_all(stream);
	return stream;
}



int main(){
	//computer my_pc(128, "VGA", 256, 512, 512, 86, 2000, 1024);
	//my_pc.show_properties();
	//cout << endl;

	//server my_server("128.0.0.1", 512, "DVI", 65324, 1920, 1080, 86, 4000, 8192);
	//my_server.show_properties();
	//my_server.add(my_pc);

	//cout << endl;
	//cout << my_server;
	//my_server.print_all();


	

	char ip[65];
	int hard_disc;
	char screen_type[65];
	long colors;
	int x_res;
	int y_res;
	int processor;
	int speed;
	int ram;
	int comp_count;

	char comp_type[10];

	int m_dpi;
	bool tch;
	
	
	
	ifstream in("input.txt");
	if (!in){
		cout << "Can not open file." << endl;
	}
	else{
		in >> ip >> hard_disc >> screen_type >> colors >> x_res >> y_res >> processor >> speed >> ram;
		server serv(ip, hard_disc, screen_type, colors, x_res, y_res, processor, speed, ram);
		
		computer tmpcomp;
		in >> comp_count;
		for (int i = 0; i < comp_count; i++){
			in >> comp_type;
			if (!strcmp(comp_type, "pc")){
				in >> m_dpi >> hard_disc >> screen_type >> colors >> x_res >> y_res >> processor >> speed >> ram;
				tmpcomp = *(new pc(m_dpi, hard_disc, screen_type, colors, x_res, y_res, processor, speed, ram));
				serv.add(tmpcomp);
			}
			if (!strcmp(comp_type, "laptop")){
				in >> tch >> hard_disc >> screen_type >> colors >> x_res >> y_res >> processor >> speed >> ram;
				tmpcomp = *(new laptop(tch, hard_disc, screen_type, colors, x_res, y_res, processor, speed, ram));
				serv.add(tmpcomp);
			}

		}
		cout << "Server: " << endl;
		serv.show_properties(cout);

		cout << endl << serv;
	}

	in.close();

	
	return 0;
}