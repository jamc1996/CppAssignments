
#include <iostream>
#include <random>
#include <iomanip>

/*
  Matrix.h -- header file for Matrix class, declaring .

  Author: John Cormican

  Purpouse: Simulate cache operation

  Usage: Runs program, option with optional arguments -a associativity
  of the cache, -f filename where address stream is taken from, -l for cache
  line length and -s for cache size. If no arguments given default values are
  set to match the assignment question.
*/

class Matrix
{
private:
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

  //sum & prod functions called by +, -, and * operators
  Matrix& prod(Matrix mat_a, Matrix mat_b);

  // increment operators
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
