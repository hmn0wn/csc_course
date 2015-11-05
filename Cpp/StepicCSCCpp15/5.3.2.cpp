
#include "5.3.2.hpp"
#include <iostream>



SharedPtr::SharedPtr(Expression *ptr = NULL)
    : counter(new size_t(ptr ? 1 : 0))
    , ptr_(ptr) {}

SharedPtr::~SharedPtr()
{

    if(*counter > 1)
    {
        --(*counter);
    }
    else
    {
        delete ptr_;
        delete counter;
    }

}

SharedPtr::SharedPtr(const SharedPtr& sptr_for_copy)
    : counter(&(++(*sptr_for_copy.counter)))
    , ptr_(sptr_for_copy.get()) {}

SharedPtr& SharedPtr::operator=(const SharedPtr& sptr_right)
{
    if(this != &sptr_right)
    {


        if(*counter > 1)
        {
            --(*counter);
        }
        else
        {
            delete ptr_;
            delete counter;
        }

        ptr_ = sptr_right.get();
        ++(*sptr_right.counter);
        counter = sptr_right.counter;

    }

    return *this;
}

Expression *SharedPtr::get() const
{
    return ptr_;
}


void SharedPtr::reset(Expression *ptr)
{

    if(*counter > 1)
    {
         --(*counter);
    }
    else
    {
        delete counter;
        delete ptr_;
    }
    counter = new size_t(1);
    ptr_ = ptr;
}

Expression &SharedPtr::operator *() const
{
    return *ptr_;
}

Expression *SharedPtr::operator->() const
{
    return ptr_;
}

int _5_3_2()
{
    Expression *exp = new BinaryOperation(new Number(12),'+', new Number(23));

    SharedPtr shptr1(exp);
    std::cout << shptr1->evaluate() << std::endl;
    std::cout << *shptr1.counter << std::endl; // 1

    SharedPtr shptr2(shptr1);
    std::cout << *shptr1.counter << std::endl; // 2
    std::cout << *shptr2.counter << std::endl; // 2

    SharedPtr shptr3;
    std::cout << *shptr3.counter << std::endl; // 0
    shptr3 = shptr2;
    std::cout << *shptr1.counter << std::endl; // 3
    std::cout << *shptr2.counter << std::endl; // 3
    std::cout << *shptr3.counter << std::endl; // 3


    return 0;
}
