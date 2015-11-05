
#ifndef HPP532
#define HPP532
#include "exp.hpp"

struct SharedPtr
{
    // реализуйте следующие методы:

    explicit SharedPtr(Expression *ptr);
    ~SharedPtr();
    SharedPtr(const SharedPtr&);
    SharedPtr& operator=(const SharedPtr&);
    Expression* get() const;

    void reset(Expression *ptr = 0);
    Expression& operator*() const;
    Expression* operator->() const;



    size_t *counter;
private:
    Expression *ptr_;
};

int _5_3_2();

#endif // HPP532
