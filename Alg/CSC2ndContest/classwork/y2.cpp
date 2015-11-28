#include <algorithm>

using namespace std;

struct T {
  int x;

  bool operator < ( const T &b ) const {
    return x > b.x;
  }
};

int main() {
  T a[10];
  sort(a, a + 10);
}
