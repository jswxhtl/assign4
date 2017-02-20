#include <cblas.h>
#include <iostream>

void diff(int size, double *arrayA, double *arrayB, double *difference){
  for (int i = 0; i < size; i++) {
    difference[i] = arrayA[i] - arrayB[i];
  }
}

void normalize_matrix(int lda, int n, double *array){
  double * temp_array = new double[lda];
  double * scale = new double[n];

  for (int j = 0; j < lda; j++) {
    for (int i = 0; i < n; i++) {
      temp_array[i] = array[i*n + j];
    }
    scale[j] = cblas_dasum(n, temp_array, 1);
  }

  for (int i = 0; i < n*lda; i++) {
    array[i] = array[i] / scale[i%n];
  }

  for (int i = 0; i < lda; i++) {
    std::cout << scale[i] << '\n';
  }
  delete [] temp_array;
  delete [] scale;
}
