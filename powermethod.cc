#include <fstream>
#include <cmath>
#include <cblas.h>
#include <iostream>
#include <lapacke.h>
#include "calculation.h"

int main(int argc, char const *argv[]) {
  int n=10, lda=10;
  double *eigenvalues = new double[n];
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

  std::ifstream infile("eigenvaluesA.txt");
  for (int i = 0; i < n; i++) {
    infile >> eigenvalues[i];
  }
  infile.close();

  int max_index = cblas_idamax(n, eigenvalues, 1);
  double maxeign = eigenvalues[max_index];
  std::cout << "Index of max eigenvalue is: " << max_index << '\n';
  std::cout << "Largest eigenvalue is: " << maxeign << '\n';
  LAPACKE_dsyev(LAPACK_ROW_MAJOR, 'V', 'U', n, a, lda, eigenvalues );

  double * true_eigenvector = new double[n];
  double * eigenvector = new double[n];
  double * temp_eigenvector = new double[n];
  double * difference = new double[n];

  for (int i = 0; i < n; i++ ) {
    true_eigenvector[i] = a[max_index*lda + i];
    temp_eigenvector[i] = 1./10.;
    difference[i] = true_eigenvector[i] - temp_eigenvector[i];
  }

  double residual = cblas_dnrm2(n, difference, 1);
  std::cout << "Norm of difference between eigenvectors is: " << residual << '\n';

  normalize_matrix(lda, n, a_operator);
  for (int i = 0; i < 10; i++) {
    std::cout << a_operator[i] << '\n';
  }

  double convergence = 1.0;
  int step = 0;
  while (convergence > 1.0e-5) {
    cblas_dgemv(CblasRowMajor, CblasNoTrans, lda, n, 1.0, a_operator, lda, temp_eigenvector, 1, 0.0, eigenvector, 1);
    diff(n, temp_eigenvector, eigenvector, difference);
    for (int i = 0; i < n; i++) {
      temp_eigenvector[i] = eigenvector[i];
    }
    convergence = cblas_dnrm2(n, difference, 1);
    step += 1;
    std::cout << "Convergence: " << convergence << '\n';
    std::cout << "Step now: " << step << '\n';
  }

  diff(n, true_eigenvector, eigenvector, difference);
  residual = cblas_dnrm2(n, difference, 1);
  std::cout << "Residual is: " << convergence << '\n';

  diff(n, true_eigenvector, temp_eigenvector, difference);
  residual = cblas_dnrm2(n, difference, 1);
  std::cout << "Residual is: " << convergence << '\n';

  diff(n, temp_eigenvector, eigenvector, difference);
  residual = cblas_dnrm2(n, difference, 1);
  std::cout << "Residual is: " << convergence << '\n';


  delete [] eigenvalues;
  delete [] a;
  delete [] a_operator;
  delete [] true_eigenvector;
  delete [] eigenvector;
  delete [] temp_eigenvector;
  delete [] difference;

  return 0;
}
