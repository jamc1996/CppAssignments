#include <iostream>
#include <random>
#include <iomanip>

/*
  Matrix.h -- header file for custom made Matrix class.

  Author: John Cormican

  Purpouse: To declare variables and functions for matrix class.

  Usage: To be used with Matrix.cc and some main.cpp, to allow use of
          matrix class in main.
*/

class Matrix
{
private:
  // Necessary variables
  int nrows;
  int ncols;
  double* data;
  double** entry;

public:
  // Constructors
  Matrix(int r, int c);
  Matrix(const Matrix& mat);

  //Getter and setter
  void set(int i, int j, double x);
  double get(int i_row, int j_col);
  double* operator[](const int i);

  //prod function called by * operators
  Matrix& prod(Matrix mat_a, Matrix mat_b);

  // increment operators, used by + and - operators
  Matrix& operator+=(const Matrix& mat);
  Matrix& operator-=(const Matrix& mat);

  // unary - operator
  Matrix operator-();

  // Reassignment/Overwrite of matrix.
  Matrix& operator=(const Matrix& mat);

  // Boolean operators
  bool operator==(const Matrix& mat);
  bool operator!=(const Matrix& mat);

  //Transpose
  void transpose();

  // Useful Functions
  void shape(int* a, int* b);
  void randomize(int a,int b);

  // Matrix printing
  void print();

  // Memory management
  ~Matrix();
};


// Addition, subtraction and mutiplication operators declared as non-members.
Matrix operator+(Matrix mat_a, Matrix mat_b);
Matrix operator-(Matrix mat_a, Matrix mat_b);
Matrix operator*(Matrix mat_a, Matrix mat_b);

// Output using cout for matrices.
std::ostream& operator<<(std::ostream &os, Matrix& mat_in);
