#include <fstream>
#include <cmath>
#include <iostream>
#include "find_max.h"

int main(int argc, char const *argv[]) {
  int n = 10;
  double *eigenvalues = new double[n];
  std::ifstream infile("eigenvaluesA.txt");
  for (int i = 0; i < n; i++) {
    infile >> eigenvalues[i];
  }
  infile.close();

  double maxeign = max_element(n, eigenvalues);
  std::cout << "Largest eigenvalue is: " << maxeign << '\n';

  double * eigenvector = new double[n];
  for (int i = 0; i < n; i++) {
    eigenvector[i] = {1./10.};
  }
  std::cout << eigenvector[1] << '\n';

  delete [] eigenvalues;
  delete [] eigenvector;
  return 0;
}
