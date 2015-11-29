#include "haffman.hpp"
#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, char *argv[])
{

    //heap_test();
    //HaffmanTree htree("./../empty.0.in", "./../haffman_output_test.bin");

    HaffmanTree htree("./../haffman_input_test.txt", "./../haffman_output_test.bin");

    htree.encode();

    return 0;

}

