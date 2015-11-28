#include <algorithm>

using namespace std;

int main() {
  int a[10];
  sort(a, a + 10);

  vector<int> b(10);
  sort(b.begin(), b.end());
}
