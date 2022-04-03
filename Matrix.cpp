#include "Matrix.hpp"
#include <stdexcept>
using namespace std;
vector<vector<double>> insert_val(std::vector<double> vec, size_t rows, size_t columns)
{
vector<vector<double>> mat(rows, vector<double>(columns));
for(size_t i=0;i<rows;i++){
    for(size_t j=0;j<columns;j++){
        size_t index = (i*columns)+j;
        double num = vec[index];
        mat[i][j] = num;
    }
}
return mat;
}
namespace zich
{
    Matrix::Matrix(std::vector<double> vec, size_t rows, size_t columns)
    {
        this->rows = rows;
        this->columns = columns;
        this->Mat=insert_val(vec,rows,columns);
    }
    Matrix::Matrix(size_t rows, size_t columns){
        this->rows=rows;
        this->columns=columns;
        this->Mat.assign(rows, vector<double>(columns));
    }
    bool Matrix::operator!=(const Matrix &other){
        if(this->rows != other.rows || this->columns != other.columns){
            return true;
        }
        for(size_t i=0; i<other.rows; i++){
            for (size_t j = 0; j < other.rows; j++)
            {
                if(this->Mat[i][j]!=other.Mat[i][j])
                {
                    return true;
                }
            }
        }
        return false;
    }
    bool Matrix::operator==(const Matrix &other){
        if(this->Mat != other.Mat){
            return false;
        }
        return true;
    }
    Matrix Matrix::operator*=(const Matrix &other){
        if(this->columns != other.rows)
        {
            throw invalid_argument("in order to multiply two matrix has to be same size of columns an rows");
        }
        Matrix multi_mat(this->rows, other.columns);
        
    }
}