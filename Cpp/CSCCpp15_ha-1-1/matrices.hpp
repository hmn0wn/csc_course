#ifndef MATRICES_HPP
#define MATRICES_HPP

#include <cstddef>

class Matrix
{
public:
    Matrix(size_t rows, size_t columns);
    Matrix(size_t rows, size_t columns, double value);
    Matrix(Matrix const &matrix);
    
    Matrix &operator=(Matrix const &matrix);
    ~Matrix();
    
    void swap(Matrix &matrix);
    double       * const operator[] (size_t i);
    double const * const operator[] (size_t i) const;
    
    Matrix &operator+= (Matrix const &matrix_right_arg);
    Matrix operator+  (Matrix const &matrix_right_arg) const;
    //Matrix &operator*= (Matrix const &matrix_right_arg);
    Matrix operator*  (Matrix const &matrix_right_arg) const;
    

    void print() const;

private:
    size_t rows_;
    size_t columns_;
    double **matrix_;

};

#endif // MATRICES_HPP

