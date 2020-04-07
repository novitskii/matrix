#include <stdio.h> 
#include <iostream>
#include <vector>

template <class T>
class Matrix{
private:
    bool is_square=false;
    int n_strings_=0;
    int n_columns_=0;
    T** elements;
public:
    Matrix(){;}
    Matrix(int n_strings);
    Matrix(int n_strings, int n_columns);
    //~Matrix(){delete[] elements;}
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T> &matrix);
};

template <class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T> &matrix){
    for (int i = 0; i < matrix.n_strings_; i++){
        for (int j = 0; j < matrix.n_columns_; j++){
            os << matrix.elements[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

template <class T>
Matrix<T>::Matrix(int n_strings, int n_columns){
    n_strings_=n_strings;
    n_columns_=n_columns;
    if (n_columns!=0 && n_strings!=0){
        elements = new T*[n_strings_];
        for (int count = 0; count < n_strings_; ++count)
        {elements[count] = new T[n_columns_];}
    }
}

int main(){
    Matrix<double> M(2,2);
    std::cout << M;
    return 0;
}
