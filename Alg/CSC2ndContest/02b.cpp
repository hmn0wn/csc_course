#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Team
{
    Team(size_t number = 0, size_t score = 0, size_t penalty = 0)
        : number(number), score(score), penalty(penalty) {}

    size_t number;
    size_t score;
    size_t penalty;
};


void printvector(vector <Team> v, int n)
{
  for(int i=0; i < n; ++i)
    cout << v[i].number << " ";
  cout << endl;
}

bool comparator(Team a, Team b)
{
    if(a.score != b.score) return (a.score > b.score);
    else
    {
        if(a.penalty != b.penalty) return (a.penalty < b.penalty);
        else
        {
            return (a.number < b.number);
        }
    }

}

int _02b()
{
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    int n = 0;

    ifstream in("./../02b_input");
    in >> n;

    vector<Team> teams(n);

    for(int i = 0; i < n; ++i)
    {
        teams[i].number = i+1;
        in >> teams[i].score;
        in >> teams[i].penalty;
    }

    printvector(teams, n);
    sort(teams.begin(), teams.end(), comparator);
    printvector(teams, n);

    return 0;
}
