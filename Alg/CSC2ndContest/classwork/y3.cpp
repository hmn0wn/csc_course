#include <algorithm>

using namespace std;

struct T {
  int x;
};

typedef bool (* TYPE_NAME)( T, T );

bool cmp( T a, T b ) {
  return a.x < b.x;
}

int main() {
  T a[10];
  TYPE_NAME f = cmp;
  sort(a, a + 10, f);
}
