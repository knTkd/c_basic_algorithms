void insertion(long *array, long length) {
  for (long j = 1; j < length; j++) {
    long key = array[j];
    long i = j - 1;
    while (i >= 0 && array[i] > key) {
      array[i + 1] = array[i];
      i -= 1;
    }
    array[i + 1] = key;
  }
}
