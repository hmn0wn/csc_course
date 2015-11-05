#include <iostream>
#include <cstring>
#include <functional>
using namespace std;


char *getline()
{
  unsigned int size = 2;
  char *buf = new char[size+1];
  char *p = buf;

  while(cin.get(*p) && '\n'!=*(p++)){
      if(p-buf == size+1){
         char *tmp = new char[size*2+1];
         memccpy(tmp, buf, 0, size+1);
         swap(buf, tmp);
         p = buf+size+1;
         size *= 2;
         delete [] tmp;
        }
    }
  buf[p-buf] = 0;
  return buf;
}

int _2_6_2()
{
  char *ch = getline();
  cout << ch << endl;
  return 0;
}
