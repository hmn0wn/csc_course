#include <iostream>
#include <fstream>
#include <math.h>
// ќценим сверху степенью двойки
#define SIZE 131072

using namespace std;


class segment_tree{
private:
	int garray[SIZE];	
	int tree_array[2*SIZE-1];

public:
	size_t length_garray;
	size_t pow2_length_garray;
	size_t length_tree_array;
	
	segment_tree();
	segment_tree(int *array_, size_t n);
	
	void buildtree();
	int Min(size_t L, size_t R);
	void Set(size_t I, int X);
	void normalize(size_t I);

	ostream &print_garray(ostream &stream);
	
};

segment_tree::segment_tree() :length_garray(0), pow2_length_garray(0), length_tree_array(0){};

/*segment_tree::segment_tree(int *array_, size_t n){
	for (size_t i = 0; i < n; i++)
		garray[i] = array_[i];
	length_garray = n;
}*/
//
//void segment_tree::buildtree(){
//	pow2_length_garray = (size_t)log2(length_garray);
//	size_t new_length_garray = (size_t)pow(2, pow2_length_garray);
//	
//	if (new_length_garray < length_garray) {
//		new_length_garray *= 2;
//		pow2_length_garray++;
//	}
//	
//	//We will build the minimal segment tree, so write the max value of int in the addition tail of garray
//	for (size_t i = length_garray; i < new_length_garray; i++)
//		garray[i] = INT_MAX;
//
//
//
//}
//
//ostream &segment_tree::print_garray(ostream &stream){
//	stream << "garray: ";
//	for (size_t i = 0; i < length_garray; i++)
//		stream << garray[i] << " ";
//	stream << endl;
//	return stream;
//}
//
//ostream &operator<<(ostream &stream, segment_tree s_tree){
//	s_tree.print_garray(stream);
//	return stream;
//}




int main(){
	ifstream in("input.txt");
	int array_[SIZE];
	size_t n, m;
	in >>n >> m;
	for (size_t i = 0; i < n; i++)
		in >> array_[i];

	segment_tree s_tree();
	//cout << s_tree;
	
	in.close();

	
}