|
vector<int> intersection( 
    const vector<int> &a, vector<int> &b ) {
  vector<int> res;
  res.reserve(min(a.size(), b.size())); // optimize x2
  size_t i = 0;
  b.push_back(INT_MAX); // border, спорный момент
  for (int x : a) {
    while (b[i] < x) // Зачёт по чтению кода =)
      i++;
    if (b[i] == x)
      res.push_back(x);
  }
  return res;
}

|

