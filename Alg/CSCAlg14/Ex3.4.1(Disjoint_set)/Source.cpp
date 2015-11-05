#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
using namespace std;

class Disjoint_set{
private:
	struct Node{
		Node *head;
		size_t number;
		Node() : head(this), number(0){}
	};
	size_t N;
	Node *Set;
public:
	Disjoint_set(size_t N);
	size_t Find(size_t num);
	bool Check(size_t numA, size_t numB);
	void Union(size_t numA, size_t numB);
	void PrintHeads();
	
};

Disjoint_set::Disjoint_set(size_t n){
	Disjoint_set::N = n;
	Set = new Node[N+1];
	for (size_t i = 1; i <= N; i++)
		Set[i].number = i;
}

size_t Disjoint_set::Find(size_t num){
	return (Set[num].head == &Set[num]) ? Set[num].number : Find(Set[num].head->number);
}

bool Disjoint_set::Check(size_t numA, size_t numB){
	return Find(numA) == Find(numB) ? true : false;
}

//LOL, чем отличается . от -> ??
void Disjoint_set::Union(size_t numA, size_t numB){
	size_t hA = 1, hB = 1;
	Node *headA = &Set[numA], *headB = &Set[numB];

	while (headA != headA->head){
		hA++;
		headA = headA->head;
	}

	while (headB != headB->head){
		hB++;
		headB = headB->head;
	}

	if (headA == headB) return;
	if (hA < hB)
		headA->head = headB;
	else
		headB->head = headA;
	
}

void Disjoint_set::PrintHeads(){
	cout << "Heads: " << endl;
	for (size_t i = 0; i <= N; i++)
		cout << "Set[" << i << "]: " << this->Find(i) << endl;
	cout << endl;
}

int main(){
	ifstream in("input.txt");
	char command[6];
	bool answers[100000];
	size_t ansiter = 0;
	
	size_t n, m, A,B;
	in >> n >> m;

	Disjoint_set ds(n);
	//cout << "Test init:" << endl;
	//ds.PrintHeads();

	for (size_t i = 0; i < m; i++){
		in >> command >> A >> B;
		if (!strcmp(command, "Check")) answers[ansiter++] = ds.Check(A, B);
		else ds.Union(A, B);
	}

	//ds.PrintHeads();

	//cout << endl << "Aswers:" << endl;
	for (size_t i = 0; i < ansiter; i++)
		cout <</* "ans[" << i << "]: " <<*/ (answers[i] ? "True" : "False" ) << endl;

	


}