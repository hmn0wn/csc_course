#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>


using namespace std;

static void printvector(vector<int> const &v, size_t n)
{
    for(size_t i = 0; i < n; ++i)
        cout << v[i] << ' ';
    cout << endl;
}


int _03g()
{
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);

    ifstream in("./../03g_input");
    size_t n = 0, k = 0;

    in >> n >> k;
    vector<int> numbers(n);
    set<int> unic;

    for(size_t i = 0; i < n; ++i)
        in >> numbers[i];
    printvector(numbers, n);

    size_t  begin = 0,
            end = 0;

    long long sum = 0;
    unic.insert(numbers[begin]);
    while(end < n)
    {
        if(unic.size() < k)
        {
            ++end;
            if(unic.find(numbers[end]) != unic.end())
                unic.insert(numbers[end]);
        }

    }


    return 0;
}
