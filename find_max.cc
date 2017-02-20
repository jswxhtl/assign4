double max_element (int length, double *array) {
  double max = array[0];
  for (int i = 0; i < length; i++)
  if (array[i] > max) {
    max = array[i];
  }

  return max;
}
