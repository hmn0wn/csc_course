#include <haffman.hpp>
#include <fstream>
#include <iostream>
#include <bitset>
#include <map>
#include <vector>

using namespace std;

void printvector(vector<uint8_t> const &v)
{
    for(size_t i = 0; i < v.size(); ++i)
        cout << (size_t)v[i];
    //cout << v.size();
}

void HaffmanTree::print_fequency_table()
{
    uint32_t sum = 0;
    for(uint8_t i = 0; i < 255; ++i)
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
    cout << "alphabet : " << (size_t)alphabet << endl;
    cout << "freq sum : " << sum << endl;
}

void HaffmanTree::print_haffman_table()
{
    uint32_t sum = 0;
    for(uint8_t i = 0; i < 255; ++i)
    {
        if(frequency_table[i])
        {
            sum += frequency_table[i];
            cout << " " << bitset<8>(i)
                 << "  "  << (size_t)i
                 << "  '" << (char)i
                 << "'  " << frequency_table[i]
                 << "\t" <<  codes[i]
                 << "\t";
            printvector(codes_.find(i)->second);
            cout << endl;
        }
    }
    cout << endl;
    cout << "alphabet : " << (size_t)alphabet << endl;
    cout << "freq sum : " << sum << endl;
}

HaffmanTree::HaffmanTree(string input_path, string output_path)
    : input_path(input_path)
    , output_path(output_path)
    , alphabet(0)
    , root(nullptr)
{
    for(uint8_t i = 0; i < 255; ++i)
    {
        nodes[i] = nullptr;
        frequency_table[i] = 0;
        haffman_table[i] = 0;
    }
}

void HaffmanTree::create_tree()
{
    ifstream in(input_path);
    ofstream out(output_path);

    uint32_t byte_size = 0;
    uint8_t  buf = 0;

    while(in.read(reinterpret_cast<char *>(&buf), sizeof(buf)))
    {
        ++byte_size;
        frequency_table[(size_t)buf] +=1;
    }

    //Create Haffman Tree
    THeap<Node *, uint32_t> theap(511);
    for(uint8_t i = 0; i < 255; ++i)
    {
        if(frequency_table[i])
        {
            nodes[alphabet] = new Node(frequency_table[i], i);
            theap.insert(nodes[alphabet], nodes[alphabet]->frequency);
            alphabet++;

        }
    }


    Node *left   = nullptr;
    Node *right  = nullptr;
    Node *parent = nullptr;

    while(theap.get_cur_size())
    {
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
    //print_fequency_table();
    cout << "root : " << root->frequency << endl;
    cout << "bute size : " << byte_size << endl;
}

void HaffmanTree::create_table()
{
    for(uint8_t current_character= 0; current_character< alphabet; ++current_character)
    {
        Node *it = nodes[current_character];
        codes_.insert(pair<uint8_t, vector<uint8_t>>(it->data, vector<uint8_t>()));
        //pair<uint8_t, vector<uint8_t>> pair(it->data, vector<uint8_t>());
        //cout << "map: " << (size_t)(codes_.begin()->first) << " " << (size_t)(it->data) << endl;
        //cout << "pair: " << (size_t)(pair.first) << " " << (size_t)(it->data) << endl;

        while(it->parent != nullptr)
        {
            if(it == it->parent->left_child)
            {
                codes[nodes[current_character]->data].push_back('0');
                vector<uint8_t> &vit = codes_.find(nodes[current_character]->data)->second;
                //cout << "map[" << (size_t)nodes[current_character]->data << "] : " << (size_t)codes_.find(nodes[current_character]->data)->first << endl;
                vit.insert(vit.begin(), 0);
                /*cout << "map[" << (size_t)nodes[current_character]->data << "].second_size : "
                     << codes_.find(nodes[current_character]->data)->second.size()<< endl;*/
            }
            else
            {
                if(it == it->parent->right_child)
                {
                    codes[nodes[current_character]->data].push_back('1');
                    vector<uint8_t> &vit = codes_.find(nodes[current_character]->data)->second;
                    vit.insert(vit.begin(), 1);
                    /*cout << "map[" << (size_t)nodes[current_character]->data << "].second_size : "
                         << codes_.find(nodes[current_character]->data)->second.size()<< endl;*/
                }
                else
                {
                    cout << "Codes table error in " << current_character << " node." << endl;
                }
            }
            it = it->parent;
        }
    }
}

void HaffmanTree::encode(){}

void HaffmanTree::decode(){}

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



