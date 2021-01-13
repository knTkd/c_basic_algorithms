#define swap(type, x, y) do{ type tmp = x; x = y; y = tmp; } while(0)

void quick(long *array, long left, long right) {
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

  quick(array, left, pr);
  quick(array, pl, right);
  return;
}
