#ifndef _6_1_1_HPP
#define _6_1_1_HPP

#include <cstddef>


template <typename T>
class Array
{

    explicit Array(size_t size = 0, const T& value = T());

    Array(const Array &array_for_copy);

    void swap(Array &array_for_swap);

    ~Array();

    Array& operator=(Array &array_right);

    size_t size() const;

    T& operator[](size_t i);

    const T& operator[](size_t i) const;

private:
    size_t size_;
    T *data_;
};


int _6_1_1();
#endif // 6_1_1_HPP

