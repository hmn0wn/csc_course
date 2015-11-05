#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int _01I(){

  //ios_base::sync_with_stdio(0);
  //cin.tie(0);

  ifstream in("D:\\pgm\\Qt\\Tools\\QtCreator\\bin\\CSC1stContest\\input");

  size_t n=0;
  in >> n;

  vector<unsigned short> collection(n,0);
  for(size_t i=0; i<n; ++i)
    in >> collection[i];

  for(size_t i=0; i<n; ++i)
    cout << collection[i] << " ";

  cout << endl;
  sort(collection.begin(), collection.end());

  for(size_t i=0; i<n; ++i)
    cout << collection[i] << " ";

  size_t count = 0;
  for(size_t i=0; i<n-1; ++i)
    if(collection[i] != collection[i+1]) ++count;
  cout << endl;
  cout << 15000 - count-1 << endl;
}

