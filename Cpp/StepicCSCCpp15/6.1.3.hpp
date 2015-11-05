#ifndef _6_1_3_HPP
#define _6_1_3_HPP
struct ICloneable
{
    virtual ICloneable* clone() const = 0;
    virtual ~ICloneable() { }

};

// Шаблон ValueHolder с типовым параметром T,
// должен содержать одно открытое поле data_
// типа T.
//
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
    ValueHolder(T const &value);
    ~ValueHolder();
    T *clone() const;

    T *data_;
};


int _6_1_3();

#endif // _6_1_3_HPP

