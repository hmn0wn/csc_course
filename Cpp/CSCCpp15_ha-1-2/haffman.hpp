#ifndef HAFFMAN_HPP
#define HAFFMAN_HPP
#include <cstddef>
//#include <utility>
//#include <algorithm>
#include <unordered_map>
#include <vector>


using namespace std;

struct Node
{
    Node(     uint32_t frequency = 0
            , uint8_t  data = 0
            , Node     *parent = nullptr
            , Node     *left_child = nullptr
            , Node     *right_child = nullptr)

                     : frequency(frequency)
                     , data(data)
                     , code(vector<uint8_t>())
                     , parent(parent)
                     , left_child(left_child)
                     , right_child(right_child)
    {
        code.reserve(30);
    }

    ~Node()
    {
        if(this != nullptr){
            if(this->left_child != nullptr)
                delete this->left_child;

            if(this->right_child != nullptr)
                delete this->right_child;
        }
    }

    uint32_t        frequency;
    uint8_t         data;
    vector<uint8_t> code;
    Node            *parent;
    Node            *left_child;
    Node            *right_child;
};

class HaffmanTree
{
    string   input_path;
    string   output_path;
    uint32_t input_file_byte_size;

    Node    *root;
    uint16_t alphabet;
    uint16_t max_alphabet;
    vector<uint32_t> frequency_table;

    unordered_map<uint8_t, Node *> leaves;


public:
    HaffmanTree(string const &input_path, string const &output_path);
    void create_tree();
    void print_fequency_table();
    void print_haffman_table();
    void create_frequency_table();
    void create_haffman_table();
    void encode();
    void decode();
    void delete_node(Node *node);
    ~HaffmanTree();
};

template <class Type, typename Prior>
class THeap
{
private:

    size_t cur_size;
    size_t max_size;
    Type  *data;
    Prior *priorities;


    void swift_up(size_t it);
    void swift_down(size_t it);
    void swift_up_max(size_t it);
    void swift_down_max(size_t it);

    size_t parent(size_t it);
    size_t left_child(size_t it);
    size_t right_child(size_t it);
    void swap(size_t it1, size_t it2);

public:
    THeap(size_t size);
    ~THeap();
    void insert(Type element, Prior priority);
    void remove(size_t it);
    Type get_min();
    Type extract_min();
    void change_priority(size_t it, Prior priority);
    size_t get_cur_size()
    {
        return cur_size;
    }
};

template <class Type, typename Prior>
void THeap<Type, Prior>::swift_up_max(size_t it)
{
    if(!parent(it) || it < 1)
    {
        return;
    }
    if(priorities[it] > priorities[parent(it)])
    {
        swap(it, parent(it));
        swift_up(parent(it));
    }
}

template <class Type, typename Prior>
void  THeap<Type, Prior>::swift_down_max(size_t it)
{
    if(left_child(it) > cur_size || it < 1)
    {
        return;
    }

    if(left_child(it) == cur_size)
    {
        if(priorities[it] < priorities[left_child(it)])
        {
            swap(it, cur_size);
        }
    }

    if(left_child(it) < cur_size)
    {
        if(priorities[it] < std::max(priorities[left_child(it)], priorities[right_child(it)]))
        {
            if(priorities[left_child(it)] > priorities[right_child(it)])
            {
                swap(it, left_child(it));
                swift_down(left_child(it));
            }
            else
            {
                swap(it, right_child(it));
                swift_down(right_child(it));
            }
        }
    }
}

template <class Type, typename Prior>
void THeap<Type, Prior>::swift_up(size_t it)
{
    if(!parent(it) || it < 1)
    {
        return;
    }
    if(priorities[it] < priorities[parent(it)])
    {
        swap(it, parent(it));
        swift_up(parent(it));
    }
}

template <class Type, typename Prior>
void  THeap<Type, Prior>::swift_down(size_t it)
{
    if(left_child(it) > cur_size || it < 1)
    {
        return;
    }

    if(left_child(it) == cur_size)
    {
        if(priorities[it] > priorities[left_child(it)])
        {
            swap(it, cur_size);
        }
    }

    if(left_child(it) < cur_size)
    {
        if(priorities[it] > std::min(priorities[left_child(it)], priorities[right_child(it)]))
        {
            if(priorities[left_child(it)] < priorities[right_child(it)])
            {
                swap(it, left_child(it));
                swift_down(left_child(it));
            }
            else
            {
                swap(it, right_child(it));
                swift_down(right_child(it));
            }
        }
    }
}

template <class Type, typename Prior>
size_t  THeap<Type, Prior>::parent(size_t it)
{
    return (it / 2);
}

template <class Type, typename Prior>
size_t  THeap<Type, Prior>::left_child(size_t it)
{
    return (it * 2);
}

template <class Type, typename Prior>
size_t  THeap<Type, Prior>::right_child(size_t it)
{
    return (it * 2 + 1);
}

template <class Type, typename Prior>
void  THeap<Type, Prior>::swap(size_t it1, size_t it2)
{
    std::swap(data[it1], data[it2]);
    std::swap(priorities[it1], priorities[it2]);
}

template <class Type, typename Prior>
 THeap<Type, Prior>::THeap(size_t size)
    : cur_size(0), max_size(0)
    , data(new Type[size + 1])
    , priorities(new Prior[size + 1]){}


 template <class Type, typename Prior>
  THeap<Type, Prior>::~THeap()
 {
     delete [] data;
     delete [] priorities;
 }

template <class Type, typename Prior>
void THeap<Type, Prior>::insert(Type element, Prior priority)
{
    data[++cur_size] = element;
    priorities[cur_size] = priority;
    swift_up(cur_size);
}

template <class Type, typename Prior>
void  THeap<Type, Prior>::remove(size_t it)
{
    change_priority(it, 0);
    extract_min();
}

template <class Type, typename Prior>
Type THeap<Type, Prior>::get_min()
{
    return data[1];
}

template <class Type, typename Prior>
Type THeap<Type, Prior>::extract_min()
{
    Type tmp = data[1];
    swap(1,cur_size--);
    swift_down(1);
    return(tmp);
}

template <class Type, typename Prior>
void THeap<Type, Prior>::change_priority(size_t it, Prior priority)
{
    if(priorities[it] > priority)
    {
        priorities[it] = priority;
        swift_up(it);
    }

    if(priorities[it] < priority)
    {
        priorities[it] = priority;
        swift_down(it);
    }
}

void heap_test();

uint8_t byte_vector_to_uint8(vector<uint8_t> const &v);

#endif // HAFFMAN_HPP

