
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


int _03d()
{
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);

    ifstream in("./../03d_input");
    size_t n = 0, k = 0;

    in >> n >> k;
    vector<int> ropes(n);


    for(size_t i = 0; i < n; ++i)
        in >> ropes[i];
    printvector(ropes, n);


    return 0;
}
