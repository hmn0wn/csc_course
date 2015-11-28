#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>


using namespace std;

struct Gnome
{
    Gnome(size_t number = 0, size_t lullaby = 0, size_t sleep = 0)
        : lullaby(lullaby)
        , sleep(sleep) {}
    size_t number;
    size_t lullaby;
    size_t sleep;
};

void printvector(Gnome *gnomes, size_t n)
{
    for(int i = 0; i < n; ++i)
      cout << gnomes[i].number << " ";
    cout << endl;

    for(int i = 0; i < n; ++i)
        cout << gnomes[i].lullaby << " ";
    cout << endl;

    for(int i = 0; i < n; ++i)
        cout << gnomes[i].sleep << " ";
    cout << endl;

    for(int i = 0; i < n; ++i)
        cout << gnomes[i].lullaby + gnomes[i].sleep << " ";
    cout << endl;
}


bool comparator_02e(Gnome dl, Gnome dr)
{
    return (dl.lullaby + dl.sleep) > (dr.lullaby + dl.sleep);
}

int _02e()
{
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);

    ifstream in("./../02e_input");
    size_t count = 0;
    size_t sum_of_lullaby = 0;

    //in >> count;
    count = 100000;
    Gnome *gnomes = new Gnome[count]();
    for(size_t i = 0; i < count; ++i)
    {
        gnomes[i].number = i+1;
        //in >> gnomes[i].lullaby;
        gnomes[i].lullaby = 10;
        sum_of_lullaby += gnomes[i].lullaby;
    }

    for(size_t i = 0; i < count; ++i)
    {
        //in >> gnomes[i].sleep;
        gnomes[i].sleep = 1;
    }
    gnomes[1].sleep = 1000000;

    sort(gnomes, gnomes + count, comparator_02e);




    for(size_t i = 0; i < count; ++i)
    {
        sum_of_lullaby -= gnomes[i].lullaby;
        if(sum_of_lullaby >= gnomes[i].sleep)
        {
            cout << i+1 << endl;
            cout << gnomes[i].sleep << endl;
            cout << sum_of_lullaby << endl;

            cout << -1;
            return 0;
        }
    }

    printvector(gnomes, count);


}
