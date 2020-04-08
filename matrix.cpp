#include <stdio.h> 
#include <iostream>
#include <vector>
#include <type_traits>

template <class T>
class Matrix{
private:
    bool is_square=false;
    int n_strings_=0;
    int n_columns_=0;
    T** elements;
    auto operator[] (int i){return elements[i];}
public:
    Matrix(){;} // 0*0
    Matrix(int n_strings, char E); //инициализация единичной квадратной
    Matrix(int n_strings, T value = T(0)); //инициализация квадратной значением value
    Matrix(int n_strings, int n_columns, T value = T(0)); //инициализация значением value
    //Арифметика
    //Сложение
    template <class U>
    friend Matrix<U> operator-(const Matrix<U>& matrix);
    template <class U, class V>
    friend auto operator+(const Matrix<U>& left, const Matrix<V>& right);
    template <class U, class V>
    friend auto operator-(const Matrix<U>& left, const Matrix<V>& right){return (left+(-right));}
    template <class U, class V>
    friend auto& operator+=(Matrix<U>& left, const Matrix<V>& right);
    template <class U, class V>
    friend auto& operator-=(Matrix<U>& left, const Matrix<V>& right){return (left+=(-right));}
    //Умножение на числа
    template <class U, class V>
    friend auto operator*(Matrix<U>& matrix, const V& volume);
    template <class U, class V>
    friend auto operator*(const V& volume, Matrix<U>& matrix){return matrix*volume;}
    template <class U, class V>
    friend auto operator/(Matrix<U>& matrix, const V& volume){return matrix*(U(1)/volume);}
    template <class U, class V>
    friend auto& operator*=(Matrix<U>& matrix, const V& volume);
    template <class U, class V>
    friend auto& operator/=(Matrix<U>& matrix, const V& volume){return matrix*=(U(1)/volume);}
    //Матричное умножение
    template <class U, class V>
    friend auto operator*(const Matrix<U>& left, const Matrix<V>& right);
    //Служебные
    template <class V>
    bool SizeEqual(const Matrix<V> &another) const {return (this->n_strings_==another.n_strings_)&&(this->n_columns_==another.n_columns_);}
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

template <class T>
Matrix<T> operator-(const Matrix<T> &matrix){
    Matrix<T> result(matrix.n_strings_,matrix.n_columns_,T(0));
    for (int i = 0; i < matrix.n_strings_; i++){
        for (int j = 0; j < matrix.n_columns_; j++){
            result.elements[i][j]=-matrix.elements[i][j];
        }}
    return result;
}

template <class U, class V>
auto operator+(const Matrix<U>& left, const Matrix<V>& right){
    if(left.SizeEqual(right)){
        const bool condition = (sizeof(V)>sizeof(U));
        typedef typename std::conditional<condition, V, U>::type ResType;
        Matrix<ResType> result(left.n_strings_,left.n_columns_,ResType(0));
        for (int i = 0; i < left.n_strings_; i++){
            for (int j = 0; j < left.n_columns_; j++){
                result.elements[i][j] = ResType(left.elements[i][j]) + ResType(right.elements[i][j]);
            }}
        return result;}
    else{throw std::logic_error("Matrix size is not equal!");}
}

template <class U, class V>
auto& operator+=(Matrix<U>& left, const Matrix<V>& right){
    if(left.SizeEqual(right)){
        for (int i = 0; i < left.n_strings_; i++){
            for (int j = 0; j < left.n_columns_; j++){
                left.elements[i][j] += U(right.elements[i][j]);
            }}
        return left;}
    else{throw std::logic_error("Matrix size is not equal!");}
}

template <class U, class V>
auto operator*(Matrix<U>& matrix, const V& volume){
    const bool condition = (sizeof(V)>sizeof(U));
    typedef typename std::conditional<condition, V, U>::type ResType;
    Matrix<ResType> result(matrix.n_strings_,matrix.n_columns_,ResType(0));
        for (int i = 0; i < matrix.n_strings_; i++){
            for (int j = 0; j < matrix.n_columns_; j++){
                result.elements[i][j]=ResType(matrix.elements[i][j])*ResType(volume);}}
    return result;
};

template <class U, class V>
auto& operator*=(Matrix<U>& matrix, const V& volume){
    for (int i = 0; i < matrix.n_strings_; i++){
        for (int j = 0; j < matrix.n_columns_; j++){
            matrix.elements[i][j]*=U(volume);}}
    return matrix;
}

template <class U, class V>
auto operator*(const Matrix<U>& left, const Matrix<V>& right){
    if((left.n_columns_==right.n_strings_)&&(right.n_columns_==left.n_strings_)){
        const bool condition = (sizeof(V)>sizeof(U));
        typedef typename std::conditional<condition, V, U>::type ResType;
        Matrix<ResType> result(left.n_strings_,right.n_columns_,ResType(0));
        for (int i = 0; i<result.n_strings_; i++){
            for (int j = 0; j<result.n_columns_; j++){
                for (int k = 0; k<left.n_columns_; k++){result[i][j]+=left.elements[i][k]*right.elements[k][j];}
        }}
        return result;
    }
    else{throw std::logic_error("Matrix size is not compatible!");}
}
    
int main(){
    Matrix<double> M(4, 'E');
    Matrix<double> G(4, 'E');
    Matrix<double> MM=-(3*M);
    std::cout << (G/=5);
    MM= (MM*G);
    std::cout << MM;
    return 0;
}
