#include "lumina/util/LMatrix.hpp"
#include "lumina/util/LVector.hpp"

#include <iostream>

using namespace std;
using namespace lumina;


void matrixTest() {
  cout << "Create new 4x4 float matrix:" << endl;
  LMatrix<float, 4, 4> m1;
  cout << m1 << endl;
  cout << "Set to identity:" << endl;
  cout << m1.setToIdentity() << endl;

  m1.data[0][3] = 2.f;
  cout << m1 << endl;
  cout << -m1.inverted() << endl;
  cout << m1.determinant() << endl;
  cout << m1.getDiagonal() << endl;
  cout << Mat4f() - m1 << endl;
  cout << m1 * m1 << endl;
  cout << matrix_cast<MatQf<5>>(m1) << endl;

  Vec4f vec(1,2,3,4);
  cout << m1 * vec << endl;


  Mat2f m2;
  cout << m2.determinant() << endl;
}


int main() {
  matrixTest();
}