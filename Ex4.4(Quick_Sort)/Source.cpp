#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

#define forn(begin,end) for(size_t i =begin; i<end; i++)

ostream &print(ostream &stream, char label[10], size_t *data, size_t begin, size_t end){
	stream << label << ": ";
	forn(begin,end+1) stream << data[i] << " ";
	stream << endl;
	return stream;
}

void swap(size_t &x, size_t &y){
	size_t tmp = x;
	x = y;
	y = tmp;
}

int partition(size_t *data, int begin, int end){
	
	swap(data[begin], data[rand() % (end - begin+1)]);//Случайный разделитель.
	
	size_t x = data[begin];
	size_t j = begin;

	forn(begin+1,end+1)
	if (data[i] <= x) swap(data[++j], data[i]);

	swap(data[begin], data[j]);

	
	return j;	
}

void q_sort(size_t *data, int begin, int end){
	if (begin >= end) return;

	int middle = partition(data, begin, end);
	cout << "b: " << begin << " m:" << middle << " e:" << end << endl;
	print(cout, " sorting", data, begin, end);
	q_sort(data, begin, middle - 1);
	q_sort(data, middle + 1, end);
}

int main(){
	

	size_t *a;
	for (size_t n = 1; n < 10; n++){
		a = new size_t[n];
		forn(0, n) a[i] = /*rand()%n*/2;
		print(cout, "unsorted", a, 0,n-1);
		q_sort(a, 0, n - 1);
		print(cout, "  sorted", a, 0,n-1);
		cout << endl << endl;
		delete(a);
	}
}