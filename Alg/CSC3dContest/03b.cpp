#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

static void printvector(vector<size_t> const &v, size_t n)
{
    for(size_t i = 0; i < n; ++i)
        cout << v[i] << ' ';
    cout << endl;
}

int _03b()
{
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);

    ifstream in("./../03b_input");
    size_t n = 0, k = 0;

    in >> n >> k;
    vector<size_t> first_list(n);
    vector<size_t> second_list(k);

    for(size_t i = 0; i < n; ++i)
        in >> first_list[i];

    for(size_t i = 0; i < k; ++i)
        in >> second_list[i];



    for(vector<size_t>::iterator it = second_list.begin(); it < second_list.end(); ++it)
    {
        if(binary_search(first_list.begin(), first_list.end(), *it))
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }

    }

    return 0;
}

