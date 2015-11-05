
#include <iostream>

void generate(int *v, int n, int left, int min = 0, int i = 0){
    if (left < 0 || min == n) return;
    v[i] = min;
    if (min != 0) generate(v, n,left - min, min, i + 1);
    generate(v, n, left - 1, min + 1, i);
    if (left == 0)
    {
        for (int j = 0; j <= i; ++j)
            std::cout << v[j] << (j != i ? ' ' : '\n');
    }

}
int _01H_(){
    int n, v[40];
    std::cin >> n;
    generate(v,n,n);
}
