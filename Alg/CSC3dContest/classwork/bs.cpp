|
/**
 * lower_bound(x) = min i : a[i] >= x
 * a[n] = +infty
 */

// C++: lower_bound(a.begin(), a.end(), x) - a.begin()
int lowerBound( const vector<int> &a, int x ) {
  int l = 0, r = a.size(); // [l..r] --> [l..r)
  while (l != r) {
    int m = (l + r) >> 1; // round down
    if (a[m] >= x)
      r = m;
    else
      l = m + 1; // +1
  }
  return l; // r
}

// predicate f, f : monotone
// f(a[-1]) = 0
// f(a[n]) = 1
int predicateBorder( const vector<int> &a, function f ) {
  int l = -1, r = a.size(); // f(l) = 0, f(r) = 1
  while (r - l > 1) { // >= 2
    int m = (l + r) >> 1; // round to any side
    // l != m != r
    if (f(a[m])) r = m;
    else         l = m;
  }
  // f(x) == !(x <= y)  =>   last <= y, first > y
  // f(x) == !(x <  y)  =>   last <  y, first >= y
  return l; // r = l + 1, f(a[l]) = 0, f(a[r]) = 1
}

|

