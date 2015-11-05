#include "5.3.1.hpp"
#include <iostream>

ScopedPtr::ScopedPtr(Expression *ptr = nullptr)
    : ptr_(ptr) {}

ScopedPtr::~ScopedPtr()
{
    delete ptr_;
}

Expression *ScopedPtr::get() const
{
    return ptr_;
}

Expression *ScopedPtr::release()
{
    Expression *tmp_ptr = ptr_;
    ptr_ = nullptr;
    return tmp_ptr;
}

void ScopedPtr::reset(Expression *ptr)
{
    delete ptr_;
    ptr_ = ptr;
}

Expression &ScopedPtr::operator *() const
{
    return *ptr_;
}

Expression *ScopedPtr::operator->() const
{
    return ptr_;
}

int _5_3_1()
{
    Expression *exp = new BinaryOperation(new Number(12),'+', new Number(23));
    ScopedPtr scptr(exp);
    std::cout << exp->evaluate() << std::endl;
    std::cout << scptr.release()->evaluate() << std::endl;

    return 0;
}
