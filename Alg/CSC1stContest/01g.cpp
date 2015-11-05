#include <iostream>

using namespace std;

int _01G(){
  unsigned long long n,m;

  cin >> n >> m;
  unsigned long long *c = new unsigned long long[n+1];

  c[0] =1;
  unsigned long long cj = 0, m2=m*m;
  for(size_t j=1; j<=n; ++j){
    cj = 0;
    for(size_t i=0; i<j; ++i){
      cj += c[i]*c[j-i-1];
      if(cj>=m2) cj-=m2;
    }
    c[j] = cj%m;
    //cout << c[j] << endl;
    }
  cout << c[n]%m;

}
