#include <iostream>
using namespace std;
void _01C(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  unsigned long long n,sum=0,k=1,k2=1;
  cin >> n;


  while(k2<=n){
      sum+=n/k2;
      ++k;
      k2=k*k;
    }

  cout << sum;

}

