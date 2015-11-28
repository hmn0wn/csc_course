#include "haffman.hpp"
#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, char *argv[])
{

    //heap_test();
    HaffmanTree htree("./../haffman_input_test.txt", "./../haffman_output_test.bin");
    //HaffmanTree htree("./../empty.0.in", "./../haffman_output_test.bin");
    htree.create_tree();
    htree.create_table();
    htree.print_haffman_table();

    cout << "longlong : " << sizeof(long long) * 8 << endl;
    return 0;

}

