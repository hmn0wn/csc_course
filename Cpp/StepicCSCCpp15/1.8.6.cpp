#include <iostream>
using namespace std;

int _log(int x)
{
    int tmp = 1;
    int count = 0;
    while(x>=tmp){
        tmp = tmp << 1;
        ++count ;
      }
    return --count;
}

int _1_8_6() {
  int n = 0, x = 0;
  cin >> n;
  for(int i=0; i<n; ++i)
  {
      cin >> x;
      cout << _log(x) << endl;
  }

  return 0;
}
