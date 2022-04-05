#include "Matrix.hpp"
#include <stdexcept>
using namespace std;
vector<vector<double>> insert_val(std::vector<double> vec, size_t rows, size_t columns)
{
    if (rows < 0 || columns < 0)
    {
        throw invalid_argument("can't have negative row or col");
    }
    if (rows % 1 != 0 || columns % 1 != 0)
    {
        throw invalid_argument("rows and columns must be int number");
    }
    vector<vector<double>> mat(rows, vector<double>(columns));
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            size_t index = (i * columns) + j;
            double num = vec[index];
            mat[i][j] = num;
        }
    }
    return mat;
}
size_t matrix_sum(const vector<vector<double>> &mat)
{

    size_t sum = 0;
    for (size_t i = 0; i < mat.size(); i++)
    {
        for (size_t j = 0; j < mat[0].size(); j++)
        {
            sum += mat[i][j];
        }
    }
    return sum;
}
int check_positive(int num){
if (num< 0)
        {
            throw invalid_argument("can't have negative row or col");
        }
        return num;
}
namespace zich
{
    Matrix::Matrix(std::vector<double> vec, int rows, int columns):Matrix(vec,static_cast<size_t>(check_positive(rows)),static_cast<size_t>(check_positive(columns))){}
    Matrix::Matrix(std::vector<double> vec, size_t rows, size_t columns)
    {
        if (rows % 1 != 0 || columns % 1 != 0)
        {
            throw invalid_argument("rows and columns must be int number");
        }
        if(rows*columns > vec.size()){
            throw invalid_argument("not enough size for matrix");
        }
        
        this->rows = rows;
        this->columns = columns;
        this->Mat = insert_val(vec, rows, columns);
    }
    Matrix::Matrix(size_t rows, size_t columns)
    {
        if (rows < 0 || columns < 0)
        {
            throw invalid_argument("can't have negative row or col");
        }
        if (rows % 1 != 0 || columns % 1 != 0)
        {
            throw invalid_argument("rows and columns must be int number");
        }
        this->rows = rows;
        this->columns = columns;
        this->Mat.assign(rows, vector<double>(columns));
    }
    bool Matrix::operator!=(const Matrix &other) const
    {
        if (this->rows != other.rows || this->columns != other.columns)
        {
            return true;
        }
        for (size_t i = 0; i < other.rows; i++)
        {
            for (size_t j = 0; j < other.rows; j++)
            {
                if (this->Mat[i][j] != other.Mat[i][j])
                {
                    return true;
                }
            }
        }
        return false;
    }
    bool Matrix::operator==(const Matrix &other) const
    {
        if (this->rows != other.rows || this->columns != other.columns)
        {
            return false;
        }
        for (size_t i = 0; i < other.rows; i++)
        {
            for (size_t j = 0; j < other.rows; j++)
            {
                if (this->Mat[i][j] != other.Mat[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    Matrix Matrix::operator*=(const Matrix &other)
    {
        if (this->columns != other.rows)
        {
            throw invalid_argument("in order to multiply two matrix has to be same size of columns an rows");
        }
        vector<vector<double>> mat(this->rows, vector<double>(other.columns));
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < other.columns; j++)
            {
                size_t sum = 0;
                for (size_t k = 0; k < this->columns; k++)
                {
                    sum += this->Mat[i][k] * other.Mat[k][j];
                }
                mat[i][j] = sum;
            }
        }
        this->Mat.assign(this->rows, vector<double>(other.columns));
        this->Mat.swap(mat);
        return *this;
    }
    bool Matrix::operator<(const Matrix &other) const
    {
        size_t sum_other = matrix_sum(other.Mat);
        size_t sum_self = matrix_sum(Mat);
        if (sum_self < sum_other)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool Matrix::operator<=(const Matrix &other) const
    {
        size_t sum_other = matrix_sum(other.Mat);
        size_t sum_self = matrix_sum(Mat);
        if (sum_self <= sum_other)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool Matrix::operator>(const Matrix &other) const
    {
        size_t sum_other = matrix_sum(other.Mat);
        size_t sum_self = matrix_sum(Mat);
        if (sum_self > sum_other)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool Matrix::operator>=(const Matrix &other) const
    {
        size_t sum_other = matrix_sum(other.Mat);
        size_t sum_self = matrix_sum(Mat);
        if (sum_self >= sum_other)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    Matrix Matrix::operator*(const Matrix &other)
    {
        if (this->columns != other.rows)
        {
            throw invalid_argument("in order to multiply two matrix has to be same size of columns an rows");
        }
        Matrix multi_mat(this->rows, other.columns);
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < other.columns; j++)
            {
                size_t sum = 0;
                for (size_t k = 0; k < this->columns; k++)
                {
                    sum += this->Mat[i][k] * other.Mat[k][j];
                }
                multi_mat.Mat[i][j] = sum;
            }
        }
        return multi_mat;
    }
    Matrix Matrix::operator++()
    {
        Matrix mat(this->rows, this->columns);
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                mat.Mat[i][j] = Mat[i][j] + 1;
            }
        }
        return mat;
    }
    Matrix Matrix::operator--()
    {
        Matrix mat(this->rows, this->columns);
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                mat.Mat[i][j] = Mat[i][j] - 1;
            }
        }
        return mat;
    }
    Matrix Matrix::operator+()
    {
        Matrix mat(this->rows, this->columns);
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                if (Mat[i][j] < 0)
                {
                    mat.Mat[i][j] = Mat[i][j] * (-1);
                }
                else
                {
                    mat.Mat[i][j] = Mat[i][j];
                }
            }
        }
        return mat;
    }
    Matrix Matrix::operator-()
    {
        Matrix mat(this->rows, this->columns);
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < columns; j++)
            {
                if (Mat[i][j] > 0)
                {
                    mat.Mat[i][j] = Mat[i][j] * (-1);
                }
                else
                {
                    mat.Mat[i][j] = Mat[i][j];
                }
            }
        }
        return mat;
    }
    Matrix Matrix::operator+=(const Matrix &other)
    {
        if (this->columns != other.columns || this->rows != other.rows)
        {
            throw invalid_argument("in order to multiply two matrix has to be same size of columns an rows");
        }
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < this->columns; j++)
            {
                Mat[i][j] += other.Mat[i][j];
            }
        }
        return *this;
    }
    Matrix Matrix::operator+(const Matrix &other)
    {
        if (this->columns != other.columns || this->rows != other.rows)
        {
            throw invalid_argument("in order to multiply two matrix has to be same size of columns an rows");
        }
        Matrix sum_mat(this->rows, this->columns);
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < this->columns; j++)
            {
                sum_mat.Mat[i][j] = Mat[i][j] + other.Mat[i][j];
            }
        }
        return sum_mat;
    }
    Matrix Matrix::operator-(const Matrix &other)
    {
        if (this->columns != other.columns || this->rows != other.rows)
        {
            throw invalid_argument("in order to multiply two matrix has to be same size of columns an rows");
        }
        Matrix sum_mat(this->rows, this->columns);
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < this->columns; j++)
            {
                sum_mat.Mat[i][j] = Mat[i][j] - other.Mat[i][j];
            }
        }
        return sum_mat;
    }
    Matrix Matrix::operator-=(const Matrix &other)
    {
        if (this->columns != other.columns || this->rows != other.rows)
        {
            throw invalid_argument("in order to multiply two matrix has to be same size of columns an rows");
        }
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < this->columns; j++)
            {
                Mat[i][j] -= other.Mat[i][j];
            }
        }
        return *this;
    }
    Matrix operator*(double scalar, const Matrix &mat)
    {
        Matrix sum_mat(mat.rows, mat.columns);
        for (size_t i = 0; i < mat.rows; i++)
        {
            for (size_t j = 0; j < mat.columns; j++)
            {
                sum_mat.Mat[i][j] = mat.Mat[i][j] * scalar;
            }
        }
        return sum_mat;
    }
    Matrix Matrix::operator*=(double scalar)
    {
        Matrix sum_mat(this->rows, this->columns);
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < this->columns; j++)
            {
                this->Mat[i][j] *= scalar;
            }
        }
        return *this;
    }
    ostream &operator<<(ostream &os, const Matrix &mat)
    {
        for (size_t i = 0; i < mat.rows; i++)
        {
            os << "["
               << " ";
            for (size_t j = 0; j < mat.columns; j++)
            {
                os << mat.Mat[i][j] << " ";
            }
            os << "]"
               << "\n";
        }
        return os;
    }
}