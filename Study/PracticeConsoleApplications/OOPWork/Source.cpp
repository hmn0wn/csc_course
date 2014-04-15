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



struct ListNode{
	int data;
	ListNode *next;
};

ListNode *appendNode(ListNode *head, int data){
	if (head == NULL){
		head = new ListNode;
		head->data = data;
		head->next = NULL;
	}
	else{
		head->next = appendNode(head->next, data);
	}
	return head;
}

void cleanList(ListNode **head){
	ListNode *iter = *head;
	while (*head!= NULL){
		iter = (*head)->next;
		delete(*head);
		*head = iter;
	}
	*head = NULL;
}


int main(){
	computer my_pc("PC", 128, "VGA", 256, 512, 512, 86, 2000, 1024);
	my_pc.show_properties();

	ListNode *ln = NULL;//Важно обнулить.
	for (size_t i = 0; i < 10; i++)
		ln = appendNode(ln, i);

	ListNode *ln_;
	ln_ = ln;
	size_t i = 1;
	while (ln_ != NULL){
		cout << "ln_[" << i++ << "]: " << ln_->data << endl;
		ln_ = ln_->next;
	}

	cleanList(&ln);
	ln_ = ln;
	i = 1;
	while (ln_ != NULL){
		cout << "ln_[" << i++ << "]: " << ln_->data << endl;
		ln_ = ln_->next;
	}

	return 0;
}