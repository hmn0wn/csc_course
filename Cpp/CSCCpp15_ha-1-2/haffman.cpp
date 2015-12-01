#include <haffman.hpp>
#include <fstream>
#include <iostream>
#include <bitset>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iomanip>

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

void byte_vector_to_uint8_vector(vector<uint8_t> const &source, vector<uint8_t>  &result)
{
    for(size_t rit = 0; rit < result.size(); ++rit)
    {
        uint8_t byte = source[rit * 8];
        for(size_t i = 1; i < 8; ++i)
        {
            byte = byte << 1;
            if(source[rit * 8 + i])
            {
                byte += 1;
            }
        }
        result[rit] = byte;
    }
}

void printvector(vector<uint8_t> const &v)
{
    for(size_t i = 0; i < v.size(); ++i)
        cout << (size_t)v[i];
    //cout << v.size();
}

void HaffmanTree::print_fequency_table()
{
    uint32_t sum = 0;
    for(size_t i = 0; i <= 255; ++i)
    {
        if(frequency_table[i])
        {
            sum += frequency_table[i];
            cout << " " << bitset<8>(i)
                 << "  "  << (size_t)i
                 << "  '" << (char)i
                 << "'  " << frequency_table[i]
                 << endl;
        }
    }
    cout << endl;

    cout << "freq sum  " << sum << endl;
}

void HaffmanTree::print_haffman_table()
{
    uint32_t sum = 0;
    for(size_t i = 0; i <= 255; ++i)
    {
        if(frequency_table[i])
        {
            sum += frequency_table[i];
            cout << " " << bitset<8>(i)
                 << "  "  << (size_t)i
                 << "  '" << (char)i
                 << "'  " << frequency_table[i]
                 << "   \t";
            printvector(leaves.find(i)->second->code);
            cout << endl;
        }
    }
    cout << endl;
    cout << "alphabet     \t" << (size_t)leaves.size() << endl;
    cout << "freq sum     \t" << sum << endl << endl;
}




HaffmanTree::HaffmanTree(string input_path, string output_path)
    : input_path(input_path)
    , output_path(output_path)
    , input_file_byte_size(0)
    , root(nullptr)
{
    for(size_t i = 0; i <= 255; ++i)
    {
        frequency_table[i] = 0;
    }
}

void HaffmanTree::create_frequency_table()
{
    ifstream in(input_path, ios_base::binary);

    uint8_t  buf = 0;

    while(in.read(reinterpret_cast<char *>(&buf), sizeof(buf)))
    {
        ++input_file_byte_size;
        frequency_table[(size_t)buf] +=1;
    }
}

void HaffmanTree::create_tree()
{


    //Create Haffman Tree
    THeap<Node *, uint32_t> theap(511);
    for(size_t i = 0; i <= 255; ++i)
    {
        if(frequency_table[i])
        {
            leaves.insert(pair<uint8_t, Node *>(i, new Node(frequency_table[i], i)));
            theap.insert(leaves.find(i)->second, leaves.find(i)->second->frequency);
        }
    }


    Node *parent = nullptr;
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
        parent = new Node(left->frequency + right->frequency, 0 , nullptr, left, right);
        left->parent = parent;
        right->parent = parent;

        theap.insert(parent, parent->frequency);

    }

    root = parent;

    //cout << "root : " << root->frequency << endl;
    //cout << "file_size : " << file_size << endl;

}

void HaffmanTree::create_haffman_table()
{
    for(unordered_map<uint8_t, Node *>::iterator mit = leaves.begin(); mit != leaves.end(); ++mit)
    {
        Node *it = mit->second;

        while(it->parent != nullptr)
        {
            if(it == it->parent->left_child)
            {
                mit->second->code.insert(mit->second->code.begin(), 0);
            }
            else
            {
                if(it == it->parent->right_child)
                {
                    mit->second->code.insert(mit->second->code.begin(), 1);
                }
                else
                {
                    cout << "Codes table error in node." << endl;
                }
            }
            it = it->parent;
        }
    }
}

void HaffmanTree::encode()
{
    cout << "encoding :" << endl << endl;
    create_frequency_table();
    create_tree();
    create_haffman_table();
    print_haffman_table();

    ifstream in(input_path, ios_base::binary);
    ofstream out(output_path, ios_base::binary);
    uint16_t table_byte_size = 0;
    uint32_t data_byte_size = 0;

    //cout << "saving the freq table:" << endl;
    uint32_t alphabet = leaves.size();
    out.write(reinterpret_cast<char *>(&alphabet), sizeof(alphabet));
    table_byte_size += 4;

    for(unordered_map<uint8_t, Node *>::iterator mit = leaves.begin(); mit != leaves.end(); ++mit)
    {
        out.write(reinterpret_cast<char *>(&mit->second->data), sizeof(mit->second->data));
        //cout << hex << (size_t)mit->second->data << " : " << hex << mit->second->frequency << endl;
        out.write(reinterpret_cast<char *>(&mit->second->frequency), sizeof(mit->second->frequency));
        table_byte_size += 5;

    }

    uint8_t                   byte_to_encode = 0;
    vector<uint8_t>           buf(8);
    vector<uint8_t>::iterator buf_it = buf.begin()
                            , buf_end = buf.end()
                            , buf_begin = buf.begin();
    //vector<uint8_t>           result(buf.size()/8);

    vector<uint8_t>::const_iterator code_it;

    while(in.read(reinterpret_cast<char *>(&byte_to_encode), sizeof(byte_to_encode)))
    {
        vector<uint8_t> &cur_code = leaves.find(byte_to_encode)->second->code;
        vector<uint8_t>::const_iterator code_end = cur_code.end();
        code_it = cur_code.begin();

        //cout << byte_to_encode << " : ";
        //printvector(cur_code);

        while(code_it < code_end)
        {
            *buf_it = *code_it;
            ++buf_it;
            ++code_it;

            if(code_it == code_end && in.peek() == EOF)
            {
                fill(buf_it, buf_end, 0);
                buf_it = buf_end;
            }

            if(buf_it == buf_end)
            {
                uint8_t byte = byte_vector_to_uint8(buf);
                out.write(reinterpret_cast<char *>(&byte), sizeof(byte));
                //cout << " byte:" << bitset<8>(byte);
                //byte_vector_to_uint8_vector(buf, result);
                //out.write(reinterpret_cast<char *>(&result.at(0)), 512/8);
                ++data_byte_size;
                buf_it = buf_begin;
            }
        }
        //cout << endl;
    }
     cout << endl  << "infile size  \t" << input_file_byte_size << endl;
     cout << "table size  \t" << table_byte_size << endl;
     cout << "data size  \t" << data_byte_size << endl;
     cout <<  "outfile size  \t" << data_byte_size + table_byte_size << endl;
     cout << endl << "PROFIT  \t" <<100 - (data_byte_size + table_byte_size) * 100 / input_file_byte_size << " %" << endl << endl;
}

void HaffmanTree::decode()
{
    cout << "decoding :" << endl << endl;


    ifstream in(input_path, ios_base::binary);
    ofstream out(output_path, ios_base::binary);

    uint16_t table_byte_size = 0;
    uint32_t data_byte_size = 0;
    uint32_t output_file_byte_size = 0;

    //cout << "saving the freq table:" << endl;
    uint32_t alphabet = 0;
    in.read(reinterpret_cast<char *>(&alphabet), sizeof(alphabet));

    if(alphabet == 1)
    {
        uint8_t byte = 0;
        uint32_t frequency = 0;

        in.read(reinterpret_cast<char *>(&byte), sizeof(byte));
        in.read(reinterpret_cast<char *>(&frequency), sizeof(frequency));
        table_byte_size += 5;

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
            in.read(reinterpret_cast<char *>(frequency_table + byte), sizeof(uint32_t));
            table_byte_size += 5;

        }

        create_tree();
        create_haffman_table();
        print_haffman_table();

        uint8_t                   byte_to_decode = 0;

        vector<uint8_t>::const_iterator code_it;
        Node                           *tree_it = root;

        while(in.read(reinterpret_cast<char *>(&byte_to_decode), sizeof(byte_to_decode)))
        {
            //cout  << endl <<  "code: " << bitset<8>(byte_to_decode) << endl;

            ++data_byte_size;
            for(size_t i = 0; i < 8; ++i)
            {
                uint8_t end_bit = byte_to_decode - ((byte_to_decode >> 1) << 1);
                byte_to_decode = byte_to_decode >> 1;
                //cout  << (size_t)end_bit;
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
                    //cout  << endl << "decoded: " << bitset<8>(tree_it->data) << endl;
                    tree_it = root;
                }

           }
        }
        input_file_byte_size = table_byte_size + data_byte_size;

    }
    cout << endl << endl << "infile size  \t" << input_file_byte_size << endl;
    cout << "table size  \t" << table_byte_size << endl;
    cout << "data size  \t" << data_byte_size << endl;
    cout << "outfile size  \t" << output_file_byte_size << endl;
}


void HaffmanTree::delete_node(Node *node)
{
    if(node != nullptr){
        if(node->left_child != nullptr)
            delete_node(node->left_child);

        if(node->right_child != nullptr)
            delete_node(node->right_child);

        delete node;
    }
}

HaffmanTree::~HaffmanTree()
{
     delete_node(root);     
}



