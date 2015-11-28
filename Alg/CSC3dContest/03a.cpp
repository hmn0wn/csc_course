#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int _03a()
{
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);

    ifstream in("./../03a_input");
    size_t n = 0, m = 0;

    in >> n;
    vector<size_t> first_list(n);
    for(size_t i = 0; i < n; ++i)
        in >> first_list[i];

    in >> m;
    vector<size_t> second_list(m);
    for(size_t i = 0; i < m; ++i)
        in >> second_list[i];

    sort(first_list.begin(), first_list.end());
    sort(second_list.begin(), second_list.end());



    size_t counter = 0;
    vector<size_t>::iterator first_it = first_list.begin();
    vector<size_t>::iterator second_it = second_list.begin();
    while(first_it < first_list.end() && second_it < second_list.end())
    {
        if(*first_it < *second_it) ++first_it;
        if(*first_it > *second_it) ++second_it;
        if(*first_it == *second_it)
        {
            ++counter;
            ++second_it;
        }
    }

    cout << counter;
    return 0;
}
