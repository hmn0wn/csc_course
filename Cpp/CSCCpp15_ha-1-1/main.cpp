#include "matrices.hpp"
#include <string>
#include <iostream>
#include <stdexcept>

int main(int argc, char **argv)
{
    try{
        if(argc < 2 || argc % 2)
        {
            throw std::runtime_error("Wrong argv string.");
        }

        std::string const add_op("--add");
        std::string const mul_op("--mult");

        Matrix result(argv[1]);

        for(size_t operation = 2; operation < (size_t)argc; operation += 2)
        {
            if(argv[operation] == add_op)
            {
                result += Matrix(argv[operation + 1]);
            }
            else
            {
                if(argv[operation] == mul_op)
                {
                    result *= Matrix(argv[operation + 1]);
                }
                else
                {
                    throw std::runtime_error("Wrong one command in argv string.");
                }
            }
        }

        result.print();
       
    }
    catch(std::runtime_error const &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }


    return 0;
}
