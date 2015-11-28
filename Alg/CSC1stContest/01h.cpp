#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void printvector(vector <short> v, size_t N){
  for(char i=0; i<N; ++i)
    cout << v[N-i-1] << " ";
  cout << endl;
}

void generate(vector <short> v, size_t N, size_t i, size_t sum){
  for(size_t j = 1; j<=N; ++j){
    v[i] = j;
    sum+=j;
    if(sum<N) {generate(v,N,i,sum); generate(v,N,++i,sum);}
    else if(sum == N) {printvector(v, i); break;}
      else break;
    }
}

int _01H(){

  ios_base::sync_with_stdio(0);
  cin.tie(0);
  size_t N = 0;
  cin >> N;

  vector <short> v(N,0);
  generate(v,N,0,0);


}
