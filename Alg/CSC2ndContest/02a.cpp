#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Bus
{
    Bus(size_t number = 0, size_t volume = 0) : number(number), volume(volume) {}

    size_t number;
    size_t volume;
};


void printvector(vector <Bus> v, int n)
{
  for(int i=0; i < n; ++i)
    cout << v[i].number << " ";
  cout << endl;
}

void printvector(vector <int> v, int n)
{
  for(int i=0; i < n; ++i)
    cout << v[i] << " ";
  cout << endl;
}

bool comparator(Bus a, Bus b)
{
    return (a.volume > b.volume);
}

int _02a()
{


    //ios_base::sync_with_stdio(0);
    //cin.tie(0);

    int n = 0, m = 0, sum = 0;

    ifstream in("./../02a_input");
    in >> n >> m;

    vector<Bus> buses(m);
    vector<int> answer;
    for(int i = 0; i < m; ++i)
    {
        in >> buses[i].volume;
        buses[i].number = i+1;
        sum += buses[i].volume;
    }

    if (sum < n) {
        cout << -1 << endl;
        return 0;
    }

    printvector(buses, m);
    sort(buses.begin(), buses.end(), comparator);
    printvector(buses, m);

    int i = 0;
    while(i < m && n > 0)
    {
        n -= buses[i].volume;
        answer.push_back(buses[i].number);
        ++i;
    }

    cout << answer.size() << endl;
    printvector(answer, answer.size());

    return 0;
}

