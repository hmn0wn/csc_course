#ifndef MATRICES_HPP
#define MATRICES_HPP

#include <cstddef>

class Matrix
{
public:
    explicit Matrix(char const *path);
    Matrix(size_t const rows, size_t const columns);
    Matrix(size_t const rows, size_t const columns, double const value);
    Matrix(Matrix const &matrix);
    
    Matrix &operator=(Matrix const &matrix);
    ~Matrix();
    
    void swap(Matrix &matrix);
    double       * operator[] (size_t const i);
    double const * operator[] (size_t const i) const;
    
    Matrix &operator+= (Matrix const &right_arg);
    Matrix &operator*= (Matrix const &right_arg);
    
    
    size_t get_rows_()    const;
    size_t get_columns_() const;

    void print() const;


private:
    size_t rows_;
    size_t columns_;
    double **matrix_;

};

Matrix operator+ (Matrix const &left_arg, Matrix const &right_arg);
Matrix operator* (Matrix const &left_arg, Matrix const &right_arg);

double **create_matrix(size_t const rows, size_t const columns);

#endif // MATRICES_HPP

