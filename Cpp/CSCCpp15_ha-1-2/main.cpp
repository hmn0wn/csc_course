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
    //HaffmanTree htree("./../tests/empty.0.in", "./../tests/haffman_output_test.bin");

    //HaffmanTree htree("./../tests/haffman_input_test.txt", "./../tests/haffman_output_test.bin");
    //HaffmanTree htree("./../tests/5mb_input", "./../tests/5mb_.archived");
    HaffmanTree htree("./../tests/NCTSLINK2015.csv", "./../tests/NCTSLINK2015.csv.archived");
    //HaffmanTree htree("./../tests/aaaaaaaabaaaaaaa.2.in", "./../tests/aaaaaaaabaaaaaaa.2.in.archived");
    //HaffmanTree htree("./../tests/5M_ff.in", "./../tests/5M_ff.in.archived");
    //HaffmanTree htree("./../tests/aaaaaaaaaaaaaaaa.in", "./../tests/aaaaaaaaaaaaaaaa.in.archived");
    htree.encode();


    clock_t encoding_end = clock();

    //HaffmanTree htree_dec("./../tests/haffman_output_test.bin", "./../tests/haffman_input_test.unarchive");
    //HaffmanTree htree_dec("./../tests/5mb_.archived", "./../tests/5mb_.unarchived");
    HaffmanTree htree_dec("./../tests/NCTSLINK2015.csv.archived", "./../tests/NCTSLINK2015.csv.unarchive");
    //HaffmanTree htree_dec("./../tests/aaaaaaaabaaaaaaa.2.in.archived", "./../tests/aaaaaaaabaaaaaaa.2.in.unarchive");
    //HaffmanTree htree_dec("./../tests/5M_ff.in.archived", "./../tests/5M_ff.in.unarchive");
    //HaffmanTree htree_dec("./../tests/aaaaaaaaaaaaaaaa.in.archived", "./../tests/aaaaaaaaaaaaaaaa.in.unarchive");
    htree_dec.decode();

    cout << endl;
    cout << "encoding: " << ((float)(encoding_end - begin_time))/CLOCKS_PER_SEC << " seconds" << endl;

    clock_t decoding_end = clock();
    cout << "decoding: " << ((float)(decoding_end - encoding_end))/CLOCKS_PER_SEC << " seconds" << endl;

    clock_t end_time = clock() - begin_time;
    end_time;
    true;
    cout << "total: " << ((float)end_time)/CLOCKS_PER_SEC << " seconds" << endl;
    cout << endl;
    return 0;

}

