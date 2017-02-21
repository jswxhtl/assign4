#include <lapacke.h>
#include <fstream>
#include "calculation.h"
#include <iostream>

int main(int argc, char **argv) {
  int n=10, lda=10;
  double *w = new double[n];
  double *a = new double[n*lda]{
    1, 11, 7, 9, 7, 11, 7, 9, 2, 11,
    11, 4, 10, 10, 6, 2, 9, 6,10, 0,
    7, 10, 3, 5, 4, 4, 4, 4, 6, 10,
    9, 10, 5, 3, 8, 8, 3, 5, 1, 8,
    7, 6, 4, 8, 8, 10, 5, 6, 10, 0,
    11, 2, 4, 8, 10, 9, 4, 3, 5, 11,
    7, 9, 4, 3, 5, 4, 3, 10, 7, 2,
    9, 6, 4, 5, 6, 3, 10, 11, 1, 7,
    2, 10, 6, 1, 10, 5, 7, 1, 10, 5,
    11, 0, 10, 8, 0, 11, 2, 7, 5, 1
  };
  double *a_operator = new double[n*lda];
  for (int i = 0; i < n*lda; i++) {
    a_operator[i] = a[i];
  }

  //Using CBLAS interface
  LAPACKE_dsyev(LAPACK_COL_MAJOR, 'V', 'U', n, a_operator, lda, w );
  std::ofstream fout("eigenvaluesA.txt");
  for (int i = 0; i < n; i++)
  fout<<w[i]<<'\n';
  fout.close();

  if (gershgorin_test(lda, n, a, w) == 0) {
    std::cout << "Gershgorin theorem satisfied!" << std::endl;
  } else {
    std::cout << "Gershgorin theorem unsatisfied!" << std::endl;
  }

  delete [] w;
  delete [] a;

  return 0;
}
