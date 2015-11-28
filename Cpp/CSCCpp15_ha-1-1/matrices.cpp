#include <iostream>
#include <utility>
#include <fstream>
#include <stdexcept>
#include "matrices.hpp"

Matrix::Matrix(char const *path)
{
    std::ifstream input(path);
    if(input)
    {
        input >> rows_;
        input >> columns_;

        matrix_ = create_matrix(rows_, columns_);


        for(size_t row = 0; row < rows_; ++row)
        {
            for(size_t column = 0; column < columns_; ++column)
            {
                input >> matrix_[row][column];
            }
        }
    }
    else
    {
        throw std::runtime_error("File can not be opened.");
    }

}

Matrix::Matrix(size_t const rows, size_t const columns)
    : rows_(rows)
    , columns_(columns)
    , matrix_(create_matrix(rows_, columns_)){}

Matrix::Matrix(Matrix const &matrix_for_copy)
    : rows_(matrix_for_copy.rows_)
    , columns_(matrix_for_copy.columns_)
    , matrix_(create_matrix(rows_, columns_))
{
    for(size_t row = 0; row < rows_; ++row)
    {
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
    delete [] matrix_;
}

double * Matrix::operator[](size_t const i)
{
    return matrix_[i];
}

double const * Matrix::operator[](size_t const i) const
{
    return matrix_[i];
}

Matrix &Matrix::operator+= (Matrix const &right_arg)
{

    if(rows_ != right_arg.rows_ || columns_ != right_arg.columns_)
    {
        throw std::runtime_error("Wrong sizes of matrices in += operation.");
    }
    for(size_t row = 0; row < rows_; ++row)
    {
        for(size_t column = 0; column < columns_; ++column)
        {
            matrix_[row][column] += right_arg[row][column];
        }
    }
    return *this;
}

Matrix &Matrix::operator*= (Matrix const &right_arg)
{
    if(columns_ != right_arg.rows_)
    {
        throw std::runtime_error("Wrong sizes of matrices in *= operation.");
    }

    Matrix tmp_matrix(rows_, right_arg.columns_);
    for(size_t row_for_left = 0; row_for_left < rows_; ++row_for_left)
    {
        for(size_t column_for_right = 0; column_for_right < right_arg.columns_; ++column_for_right)
        {
            for(size_t index_for_sum = 0; index_for_sum < columns_ ;++index_for_sum)
            {
                tmp_matrix[row_for_left][column_for_right] += matrix_[row_for_left][index_for_sum] * right_arg[index_for_sum][column_for_right];
            }
        }

    }
    *this = tmp_matrix;
    return *this;

}

size_t Matrix::get_rows_() const
{
    return rows_;
}

size_t Matrix::get_columns_() const
{
    return columns_;
}

Matrix operator+ (Matrix const &left_arg, Matrix const &right_arg)
{
    return Matrix(left_arg) += right_arg;
}

Matrix operator* (Matrix const &left_arg, Matrix const &right_arg)
{
    return Matrix(left_arg) *= right_arg;
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

double **create_matrix(size_t const rows, size_t const columns)
{
    double **matrix = new double *[rows];
    for (size_t row = 0; row < rows; ++row)
    {
        matrix[row] = new double[columns]();
    }

    return matrix;
}
