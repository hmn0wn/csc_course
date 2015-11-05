
#ifndef _6_1_3_HPP
#define _6_1_3_HPP

#include <iostream>
struct ICloneable
{
    virtual ICloneable* clone() const = 0;
    virtual ~ICloneable() { }

};


// В шаблоне ValueHolder должен быть определен
// конструктор от одного параметра типа T,
// который инициализирует поле data_.
//
// Шаблон ValueHolder должен реализовывать
// интерфейс ICloneable, и возвращать указатель
// на копию объекта, созданную в куче, из метода
// clone.

template <typename T>
struct ValueHolder : ICloneable// дальше самостоятельно
{
    ValueHolder(T const &value) : data_((T*)(new char[sizeof(T)]))
    {
        new(data_) T();
        std::cout << "constructor" << std::endl;
    }

    ~ValueHolder()
    {
        data_->~T();
        delete [] (char*)(data_);
        std::cout << "destructor" << std::endl;
    }

    ValueHolder *clone() const
    {
        ValueHolder *copy_of_this = new ValueHolder(*(this->data_));
        std::cout << "clone" << std::endl;
        return copy_of_this;
    }

    T *data_;
};

struct TestObject {
    TestObject() : i(0) {
        std::cout << "\t new obj     addr=" << this << std::endl;
    }
    ~TestObject() {
        std::cout << "\t del obj     addr=" << this << std::endl;
    }
    TestObject(const TestObject & a) : i(a.i) {
        std::cout << "\t new copy obj     addr=" << this << std::endl;
    }
    int i;
};

int _6_1_3()
{
    std::cout << "begin of program" << std::endl;
    ValueHolder<TestObject> value_holder(*(new TestObject()));
    ICloneable *clone = value_holder.clone();
    std::cout << "end of program" << std::endl;
}


#endif // _6_1_3_HPP

