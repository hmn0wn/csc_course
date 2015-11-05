#include <iostream>

using namespace std;
#define MAX(x, y, r) {int tx = (x), ty = (y), &tr = (r); tr = tx>ty?tx:ty;}

void _1_8_2()
{
  int a = 10;
  int b = 20;
  int c = 0;
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  cout << "c = " << c << endl;
  MAX(a, b, c); // теперь c равно 20
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  cout << "c = " << c << endl;
  MAX(a += b, b, c); // теперь a = с = 30
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  cout << "c = " << c << endl;

}
