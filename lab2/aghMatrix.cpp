#include "aghMatrix.h"


// Parameter Constructor                                                                                                                                                      
template<typename T>
AGHMatrix<T>::AGHMatrix(const std::vector<std::vector<T>>& mat) 
{
  matrix.resize(mat.size());
  for (unsigned i = 0; i < mat.size(); i++) 
  {
    matrix[i].resize(mat[i].size());
    for(unsigned j = 0; j < mat[i].size(); j++)
    {
      matrix[i][j] = mat[i][j];
    }
  }
  rows = matrix.size();
  cols = matrix[0].size();
}

// Parameter Constructor                                                                                                                                                      
template<typename T>
AGHMatrix<T>::AGHMatrix(unsigned _rows, unsigned _cols, const T& _initial) 
{
  matrix.resize(_rows);
  for (unsigned i=0; i<matrix.size(); i++) 
  {
    matrix[i].resize(_cols, _initial);
  }
  rows = _rows;
  cols = _cols;
}

// Copy Constructor                                                                                                                                                           
template<typename T>
AGHMatrix<T>::AGHMatrix(const AGHMatrix<T>& rhs) 
{
  matrix = rhs.matrix;
  rows = rhs.get_rows();
  cols = rhs.get_cols();
}

// Get the number of rows of the matrix                                                                                                                                       
template<typename T>
unsigned AGHMatrix<T>::get_rows() const 
{
  return this->rows;
}

// Get the number of columns of the matrix                                                                                                                                    
template<typename T>
unsigned AGHMatrix<T>::get_cols() const 
{
  return this->cols;
}

// Assignment Operator                                                                                                                                                        
template<typename T>
AGHMatrix<T>& AGHMatrix<T>::operator=(const AGHMatrix<T>& rhs) 
{
  if (&rhs == this)
    return *this;

  unsigned new_rows = rhs.get_rows();
  unsigned new_cols = rhs.get_cols();

  matrix.resize(new_rows);
  for (unsigned i=0; i<matrix.size(); i++) 
  {
    matrix[i].resize(new_cols);
  }

  for (unsigned i=0; i<new_rows; i++) 
  {
    for (unsigned j=0; j<new_cols; j++) 
    {
      matrix[i][j] = rhs(i, j);
    }
  }
  rows = new_rows;
  cols = new_cols;

  return *this;
}

// Access the individual elements                                                                                                                                             
template<typename T>
T& AGHMatrix<T>::operator()(const unsigned& row, const unsigned& col) 
{
  return this->matrix[row][col];
}

// Access the individual elements (const)                                                                                                                                     
template<typename T>
const T& AGHMatrix<T>::operator()(const unsigned& row, const unsigned& col) const 
{
  return this->matrix[row][col];
}

template<typename T>
bool AGHMatrix<T>::operator==(const AGHMatrix<T>& rhs) {
  if (rows != rhs.get_rows() || cols != rhs.get_cols()) {
    return false;
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (this->matrix[i][j] != rhs(i, j)) {
        return false;
      }
    }
  }

  return true;
}

// Addition of two matrices                                                                                                                                                   
template<typename T>
AGHMatrix<T> AGHMatrix<T>::operator+(const AGHMatrix<T>& rhs) 
{
  if (rows != rhs.get_rows() || cols != rhs.get_cols())
  {
    throw std::runtime_error("Matrices have to be of same size");
  }

  AGHMatrix<T> mat(rows, cols, 0);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      mat(i, j) = this->matrix[i][j] + rhs(i, j);
    }
  }

  return mat;
}

// Left multiplication of this matrix and another                                                                                                                              
template<typename T>
AGHMatrix<T> AGHMatrix<T>::operator*(const AGHMatrix<T>& rhs) 
{
  if (cols != rhs.get_rows()) {
    throw std::runtime_error("Incorrect matrix dimensions");
  }

  AGHMatrix<T> mat(rows, rhs.get_cols(), 0);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < rhs.get_cols(); j++) {
      T sum = 0;
      for (int k = 0; k < cols; k++) {
        sum += this->matrix[i][k] * rhs(k, j);
      }
      mat(i, j) = sum;
    }
  }

  return mat;
}

template<typename T>
AGHMatrix<T> AGHMatrix<T>::operator*(T scalar) {
  AGHMatrix<T> mat(rows, cols, 0);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      mat(i, j) = scalar * this->matrix[i][j];
    }
  }

  return mat;
}

template<typename T>
AGHMatrix<T> AGHMatrix<T>::transpose()
{
  AGHMatrix<T> mat(cols, rows, 0);

  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      mat(i, j) = this->matrix[j][i];
    }
  }

  return mat;
}

template<typename T>
bool AGHMatrix<T>::is_symmetric()
{
  return (rows == cols && *this == transpose());
}

template<typename T>
void AGHMatrix<T>::swap_rows(int r1, int r2) 
{
    for (int i = 0; i < cols; i++) {
        T b = this->matrix[r1][i];
        this->matrix[r1][i] = this->matrix[r2][i];
        this->matrix[r2][i] = b;
    }
}

// Printing matrix                                                                                                                        
template<typename T>
std::ostream& operator<<(std::ostream& stream, const AGHMatrix<T>& matrix) 
{
  for (int i=0; i<matrix.get_rows(); i++) 
  { 
    for (int j=0; j<matrix.get_cols(); j++) 
    {
        stream << matrix(i,j) << ", ";
    }
    stream << std::endl;
  }
  stream << std::endl;

  return stream;
}