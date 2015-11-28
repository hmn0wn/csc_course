
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <utility>



using namespace std;

struct Point
{
    int coord;
    char type;
    size_t number;

};

void printvector(vector<Point> const &points, size_t n)
{
    for(int i = 0; i < n; ++i)
        cout << points[i].coord << " : " << points[i].type << endl;
    cout << endl;
}


bool comparator_02f(Point pl, Point pr)
{
    if(pl.coord == pr.coord)
    {
        return     (pl.type == 'l' && pr.type == 'p')
                || (pl.type == 'p' && pr.type == 'r')
                || (pl.type == 'l' && pr.type == 'r');
    }
    return pl.coord < pr.coord;
}



int _02f()
{
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);

    ifstream in("./../02f_input");
    size_t n = 0, m = 0;

    in >> n >> m;
    size_t gen_len = 2 * n + m;

    vector<Point> points(gen_len);
    vector<size_t> only_points(m, 0);
    for(size_t i = 0; i < n; ++i)
    {
        int a, b;
        in >> a >> b;

        if(a > b) swap(a, b);
        points[2 * i].coord = a;
        points[2 * i].type = 'l';

        points[2 * i + 1].coord = b;
        points[2 * i + 1].type = 'r';

    }

    for(size_t i = 2 * n; i < 2 * n + m; ++i)
    {
        in >> points[i].coord;
        points[i].type = 'p';
        points[i].number = i - 2 * n;
    }


    printvector(points, gen_len);
    sort(points.begin(), points.end() , comparator_02f);

    size_t counter = 0;
    for(size_t i = 0; i < gen_len; ++i)
    {
        if(points[i].type == 'l') ++counter;
        if(points[i].type == 'r') --counter;
        if(points[i].type == 'p')  only_points[points[i].number] = counter;

    }
    //printvector(points, gen_len);

    for(size_t i = 0; i < m; ++i)
        cout << only_points[i] << " ";
    cout << endl;

    cout << pow(2, 31) - 1 << endl;
}
