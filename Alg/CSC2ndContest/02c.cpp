#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>


using namespace std;

void printvector(vector <int> v, int n);

long long product(vector<int> first_vector, vector<int> second_vector, size_t length)
{
    long long sum = 0;
    for(size_t i = 0; i < length; ++i)
        sum += (long long)first_vector[i]*second_vector[i];
    return sum;
}

bool comparator02c(int a, int b )
{
    return (a > b);
}


int _02c()
{
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);

    ifstream in("./../02c_input");
    size_t t = 0, n = 0;
    size_t const max_length = 8e2;

    in >> t;

    vector<int> first_vector(800, -100000);
    vector<int> second_vector(800, -100000);
    cout << "Case #" << 0 << ": " << product(first_vector, second_vector, 800) << endl;



    for(size_t case_ = 0; case_ < t; ++case_)
    {
        in >> n;
        for(size_t j = 0; j < n; ++j)
            in >> first_vector[j];
        for(size_t j = 0; j < n; ++j)
            in >> second_vector[j];

        sort(first_vector.begin(), first_vector.begin() + n);
        sort(second_vector.begin(), second_vector.begin() + n, comparator02c);

        printvector(first_vector, n);
        printvector(second_vector, n);

        cout << "Case #" << case_ + 1 << ": " << product(first_vector, second_vector, n) << endl;

    }


    cout << pow(2,8*sizeof(long long)-1) << " " << 8e2 << endl;

    return 0;
}
