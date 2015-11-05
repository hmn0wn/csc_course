#include <iostream>
using namespace std;

int _1_8_5()
{
    /* ... */

    char c = '\0';
    bool space = 0;
    while (cin.get(c)) {
        if(c!=' ') {
            if(space) {space = false; cout << ' '; }
            cout << c;
        }
        else space = true;
    }

        return 0;
}
