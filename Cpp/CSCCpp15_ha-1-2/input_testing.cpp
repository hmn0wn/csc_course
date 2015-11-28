#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "haffman.hpp"

#include <vector>
#include <string>

#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <cstdint>

using namespace std;

template<class Container>
Container binary_load(std::string const & bin_file_name)
{
    std::ifstream in(bin_file_name,std::ios::binary);
    if (!in) {
        throw std::runtime_error("Could not open \"" + bin_file_name +
            "\" for reading");
    }
    std::noskipws(in); // PON 1
    return Container(std::istream_iterator<std::uint8_t>(in),
                        std::istream_iterator<std::uint8_t>()); //PON 2

}

template<class Container>
void binary_save(Container && data, std::string const & bin_file_name)
{
    std::ofstream out(bin_file_name,std::ios::binary);
    if (!out) {
        throw std::runtime_error("Could not open \"" + bin_file_name +
            "\" for writing");
    }
    std::copy(data.begin(),data.end(),
        std::ostream_iterator<std::uint8_t>(out,"")); // PON 3
}

using namespace  std;

void heap_test()
{

    ifstream in("./../Heap_sort/input.txt");
    fstream out("./../Heap_sort/output.txt");
    size_t n;
    in >> n;

    THeap<Node const *, size_t> NHeap(101);
    Node *nodes = new Node[101]();
    for (size_t i = 1; i <= n; i++)
    {
        in >> nodes[i].data;
        in >> nodes[i].frequency;
        NHeap.insert(nodes + i, nodes[i].frequency);
    }

    Node *tmp;
    for (size_t i = 1; i <= n; i++)
    {
        tmp = const_cast<Node *> (NHeap.extract_min());
        cout << tmp->frequency << " : " << tmp->data << endl;
    }

    cout << endl;

    //Heap myheap;
    THeap<size_t *, size_t> StHeap(101);
    size_t *s_tnodes = new size_t[101]();
    for (size_t n = 1; n < 10; n++)
    {
        for (size_t i = 1; i <= n; i++)
        {
            s_tnodes[i] = (rand() % 100 + 1);
            StHeap.insert(s_tnodes + i, s_tnodes[i]);
            cout << s_tnodes[i] << " ";
        }
        cout << endl;
        for (size_t i = 1; i <= n; i++)
        {
            cout << *StHeap.extract_min() << " ";
        }
        cout << endl << endl;
    }
}

uint32_t change_endiannes(uint32_t value)
{
    uint32_t result = 0;
    result |= (value & 0x000000FF) << 24;
    result |= (value & 0x0000FF00) << 8;
    result |= (value & 0x00FF0000) >> 8;
    result |= (value & 0xFF000000) >> 24;
    return result;
}

void create_input_test()
{

    ofstream out("./../endian_test_input", ios::binary);
    uint32_t tmp = 511;

    out.write(reinterpret_cast<char *>(&tmp), sizeof(tmp));
    out.close();


    ifstream in("./../endian_test_input", ios::binary);
    uint8_t buf[4];

    in.read(reinterpret_cast<char *>(&tmp), sizeof(uint32_t));
    cout << tmp;

    /*in.read(reinterpret_cast<char *>(buf), 4);
    cout << "buf[0]\t: " << (int)buf[0] << endl;
    cout << "buf[1]\t: " << (int)buf[1] << endl;
    cout << "buf[2]\t: " << (int)buf[2] << endl;
    cout << "buf[3]\t: " << (int)buf[3] << endl;*/



}

void input_test()
{
    ifstream in("./../endian_test_input" , ios::binary);
    ofstream out("./../endian_test_output" , ios::binary);

    cout << "non portable version :" << endl;
    uint32_t tmp;
    in.read(reinterpret_cast<char *>(&tmp), 4);
    cout << " <<\t: " << change_endiannes(tmp) << endl;;   // prints 511 on little endian systems
                                        // (or -16711680 on big endian systems)
    out << "write\t: ";
    out.write(reinterpret_cast<char *>(&tmp), 4);
    cout << endl;


    cout << endl << "portable version :" << endl;
    uint8_t b[4]; // use an unsigned type like uint8_t... don't use char
    in.read( reinterpret_cast<char*>(b), 4 );

    cout << "after reading to uint8_t:" << endl;
    cout << "b[0]\t: " << hex << b[0] << endl;
    cout << "b[1]\t: " << hex << b[1] << endl;
    cout << "b[2]\t: " << hex << b[2] << endl;
    cout << "b[3]\t: " << hex << b[3] << endl;

    uint32_t v = b[0] |
                (b[1] << 8) |
                (b[2] << 16) |
                (b[3] << 24);



    cout << " <<\t: " << v << endl;  // now prints 511 regardless of system endianness

    // to write:
    b[0] = (v & 0xFF);
    b[1] = ((v >> 8) & 0xFF);
    b[2] = ((v >> 16) & 0xFF);
    b[3] = ((v >> 24) & 0xFF);

    out << "write\t: ";
    out.write( reinterpret_cast<char*>(b), 4 );
}

