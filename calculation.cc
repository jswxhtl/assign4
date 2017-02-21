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


bool within_intervals(int size, double *eigenvalues, double *intervals){
  bool check = false;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (eigenvalues[i] > intervals[2*j]) {
        if (eigenvalues[i] < intervals[2*j + 1]) {
          check = true;
        }
      }
    }
  }
  return check;
}


int gershgorin_test(int lda, int n, double *array, double *eigenvalues){
  double * intervals = new double[2*lda];
  for (int i = 0; i < lda; i++) {
    double * temp = new double[n];
    int row_radius, row_center;
    int index = 0;
    for (int j = 0; j < n*lda; j++) {
      if (j/lda == i) {
        if (j%(n+1) == 0) {
          temp[index] = 0;
          row_center = array[j];
        }else{
          temp[index] = array[j];
        }
        index += 1;
      }
    }
    row_radius = cblas_dasum(n, temp, 1);
    intervals[2*i] = row_center - row_radius;
    intervals[2*i + 1] = row_center + row_radius;
    delete[] temp;
  }
  if (within_intervals(lda, eigenvalues, intervals)){
    delete[] intervals;
    return 0;
  } else {
    delete[] intervals;
    return 1;
  }
}
