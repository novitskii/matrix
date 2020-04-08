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
    Matrix(){;} // 0*0
    Matrix(int n_strings, char E); //инициализация единичной квадратной
    Matrix(int n_strings, T value = T(0)); //инициализация квадратной значением value
    Matrix(int n_strings, int n_columns, T value = T(0)); //инициализация значением value
    template <class U, class V>
    friend const auto operator+(const Matrix<U>& left, const Matrix<V>& right);
    //template <class U>
    //Matrix<T> operator*(const U &another) const;
    //T GetElement(int i,int j) const {return elements[i][j];}
    //void SetElement(int i,int j, T value){elements[i][j]=value;}
    //~Matrix(){delete[] elements;}
    template <class U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<U> &matrix);
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
Matrix<T>::Matrix(int n_strings, int n_columns, T value){
    n_strings_=n_strings;
    n_columns_=n_columns;
    if (n_columns==n_strings) {is_square=true;}
    if (n_columns!=0 && n_strings!=0){
        elements = new T*[n_strings_];
        for (int count = 0; count < n_strings_; ++count)
        {elements[count] = new T[n_columns_];}
    }
    for (int i = 0; i < n_strings_; i++){
        for (int j = 0; j < n_columns_; j++){
            elements[i][j]=T(value);}}
}

template <class T>
Matrix<T>::Matrix(int n_strings, T value) : Matrix(n_strings, n_strings, value) {is_square=true;}

template <class T>
Matrix<T>::Matrix(int n_strings, char E) : Matrix(n_strings, n_strings, T(0)) {is_square=true; if(E=='E'||E=='I'){ for (int i = 0; i < n_strings; ++i) elements[i][i] = T(1); }}

template <class U, class V>
const auto operator+(const Matrix<U>& left, const Matrix<V>& right)
{
    sizeof(V)>sizeof(U) ? typedef V ResType : typedef U ResType;
    Matrix<ResType> result(left.n_strings_,left.n_columns_,ResType(0));
    for (int i = 0; i < left.n_strings_; i++){
        for (int j = 0; j < left.n_columns_; j++){
            result[i][j] = ResType(left.elements[i][j]) + ResType(right.elements[i][j]);
        }}
    return result;
}

// template <class T, class U>
// Matrix<T> Matrix<T>::operator*(const U &another) const{
//     Matrix<T> result(n_strings_,n_columns_);
//     for (int i = 0; i < n_strings_; i++){
//         for (int j = 0; j < n_columns_; j++){
//             T element_value = this->GetElement(i,j)*T(another);
//             result.SetElement(i,j,element_value);}}
//     return result;
// };
    
int main(){
    Matrix<double> M(4, 'E');
    std::cout << (M+M);
    return 0;
}
