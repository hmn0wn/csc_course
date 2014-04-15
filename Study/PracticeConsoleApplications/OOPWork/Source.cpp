#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

class comp_component{
public:
	virtual void show_properties() = 0;
};

class computer_screen : public comp_component{
public:
	computer_screen(char *, long, int, int);
	void show_properties(void);

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

void computer_screen::show_properties(void){
	cout << "Type of screen:\t" << type << endl;
	cout << "Colors:\t" << colors << endl;
	cout << "Resolution:\t" << x_resolution << " x " << y_resolution << endl;
}

class mother_board : public comp_component{
public:
	mother_board(int, int, int);
	void show_properties(void);

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

void mother_board::show_properties(void){
	cout << "Processor:\t" << processor << endl;
	cout << "Speed:\t" << speed << " Mz" << endl;
	cout << "RAM:\t" << RAM << " Mb" << endl;
}

class computerObj :public computer_screen, public mother_board{
public:
	computerObj(char *, int, char *, long, int, int, int, int, int);
	void show_properties();
private:
	char name[64];
};

/*computerObj::computerObj(char *name, char *screen_type, long colors, int x_res, int y_res, int processor, int speed, int ram) :
computer_screen(screen_type, colors, x_res, y_res), mother_board(processor, speed, ram){
	strcpy(computerObj::name, name);
	
}
*/

class computer : public computer_screen, public mother_board{

public:
	computer(char *, int, char *, long, int, int, int, int, int);
	void show_properties(void);

private:
	char name[64];
	int hard_disc;
	
};

computer::computer(char *name, int hard_disc, char *screen_type, long colors, int x_res, int y_res, int processor, int speed, int ram) :
computer_screen(screen_type, colors, x_res, y_res), mother_board(processor, speed, ram){
	strcpy(computer::name, name);
	computer::hard_disc = hard_disc;
	
}

void computer::show_properties(void){
	cout << "Type of computer:\t" << name << endl;
	cout << "Hard drive:\t" << hard_disc << endl;
	computer_screen::show_properties();
	mother_board::show_properties ();
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
	T element[SIZE];
	size_t count;
public:
	_array(){
		for (size_t i = 0; i < count; i++)
			element[i] = NULL;
		count = 0;
	}
	void add(T value);
	void print_all();
	void clean();
	
};

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
#pragma endregion


int main(){
	computer my_pc("PC", 128, "VGA", 256, 512, 512, 86, 2000, 1024);
	my_pc.show_properties();
	cout << endl;
	
	List mylist;
	_array<int> myarray;
	

	for (size_t i = 0; i < 10; i++){
		mylist.appendNode(i);
		myarray.add(i);
	}


	mylist.print_all();
	mylist.clean();
	mylist.print_all();

	cout << endl;

	myarray.print_all();
	myarray.clean();
	myarray.print_all();


	return 0;
}