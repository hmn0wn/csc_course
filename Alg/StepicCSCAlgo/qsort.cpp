
#include <iostream>
#include <cstddef>
#include <algorithm>
using namespace std;

class Array_{
private:
  size_t size_;
  int *data_;
public:
  Array_():size_(0), data_(NULL)();
  Array_(size_t size):size_(size), data_(new int[size]);
  Array_(Array_ &a){
    size_ = a.size_;
    delete [] data_;
    data_ = new int[size_];
    memcpy(data_, a.data_, size_*sizeof(int));
  }
  swap(Array_ &x, Array_ &y){
    swap(x.size_, y.size_);
    swap
  }
};


void Qsort(int *first, int *last){
  if(last-first == 2);


}
