#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string.h>
using namespace std;

//Базовый, абстрактный класс, содержит только один чисто виртуальный метод, 
//символизирующий абстрактный компоненте в составе компьютера.

class comp_component{
public:
	virtual ostream &show_properties(ostream &stream) = 0;//Подобное определение и есть пример динамического полиморфизма.
};

//Наследник базового класса, содержит определение виртуальной функции предка,
//которая выводит в поток значения полей класса.
//Класс символизирует монитор компьютера, содержит поля: тип, колличество цветов,
//и разрешение.
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

//Второй наследник базового класса, содержит определение виртуальной функции(аналогичное),
//Символизирует материнскую плату компьютера, содержит поля: тип процессора, 
//частота процессора, объем опереативной памяти; содержит процедуру вывода параметров.
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

//Класс компьютера, являет собой результат множественного наследования от классов:
//материнской платы и монитора, содержит в себе все их поля и аналогичную процедуру
//вывода параметров в поток, которая доопределяется; она определена в базовом классе
//как виртуальная функция
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

//Более узкий класс, обычный пк, наследуется от компьютера, добавлено одно поле, и немного
//доопределена процедура вывода.
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

//Аналогично только лаптоп.
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

//Не нужнет.
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

//Шаблонный класс обобщенного массива.
#pragma region TemplateArray
const size_t SIZE = 10;// Максимальное число элементов массива, архитектурно вынужденное решение, определяется пользователем в коде программы
//никак не контроллируется извне программы, ибо должно быть определено еще на этапе компилляции, причина тому — статический массив.
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

//Апогей творения, сервер, наследуется от массива и компьютера;
//наследование от компьютера дает поля и метод вывода полей;
//наследование от массива(с уточнением типа, на компьютер) дает поле типа массива
//и методы для работы с этим полем; это поле может содержать как пк так и лаптопы, ибо класс предок у них 
//один и он же и уточняет тип на этапе наследования;


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

//Ксасс сервер прегружает метод массива отвечающий за вывод в поток параметров всех содержащихся в нем классав,
//классов типа компьютера, а именно лаптопы и пк, которые в свою очередь имеют собственные методы вывода информации
//в поток stream.
ostream &server::print_all(ostream &stream){
	for (size_t i = 0; i < getcount(); i++){
		stream << "Comp[" << i + 1 << "]:" << endl;
		element[i].show_properties(stream);
		stream << endl;
	}
	
	return stream;
}

//Перегрузка оперетора вывода в поток, из стандартной библиотеки ввода вывода <iostream>.
//За основу берется уже реализованный метод вывода в поток у всех реализованных классов.
//Это обстоятельсто гарантируется виртуальным методом базового абстрактного класса.
ostream &operator<<(ostream &stream, server serv){
	serv.print_all(stream);
	return stream;
}



void main(int argc, char *argv[]){
	if (argc == 2 && !strcmp(argv[1], "help")){
		/*cout << "Запуск программы происходит при использовании параметра командной стрки \"run\"" << endl;
		cout << "Данные для демонстрационного примера берутся из файла input.txt." << endl;
		cout << "В первой строке данные для заполнения полей сервера, он один, определен программно." << endl;
		cout << "Во второй колличесто компьютеров для ввода в сервер, не должно превосходить SIZE." << endl;
		cout << "Далее следуют текстовые специффикаторы pc и laptop." << endl;
		cout << "А за ними соответствеющие данные." << endl;*/

		cout << endl << endl << "\tATTENTION!!!" << endl;
		cout << "Run occurs when you use the command line \" run \"" << endl;
		cout << "Data for the demo, taken from the file input.txt" << endl;
		cout << "The first line of data to populate the server, server is defined in program code" << endl;
		cout << "The second Nuber computers for input to the server, should not exceed SIZE" << endl;
		cout << "Followed by text parameters pc and laptop" << endl;
		cout << "And behind them the relevant data" << endl;
		cout << endl;
	}
	else if (argc == 2 && !strcmp(argv[1], "run")){


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

			//Далее следует заполнение сервера компьютерами.
			//Это классический пример динамического полиморфизма, посылки к такому его применению положены
			//в классе компьютер который является предком классов пк и лаптоп.
			//По текстовому специффикатору происходит заполнение массива соответствующими элементами, тип которых
			//выбирается динамически, но насмотря на это --->
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
			//--->несмотря на это, метод для вывода разнотипных элементов один и тот же,
			//он реализован еще в классе предке, в компьютере, а объявлен как виртуальный, еще в базовом
			//классе
			cout << endl << serv;
		}

		in.close();
	}
	
	
}