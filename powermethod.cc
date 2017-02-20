#include <fstream>
#include <lapacke.h>
#include <iostream>
#include "find_max.h"

int main(int argc, char const *argv[]) {
  int n = 10;
  double w[n] = {};
  std::ifstream infile("eigenvaluesA.txt");
  for (int i = 0; i < n; i++) {
    infile >> w[i];
  }
  infile.close();

  double maxeign = max_element(n, w);
  std::cout << maxeign << '\n';

  return 0;
}
