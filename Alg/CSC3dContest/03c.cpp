#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>



using namespace std;

bool lower_predicate(int a, int b)
{
    return a >= b;
}

bool upper_predicate(int a, int b)
{
    return !(a <= b);
}

size_t lower_bound_(vector<int> const &v, int x)
{
    size_t l = 0, r = v.size();

    while (l < r)
    {
        int m = (l + r) >> 1;
        if(x <= v[m])
            r = m;
        else
            l = m + 1;
    }
    return l;
}
size_t upper_bound_(vector<int> const &v, int x)
{
    size_t l = 0, r = v.size();

    while (l < r)
    {
        int m = (l + r) >> 1;
        if(v[m] <= x)
            l = m + 1;
        else
            r = m;
    }
    return l;
}

size_t border_predicate(vector<int> const &v, int val, bool (*pred)(int a, int b))
{
    size_t l = 0, r = v.size();
    while(l < r)
    {
        size_t m = (l + r) >> 1;
        if(pred(v[m], val))
            r = m;
        else
            l = m +1;
    }
    return l;
}

int _03c()
{
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);

    ifstream in("./../03c_input");
    size_t n = 0, k = 0;

    in >> n;
    vector<int> numbers(n + 1);
    numbers[n] = numeric_limits<int>::max();

    for(size_t i = 0; i < n; ++i)
        in >> numbers[i];

    sort(numbers.begin(), numbers.end());

    in >> k;
    size_t l = 0, r = 0;
    for(size_t i = 0; i < k; ++i)
    {
        in >> l >> r;
        cout << upper_bound_(numbers, r) - lower_bound_(numbers, l) << " ";

        cout <<   (border_predicate(numbers, r, upper_predicate)
                 - border_predicate(numbers, l, lower_predicate))  << " ";
        cout << "vs STL search ";
        cout <<  (search(numbers.begin(), numbers.end(), &r, &r+1, upper_predicate)
                - search(numbers.begin(), numbers.end(), &l, &l+1, lower_predicate))  << " ";

        cout << endl;
    }

    cout << endl;


    return 0;
}

