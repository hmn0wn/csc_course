
#include <iostream>
#include <utility>

int _2_3_1() {
  int a = 0, b = 0;
  std::cin >> a >> b;
  while(a>0&&b>0){
    if(a<b) std::swap(a, b);
    a-=b*(a/b);
  }
  std::cout << b;
  return 0;
}
