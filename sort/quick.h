#ifndef swap
#define swap(type, x, y) do{ type tmp = x; x = y; y = tmp; } while(0)
#endif

void quickrec(long *array, long left, long right) {
  if (left >= right) return;
  long pl = left, pr = right;
  long x = array[(pl + pr) / 2];

  while (pl <= pr) {
    while (array[pl] < x) pl++;
    while (array[pr] > x) pr--;
    if (pl <= pr) {
      swap(long, array[pl], array[pr]);
      pl++;  pr--;
    }
  }

  quickrec(array, left, pr);
  quickrec(array, pl, right);
  return;
}

void quick(long *array, long length) {
  quickrec(array, 0, length - 1);
}
