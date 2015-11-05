#include <iostream>
#include <functional>
using namespace std;

void rotate(int a[], unsigned size, int shift)
{
  int real_shift = shift % size;
  int *b = new int[size];
  for(unsigned int i = 0; i<size; ++i)
    b[i] = a[i];

  for(unsigned int i = 0; i<size; ++i)
    a[i] = b[(i+real_shift)%size];

  delete [] b;
}


int _2_3_1()
{
  int a[] = {1,2,3,4,5};
  for(int i=0;i<5; ++i)
    cout << a[i]  << endl;
  cout << endl;

  rotate(a,5,3);
  for(int i=0;i<5; ++i)
    cout << a[i] << endl;
}
