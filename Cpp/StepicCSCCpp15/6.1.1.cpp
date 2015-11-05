
#include <cstddef>
#include <utility>
#include <new>
#include <cstring>
#include <iostream>

template <typename T>
class Array
{
public:
    // Список операций:
    //
    // explicit Array(size_t size = 0, const T& value = T())
    //   конструктор класса, который создает
    //   Array размера size, заполненный значениями
    //   value типа T. Считайте что у типа T есть
    //   конструктор, который можно вызвать без
    //   без параметров, либо он ему не нужен.
    explicit Array(size_t size = 0, const T& value = T())
        //: size_(size), data_(new T[size_]())
        : size_(size)
    {

        data_ = (T*)(new char[size_*sizeof(T)]);
        for(size_t i = 0; i < size_; ++i)
        {
            new(data_ + i) T(value);
            //std::cout << "[" << i << "] = value" << std::endl;
            //data_[i] = value;
            //memcpy(data_ + i, &value, sizeof(T));
        }
    }

    //
    // Array(const Array &)
    //   конструктор копирования, который создает
    //   копию параметра. Считайте, что для типа
    //   T определен оператор присваивания.
    Array(const Array &array_for_copy)
        //: size_(array_for_copy.size_), data_(new T[size_]())
        : size_(array_for_copy.size_)
    {

        data_ = (T*)(new char[size_*sizeof(T)]);
        for(size_t i = 0; i < size_; ++i)
        {
            new(data_ + i) T(array_for_copy[i]);
            //std::cout << "[" << i << "] = value" << std::endl;
            //data_[i] = value;
            //memcpy(data_ + i, &value, sizeof(T));
        }
    }

    void swap(Array &array_for_swap)
    {
        std::swap(size_, array_for_swap.size_);
        std::swap(data_, array_for_swap.data_);
    }

    //
    // ~Array()
    //   деструктор, если он вам необходим.
    ~Array()
    {
        for(size_t i = 0; i < size_; ++i)
            data_[i].~T();
        operator delete ((char*)data_);
    }

    //
    // Array& operator=(...)
    //   оператор присваивания.
    Array& operator=(Array &array_right)
    {
        if(this != &array_right){
            Array tmp = Array(array_right);
            tmp.swap(*this);

        }
    }

    //
    // size_t size() const
    //   возвращает размер массива (количество
    //                              элементов).
    size_t size() const
    {
        return size_;
    }
    //
    // T& operator[](size_t)
    T& operator[](size_t i)
    {
        return data_[i];
    }

    // const T& operator[](size_t) const
    //   две версии оператора доступа по индексу.
    const T& operator[](size_t i) const
    {
        return data_[i];
    }
private:
    size_t size_;
    T *data_;
};

struct TstObj {
    TstObj() : i(0) {
        std::cout << "\t new obj     addr=" << this << std::endl;
    }
    ~TstObj() {
        std::cout << "\t del obj     addr=" << this << std::endl;
    }
    TstObj(const TstObj & a) : i(a.i) {
        std::cout << "\t new copy obj     addr=" << this << std::endl;
    }
    int i;
};

int _6_1_1()
{
    std::cout << "start of program" << std::endl;
    typedef Array<size_t> ArS_t;
    typedef Array<TstObj> ArTest;


    ArTest artest1(3);
    std::cout << "end of program" << std::endl;


}
