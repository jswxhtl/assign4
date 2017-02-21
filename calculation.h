void diff(int size, double *arrayA, double *arrayB, double *difference);
void normalize_matrix(int lda, int n, double *array);
bool within_intervals(int size, double *eigenvalues, double *intervals);
int gershgorin_test(int n, int lda, double *array, double *eigenvalues);
