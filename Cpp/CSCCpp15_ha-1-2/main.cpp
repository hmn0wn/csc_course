#pragma GCC optimize ("O2")
#include "haffman.hpp"
#include <iostream>
#include <math.h>
#include <time.h>


using namespace std;



int main(int argc, char *argv[])
{
    clock_t begin_time = clock();

    //heap_test();
    //HaffmanTree htree("./../empty.0.in", "./../haffman_output_test.bin");

    //HaffmanTree htree("./../haffman_input_test.txt", "./../haffman_output_test.bin");
    //HaffmanTree htree("./../5mb_input", "./../5mb_.archived");
    HaffmanTree htree("./../NCTSLINK2015.csv", "./../NCTSLINK2015.csv.archived");
    htree.encode();


    clock_t encoding_end = clock();

    //HaffmanTree htree_dec("./../haffman_output_test.bin", "./../haffman_input_test.unarchive");
    //HaffmanTree htree_dec("./../5mb_.archived", "./../5mb_.unarchived");
    HaffmanTree htree_dec("./../NCTSLINK2015.csv.archived", "./../NCTSLINK2015.csv.unarchive");
    htree_dec.decode();

    cout << endl;
    cout << "encoding: " << ((float)(encoding_end - begin_time))/CLOCKS_PER_SEC << " seconds" << endl;

    clock_t decoding_end = clock();
    cout << "decoding: " << ((float)(decoding_end - encoding_end))/CLOCKS_PER_SEC << " seconds" << endl;

    clock_t end_time = clock() - begin_time;
    cout << "total: " << ((float)end_time)/CLOCKS_PER_SEC << " seconds" << endl;
    cout << endl;
    return 0;

}

