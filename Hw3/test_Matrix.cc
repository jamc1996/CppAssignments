#include "Matrix.h"

int main()
{
  Matrix A(4,3);
  A.randomize(-2,2);

  std::cout << "A initialized as 4x3 matrix and filled with random values." << std::endl;
  std::cout << "\nA: " << A << std::endl;

  std::cout << "set used to update value(3,2) and get used to print it:" << std::endl;
  A.set(3,2,3.14);
  std::cout << "A.get(3,2) = " << A.get(3,2) << std::endl;
  std::cout << "Overloaded [], so can also reference as A[3][2] = " << A[3][2] << std::endl;

  std::cout << "\nNow deep copy constructorused to make B=A." << std::endl;
  Matrix B = A;
  std::cout << "\nB: " << B << std::endl;

  Matrix C(4,3);
  C.randomize(-2,2);
  std::cout << "C, a new 4x3 matrix is created and filled with random values." << std::endl;
  std::cout << "\nC: " << A << std::endl;

  std::cout << "Now calculate A + C" << std::endl;
  Matrix D = A + C;
  std::cout << "\nD = A + C: " << D << std::endl;

  std::cout << "Now D+=B gives" << std::endl;
  D+=B;
  std::cout << "\nD: ";
  D.print();
  std::cout << "And D-=B brings us back to" << std::endl;
  D-=B;
  std::cout << "\nD: " << D << std::endl;

  std::cout << "We also have unary - operator" << std::endl;
  Matrix E = -D;
  std::cout << "\nE =-D: " << E << std::endl;

  std::cout << "and binary - operator:" << std::endl;
  Matrix F = A - D;
  std::cout << "\nF = A - D:" << F << std::endl;

  std::cout << "And some boolean operators:" << std::endl;
  if (A == B) {
    std::cout << "This prints if A == B" << std::endl;
  }
  if (A != D) {
    std::cout << "This prints if A != D" << std::endl;
  }

  std::cout << "We can also transpose matrices" << std::endl;
  F.transpose();
  std::cout << "\nF transposed:" << F << std::endl;

  std::cout << "Finally we can multiply:" << std::endl;
  Matrix G = A*F;
  std::cout << "\nG = F*A:" << G << std::endl;

  return 0;
}
