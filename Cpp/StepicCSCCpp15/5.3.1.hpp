#ifndef HPP531
#define HPP531
#include "exp.hpp"

struct Expression;
struct Number;
struct BinaryOperation;

struct ScopedPtr
{
    // реализуйте следующие методы:

    explicit ScopedPtr(Expression *ptr);
    ~ScopedPtr();
    Expression *get() const;
    Expression *release();
    void reset(Expression *ptr = 0);
    Expression &operator*() const;
    Expression *operator->() const;


private:
    // запрещаем копирование ScopedPtr
    ScopedPtr(const ScopedPtr&);
    ScopedPtr& operator=(const ScopedPtr&);

    Expression *ptr_;
};

int _5_3_1();
#endif // HPP531

