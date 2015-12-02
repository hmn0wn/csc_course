#include <fstream>
#include <iostream>
#include <vector>
#include "haffman.hpp"

using namespace std;

uint8_t byte_vector_to_uint8(vector<uint8_t> const &v)
{
    uint8_t result = v[v.size() - 1];
    for(size_t i = 2; i <= v.size(); ++i)
    {
        result = result << 1;
        if(v[v.size() - i])
        {
            result += 1;
        }
    }
    return result;
}

HaffmanTree::HaffmanTree(string const &input_path, string const &output_path)
    : input_path(input_path)
    , output_path(output_path)
    , input_file_byte_size(0)
    , root(nullptr)
    , alphabet(0)
    , max_alphabet(256)

{
    frequency_table.resize(max_alphabet, 0);
    codes.resize(max_alphabet, nullptr);
}

void HaffmanTree::create_frequency_table()
{
    ifstream in(input_path, ios_base::binary);
    uint8_t  buf = 0;

    while(in.read(reinterpret_cast<char *>(&buf), sizeof(buf)))
    {
        ++input_file_byte_size;
        if(!frequency_table[(size_t)buf])
        {
            ++alphabet;
        }
        frequency_table[(size_t)buf] +=1;
    }
}

void HaffmanTree::create_tree()
{
    THeap<Node *, uint32_t> theap(max_alphabet * 2);
    for(size_t cur_byte = 0; cur_byte < max_alphabet; ++cur_byte)
    {
        if(frequency_table[cur_byte])
        {
            Node *cur_node = new Node(frequency_table[cur_byte], cur_byte);
            theap.insert(cur_node, frequency_table[cur_byte]);
        }
    }



    while(theap.get_cur_size())
    {
        Node *left   = nullptr;
        Node *right  = nullptr;

        if(theap.get_cur_size() == 1)
        {
            root = theap.extract_min();
            break;
        }

        left  = theap.extract_min();
        right = theap.extract_min();

        root = new Node(left->frequency + right->frequency, 0, left, right);
        theap.insert(root, root->frequency);

    }



}

void HaffmanTree::create_haffman_table_recursive(Node* cur_node, vector<uint8_t> *cur_code, size_t it = 0)
{
    if(cur_node)
    {

        if(cur_node->left_child && cur_node->right_child)
        {
            cur_code->at(it) = 0;
            create_haffman_table_recursive(cur_node->left_child, cur_code, it + 1);


            cur_code->at(it) = 1;
            create_haffman_table_recursive(cur_node->right_child, cur_code, it + 1);
        }
        else
        {
            codes[cur_node->data] = new vector<uint8_t>(cur_code->begin(), cur_code->begin() + it);

        }
    }
}

void HaffmanTree::encode()
{
    create_frequency_table();


    ifstream in(input_path, ios_base::binary);
    ofstream out(output_path, ios_base::binary);
    uint16_t table_byte_size = 0;
    uint32_t data_byte_size = 0;

    if(input_file_byte_size)
    {
        out.write(reinterpret_cast<char *>(&alphabet), sizeof(alphabet));
        table_byte_size += 2;

        if(alphabet == 1)
        {
            uint16_t byte = 0;
            while(!frequency_table[byte])
            {
                ++byte;
            }

            out.write(reinterpret_cast<char *>(&frequency_table[byte]), sizeof(frequency_table[byte]));
            out.write(reinterpret_cast<char *>(&byte), sizeof(byte));
            data_byte_size += 1;
            table_byte_size += 4;


        }
        else
        {


            create_tree();

            vector <uint8_t>  *init_code = new vector<uint8_t>(max_alphabet/2);
            init_code->reserve(max_alphabet);
            create_haffman_table_recursive(root, init_code);
            delete init_code;


            for(uint16_t it = 0; it < max_alphabet; ++it)
            {
                if(frequency_table[it])
                {
                    out.write(reinterpret_cast<char *>(&it), sizeof(uint8_t));
                    out.write(reinterpret_cast<char *>(&frequency_table[it]), sizeof(uint32_t));
                    table_byte_size += 5;

                }

            }

            uint8_t                   byte_to_encode = 0;
            vector<uint8_t>           buf(8);


            size_t  buf_it = 0
                  , buf_end = buf.size();

            size_t code_it = 0;

            while(in.read(reinterpret_cast<char *>(&byte_to_encode), sizeof(byte_to_encode)))
            {

                vector<uint8_t> &cur_code = *codes[byte_to_encode];
                size_t           code_end = cur_code.size();
                code_it = 0;

                while(code_it < code_end)
                {
                    buf[buf_it] = cur_code[code_it];
                    ++buf_it;
                    ++code_it;

                    if(code_it == code_end && in.peek() == EOF)
                    {
                        fill(buf.begin() + buf_it, buf.end(), 0);
                        buf_it = buf_end;
                    }

                    if(buf_it == buf_end)
                    {
                        uint8_t byte = byte_vector_to_uint8(buf);
                        out.write(reinterpret_cast<char *>(&byte), sizeof(byte));
                        ++data_byte_size;
                        buf_it = 0;
                    }
                }

            }
        }
    }
    cout << input_file_byte_size << endl;
    cout << data_byte_size << endl;
    cout << table_byte_size << endl;

}

void HaffmanTree::decode()
{
    ifstream in(input_path, ios_base::binary);
    ofstream out(output_path, ios_base::binary);

    uint16_t table_byte_size = 0;
    uint32_t data_byte_size = 0;
    uint32_t output_file_byte_size = 0;
    uint32_t freq_sum = 0;


    in.read(reinterpret_cast<char *>(&alphabet), sizeof(alphabet));
    table_byte_size += 2;

    if(alphabet == 1)
    {
        uint32_t frequency = 0;
        uint8_t  byte = 0;

        in.read(reinterpret_cast<char *>(&frequency), sizeof(frequency));
        in.read(reinterpret_cast<char *>(&byte), sizeof(byte));
        data_byte_size += 1;
        table_byte_size += 4;

        for(size_t i = 0; i < frequency; ++i)
        {
            out.write(reinterpret_cast<char *>(&byte), sizeof(byte));
            ++output_file_byte_size;
        }

    }
    else
    {
        for(size_t i = 0; i < alphabet; ++i)
        {
            uint8_t byte = 0;

            in.read(reinterpret_cast<char *>(&byte), sizeof(byte));
            in.read(reinterpret_cast<char *>(&frequency_table[byte]), sizeof(uint32_t));
            freq_sum += frequency_table[byte];
            table_byte_size += 5;

        }

        create_tree();

        vector <uint8_t>  *init_code = new vector<uint8_t>(max_alphabet/2);
        init_code->reserve(max_alphabet);
        create_haffman_table_recursive(root, init_code);
        delete init_code;



        uint8_t byte_to_decode = 0;
        Node    *tree_it = root;

        while(in.read(reinterpret_cast<char *>(&byte_to_decode), sizeof(byte_to_decode)))
        {
            ++data_byte_size;
            for(size_t i = 0; i < 8; ++i)
            {
                uint8_t end_bit = byte_to_decode - ((byte_to_decode >> 1) << 1);
                byte_to_decode = byte_to_decode >> 1;

                if(end_bit)
                {
                    tree_it = tree_it->right_child;
                }
                else
                {
                    tree_it = tree_it->left_child;
                }

                if(tree_it->left_child == nullptr || tree_it->right_child == nullptr)
                {
                    out.write(reinterpret_cast<char *>(&tree_it->data), sizeof(tree_it->data));
                    ++output_file_byte_size;
                    if(output_file_byte_size == freq_sum)
                    {
                        break;
                    }

                    tree_it = root;
                }

           }
        }

        input_file_byte_size = table_byte_size + data_byte_size;

    }
    cout << data_byte_size << endl;
    cout << output_file_byte_size << endl;
    cout << table_byte_size << endl;
}

HaffmanTree::~HaffmanTree()
{
     delete root;
    for(size_t it = 0; it < max_alphabet; ++it)
    {
        delete codes[it];
    }
}



