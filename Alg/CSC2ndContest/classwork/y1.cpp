#include <algorithm>

using namespace std;

struct T {
  int x;
};

bool operator < ( const T &a, const T &b ) {
  return a.x > b.x;
}

int main() {
  T a[10];
  sort(a, a + 10);
}
