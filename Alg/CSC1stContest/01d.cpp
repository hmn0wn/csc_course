#include <iostream>

using namespace std;

int _01D(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n=0;
  cin >> n;
  long *a = new long[n];
  for(int i = 0; i<n; ++i)
    cin >> a[i];

  for(int i=n-1; i>=0; --i)
    cout << a[i] << " ";

  delete [] a;
  return 0;
}
