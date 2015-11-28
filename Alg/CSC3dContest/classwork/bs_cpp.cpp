|
int main() {
  int n = 10, a[n]; // g++
  int i = lower_bound(a, a + n, 3) - a; // >= 3

  int j = lower_bound(a, a + n, 3+1) - a; // > 3
  //int j = upper_bound(a, a + n, 3) - a; // > 3

  // (last <= 3) == (first > 3) - 1
  int j = lower_bound(a, a + n, 3+1) - a - 1; 
}

|

