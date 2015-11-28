|1. int n, a[n];
   #define all(a) a,a+n
   sort(all(a)); 
   upper_bound(all(a), R) -
   lower_bound(all(a), L)

2. 
   n + sort()
   b = [(1,2), (2,1), (3,0), (10,3)]
   /** O(n \log n) */

   upper_bound(b, (X, R)) -
   lower_bound(b, (X, L))
   /** \Theta(\log n) */

3. L = 1, R = 1
   while (a[R] < x) // O(logK)
     R *= 2
   /** R < 2K */
   binarySearch(L, R) // O(logK)

Задача:

  deg P = 2*k + 1 
  a[deg P] > 0
  Найти любой корень?
  Бинпоиск
  R = 1, 2, 4, 8, ... P(R)>0
  L = -1, -2, -4, ... P(L)<0
  double
  eps = 1e-15
  L,R = 10^{15}
  //while (R - L > eps)
  while (R - L > max(1, abs(R) + abs(L)) * eps)

    M=(L+R)/2
    (P(M)<0 ? L : R) = M

4. O(N * log max(a_i))
   Бинарный поиск по ответу
   L = 0, R = max(a_i)
   while (R - L > eps)
     M = (L + R) / 2
     if (check(M)) // O(N)
       L = M
     else
       R = M

5. Бинарный поиск по ответу
   sort(xs)
   function check(d)
     last = -infty
     cnt = 0
     for x in xs:
       if x >= last + d:
         last = x
         cnt += 1
     return cnt >= k
   
6. f(i) = (A[i+1]-A[i] < 0)
   Троичный ~= бинарный поиск по производной
   Тернарный поиск

   
|
