
#include <iostream>
#include <utility>

int _2_1_3() {
  int f1 = 0, f2 = 1, m = 1;
  long long n = 0;
  std::cin >> n;
  std::cin >> m;
  for(; n>1; --n){
    f1+=f2;
    //if(f1>=m) f1=f1%m;
    //std::swap(f1, f2);
  }
  std::cout << f2;
  return 0;
}
