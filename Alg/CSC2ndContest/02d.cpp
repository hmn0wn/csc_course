#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;

/*string appendix(string const &str, size_t size)
{
    size_t str_size = 0;
    char tmp[size+1];

    while(str_size < size/2){
        memcpy(tmp + str_size, str.c_str(), str.size());
        str_size += str.size();
    }

    memcpy(tmp + str_size, tmp, size - str_size);
    tmp[size] = 0;

    return string(tmp);
}

bool comparator_02d(string a, string b)
{

    if(a.size() > b.size()){
        b = appendix(b, a.size());
    }

    if(a.size() < b.size()){
       a = appendix(a, b.size());
    }

    cout << a << " > " << b << " = " << (a > b) << endl;
    if (a > b);

}*/

/*bool comparator_02d(string const &a, string const &b)
{
    if(a.size() == b.size()) return a > b;

    size_t min_length = (a.size() < b.size()) ? a.size() : b.size();
    string a_(a, 0, min_length), b_(b,0, min_length);
    string a_app(a, min_length, a.size()), b_app(b,min_length, b.size());

    cout << a << " > " << b << " : " << endl;

    if (a_ > b_){
        cout  << "\t" << a_ << " > " << b_ << " = " << (a_ > b_) << endl;
        return 1;
    }
    else if( a_ == b_)
    {
        cout << "\t"<< a_ << "  == " << b_ << " = " << (a_ == b_) << endl;
        if( a.size() > b.size() )
        {
            cout << "\t\t" << a_app << " > " << b_ << " = " << (a_app > b_) << endl;
            return (a_app > b_);
        }
        else
        {
            cout << "\t\t" << a_ << " > " << b_app << " = " << (a_ > b_app) << endl;
            return (a_ > b_app);
        }
    }

    return 0;

}*/

bool comparator_02d(string a, string b)
{
    if(a.size() == b.size()) return a > b;

    size_t min_length = (a.size() < b.size()) ? a.size() : b.size();
    string a_(a, 0, min_length), b_(b,0, min_length);
    string a_app(a, min_length, a.size()), b_app(b,min_length, b.size());

    cout << "a: " << a.capacity() << endl;
    cout << "b: " << b.capacity() << endl;
    cout << "a_: " << a_.capacity() << endl;
    cout << "b_: " << b_.capacity() << endl;
    cout << "a_app: " << a_app.capacity() << endl;
    cout << "b_app: " << b_app.capacity() << endl;

    cout << a << " > " << b << " : " << endl;

    if (a_ > b_){
        cout  << "\t" << a_ << " > " << b_ << " = " << (a_ > b_) << endl;
        return 1;
    }
    else if( a_ == b_)
    {
        cout << "\t"<< a_ << " == " << b_ << " = " << (a_ == b_) << endl;
        if( a.size() > b.size() )
        {
            cout << "\t\t" << a_app << " > " << b_ << " = " << (a_app > b_) << endl;
            return comparator_02d(a_app, b_);
        }
        else
        {
            cout << "\t\t" << a_ << " > " << b_app << " = " << (a_ > b_app) << endl;
            return comparator_02d(a_, b_app);
        }
    }

    cout  << "\t" << a_ << " > " << b_ << " = " << (a_ > b_) << endl;
    return 0;

}


void printvector(vector <string> const &v, int n)
{
  for(int i = 0; i < n; ++i)
    cout << v[i] << "\n";
  cout << endl;
}


int _02d()
{
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);

    ifstream in("./../02d_input");
    size_t const max_length = 1e2+1;
    vector<string> pieces(max_length);
    size_t size = 0;


    while (in)
    {
        in >> pieces[size++];
    }

    printvector(pieces, size);
    sort(pieces.begin(), pieces.begin() + size-1, comparator_02d);

    printvector(pieces, size);
    return 0;
}
