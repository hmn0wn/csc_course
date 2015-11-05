
#include <iostream>
#include <utility>
#include "matrices.hpp"

Matrix::Matrix(size_t rows, size_t columns)
    : rows_(rows)
    , columns_(columns)
    , matrix_(new double*[rows])
{
    for(size_t row = 0; row<rows; ++row)
        matrix_[row] = new double[columns]();
}

 Matrix::Matrix(size_t rows, size_t columns, double value)
     : rows_(rows)
     , columns_(columns)
     , matrix_(new double*[rows])
 {
     for(size_t row = 0; row < rows; ++row)
     {
         matrix_[row] = new double[columns]();
         for(size_t column = 0; column < columns_; ++column)
         {
             matrix_[row][column] = value;
         }
     }

 }

Matrix::Matrix(Matrix const &matrix_for_copy)
    : rows_(matrix_for_copy.rows_)
    , columns_(matrix_for_copy.columns_)
    , matrix_(new double*[rows_])
{
    for(size_t row = 0; row < rows_; ++row)
    {
        matrix_[row] = new double[columns_];
        for(size_t column = 0; column < columns_; ++column)
        {
            matrix_[row][column] = matrix_for_copy[row][column];
        }
    }
}

void Matrix::swap(Matrix &matrix)
{
    std::swap(rows_, matrix.rows_);
    std::swap(columns_, matrix.columns_);
    std::swap(matrix_, matrix.matrix_);
}

Matrix &Matrix::operator=(Matrix const &matrix)
{
    if(this != &matrix)
    {
        Matrix(matrix).swap(*this);
    }
    return *this;
}

Matrix::~Matrix()
{
    for(size_t row = 0; row < rows_; ++row)
    {
        delete [] matrix_[row];
    }
}

double * const Matrix::operator[](size_t i)
{
    return matrix_[i];
}

double const *const Matrix::operator[](size_t i) const
{
    return matrix_[i];
}

Matrix &Matrix::operator+= (Matrix const &matrix_right_arg)
{
    //Добавить проверку размера матрицы аргумента
    for(size_t row = 0; row < rows_; ++row)
    {
        for(size_t column = 0; column < columns_; ++column)
        {
            matrix_[row][column] += matrix_right_arg[row][column];
        }
    }
    return *this;
}

Matrix Matrix::operator+  (Matrix const &matrix_right_arg) const
{
    return Matrix(*this)+=matrix_right_arg;
}

Matrix Matrix::operator* (Matrix const &matrix_right_arg) const
{
    //Добавить проверку размера матрицы аргумента
    Matrix tmp_matrix(rows_, matrix_right_arg.columns_);
    for(size_t row_for_right = 0; row_for_right < rows_; ++row_for_right)
    {
        for(size_t column_for_left = 0; column_for_left < columns_; ++column_for_left)
        {
            for(size_t column_for_sum = 0; column_for_sum < columns_; ++column_for_sum)
            {
                (tmp_matrix[row_for_right][column_for_left]) += matrix_[row_for_right][column_for_sum] * matrix_right_arg[column_for_sum][column_for_left];
            }
        }
        
    }
    return tmp_matrix;
}

void Matrix::print() const
{
    std::cout << rows_ << std::endl;
    std::cout << columns_ << std::endl;
    for(size_t row = 0; row < rows_; ++row)
    {
        for(size_t column = 0; column < columns_; ++column)
        {
            std::cout << matrix_[row][column] << ' ';
        }
        std::cout << std::endl;
    }
}
