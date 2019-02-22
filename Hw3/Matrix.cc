#include "Matrix.h"


Matrix::Matrix(const int r, const int c) : nrows(r), ncols(c), data(new double[r*c]), entry(new double*[r])
/* Function to construct a zeroed matrix of size r x c. */
{
  // Memory allocation does before the start.

  // Everything set to 0, and entries organised to point correctly.
  memset(data,0.0,sizeof(double)*r*c);
  for (int i = 0; i < r; i++)
  {
    entry[i] = &data[i*c];
  }
}

Matrix::Matrix(const Matrix& mat_in) : nrows(mat_in.nrows), ncols(mat_in.ncols)
/* Alternative constructor for deep copy assignment*/
{
  //After checking that we are not copy null matrix, data memory allocated/filled
  if (mat_in.data != 0) {
    data = new double[nrows*ncols];
    std::copy(mat_in.data,mat_in.data+(mat_in.nrows*mat_in.ncols),data);
  }else {
    data = 0;
    return;
  }

  // entry pointers organised appropriately.
  entry = new double*[nrows];
  for (int i = 0; i < nrows; i++) {
    entry[i] = &data[i*ncols];
  }
}

Matrix& Matrix::operator=(const Matrix& mat_in)
/* Matrix deep copy assignment for overwriting an existing matrix. */
{
  // If matrix is assigned to self we save time:
  if (this == &mat_in) {return *this; }

  // Data allocated and stored:
  double* p = new double[mat_in.nrows*mat_in.ncols];
  std::copy(mat_in.data,mat_in.data+(mat_in.nrows*mat_in.ncols),p);

  // Old pointers freed and new assignments
  delete[] this->data;
  delete[] this->entry;
  data = p;
  nrows = mat_in.nrows;
  ncols = mat_in.ncols;
  entry = new double*[nrows];
  for (int i = 0; i < nrows; i++) {
    entry[i] = &data[i*ncols];
  }

  return *this;
}

void Matrix::set(int i, int j, double x)
/* Function set matrix entry[i][j] to a value x. */
{
  if (i >= nrows || j >= ncols) {
    std::cerr << "set: matrix index out of bounds." << std::endl;
    exit(1);
  }
  entry[i][j] = x;
}

double Matrix::get(int i, int j)
/* Function to return matrix entry[i][j]. */
{
  if (i >= nrows || j >= ncols) {
    std::cerr << "get: matrix index out of bounds." << std::endl;
    exit(1);
  }
  return entry[i][j];
}

double* Matrix::operator[](int i)
/* Function to allow reference to entry[i][j] via mat[i][j]*/
{
  if (i >= nrows) {
    std::cerr << "index: row index out of bounds." << std::endl;
    exit(1);
  }
  //Returning the correct row will allow any entry in it to be referenced.
  return entry[i];
}

Matrix Matrix::operator-()
/* Unary - operator to allow reference to -A matrix for instance. */
{
  Matrix mat_out = *this;
  for (int i = 0; i < nrows*ncols; i++) {
    mat_out.data[i] = -mat_out.data[i];
  }
  return mat_out;
}


Matrix prod(Matrix mat_a, Matrix mat_b)
/* Function to return the matrix product of mat_a and mat_b, used by * operator. */
{
  // We start with error checking:
  int na, ma, nb, mb;
  mat_a.shape(&na,&ma);
  mat_b.shape(&nb,&mb);
  if (ma != nb) {
    std::cerr << "matrix multiply: matrix dimensions don't match." << std::endl;
    exit(1);
  }

  //Now matrix created and
  Matrix mat_out(na,mb);
  for (int i = 0; i < na; i++) {
    for (int j = 0; j < mb; j++){
      for (int k = 0; k < nb; k++) {
        mat_out[i][j]+=(mat_a[i][k]*mat_b[k][j]);
      }
    }
  }
  return mat_out;
}

Matrix sum(Matrix mat_a, Matrix mat_b)
/* Function to return sum of mat_a and mat_b, used by +,- operators*/
{
  // Error checking
  int na, ma, nb, mb;
  mat_a.shape(&na,&ma);
  mat_b.shape(&nb,&mb);
  if (na != nb || ma != mb) {
    std::cerr << "matrices of different dimensions" << std::endl;
    exit(1);
  }

  // Matrix values calculated
  Matrix mat_out(na,ma);
  for (int i = 0; i < na; i++) {
    for (int j = 0; j < ma; j++) {
      mat_out[i][j] = mat_a[i][j] + mat_b[i][j];
    }
  }
  return mat_out;
}

void Matrix::shape(int* n,int* m)
/*Function to update integers for values of nrows and ncols for error checking.*/
{
  *n = nrows;
  *m = ncols;
}

Matrix& Matrix::operator+=(const Matrix& mat_in)
/* Function to allow increment of a matrix by another matrix. */
{
  //Error checking:
  if (nrows != mat_in.nrows || ncols != mat_in.ncols) {
    std::cerr << "matrices of different dimensions" << std::endl;
    exit(1);
  }
  //Values updated:
  for (int i = 0; i < nrows*ncols; i++) {
    data[i] += mat_in.data[i];
  }
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& mat_in)
/* Function to allow decrement of a matrix by another matrix. */
{
  // Error checking:
  if (nrows != mat_in.nrows || ncols != mat_in.ncols) {
    std::cerr << "matrices of different dimensions" << std::endl;
    exit(1);
  }
  // Values calculated:
  for (int i = 0; i < nrows*ncols; i++) {
    data[i] -= mat_in.data[i];
  }
  return *this;
}

bool Matrix::operator==(const Matrix& mat_in)
/* Boolean operator to check if two matrices are equal. */
{
  // Dimensions checked first.
  if (nrows != mat_in.nrows || ncols != mat_in.ncols) {
    return false;
  }
  // Then all entries checked:
  for (int i = 0; i < nrows*ncols; i++) {
    if (data[i] != mat_in.data[i]) {
      return false;
    }
  }
  return true;
}

bool Matrix::operator!=(const Matrix& mat_in)
/* Boolean operator to check if two matrices are not equal. */
{
  // I just used == operator:
  if (*this == mat_in) {
    return false;
  }
  return true;
}

Matrix::~Matrix()
/*Destructor for good memory management*/
{
  delete []entry;
  delete []data;
}

Matrix operator+(Matrix mat_a, Matrix mat_b)
/* Function to allow addition of matrices*/
{
  Matrix mat_out = mat_a;
  mat_out += mat_b;
  return mat_out;
}

Matrix operator-(Matrix mat_a, Matrix mat_b)
/* Function to allow subtraction of matrices*/
{
  Matrix mat_out = mat_a;
  mat_out -= mat_b;
  return mat_out;
}


Matrix operator*(Matrix mat_a, Matrix mat_b)
/* Function to allow multiplication of matrices*/
{
  return prod(mat_a,mat_b);
}

void Matrix::transpose()
/* Function to transpose a matrix. */
{
  // A new array created to store values.
  double* p = new double[nrows*ncols];
  for (int j = 0; j < ncols; j++) {
    for (int i = 0; i < nrows; i++) {
      p[j*nrows + i] = entry[i][j];
    }
  }

  // Old data deleted
  delete []entry;
  delete []data;

  //Row and column numbers swapped
  int temp = nrows;
  nrows = ncols;
  ncols = temp;

  //New pointers set
  data = p;
  entry = new double*[nrows];
  for (int i = 0; i < nrows; i++) {
    entry[i] = &p[i*ncols];
  }
}

void Matrix::randomize(int a,int b)
/*Function to set Matrix values to random values to make testing clearer. */
{
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<> dis(-2.0, 2.0);
  for (int i = 0; i < nrows*ncols; i++) {
    data[i] = dis(gen);
  }
}

void Matrix::print(){
  std::cout << std::fixed;
  std::cout << std::setprecision(2);
  //Matrix Printed:
  std::cout << '\n';
  for (int i = 0; i<nrows; ++i){
    std::cout << "( ";
    for (int j = 0; j < ncols; j++) {
      if (entry[i][j]<0){
        std::cout << entry[i][j] << " ";
      }else{
        std::cout << " " << entry[i][j] << " ";
      }
    }
    std::cout << ")\n";
  }
  std::cout << std::endl;
}

std::ostream& operator<<(std::ostream &os, Matrix& mat_in)
/* cout output overwritten */
{
  int n,m;
  mat_in.shape(&n,&m);
  // Precision set to clean up output:
  os << std::fixed;
  os << std::setprecision(2);
  //Matrix Printed:
  os << '\n';
  for (int i = 0; i<n; ++i){
    os << "( ";
    for (int j = 0; j < m; j++) {
      if (mat_in.get(i,j)<0){
        os << mat_in.get(i,j) << " ";
      }else{
        os << " " << mat_in.get(i,j) << " ";
      }
    }
    os << ")\n";
  }
  os << std::endl;
  return os;
}
