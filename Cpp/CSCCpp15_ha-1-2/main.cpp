#pragma GCC optimize ("O2")
#include "haffman.hpp"
#include <iostream>
#include <stdexcept>


using namespace std;



int main(int argc, char *argv[])
{
    try
    {

        if(argc != 6)
        {
            throw std::runtime_error("Wrong argv string.");
        }


        std::string input_file;
        std::string output_file;

        std::string key2 = argv[2];
        if(key2 == "-f" || key2 == "--file")
        {
            input_file = argv[3];
        }
        else
        {
            throw std::runtime_error("Wrong argv string.");
        }

        std::string key3 = argv[4];
        if(key3 == "-o" || key3 == "--output")
        {
            output_file = argv[5];
        }
        else
        {
            throw std::runtime_error("Wrong argv string.");
        }

        std::string key1 = argv[1];
        if(key1 == "-c")
        {

            HaffmanTree htree(input_file, output_file);
            htree.encode();

            return 0;
        }

        if(key1 == "-u")
        {
            HaffmanTree htree_dec(input_file, output_file);
            htree_dec.decode();

            return 0;
        }

        throw std::runtime_error("Wrong argv string.");
    }
    catch(std::runtime_error const &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;

    }

    return 0;
}

