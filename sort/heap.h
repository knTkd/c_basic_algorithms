#ifndef swap
#define swap(type, x, y) do { type t = x; x = y; y = t; } while (0)
#endif

void downheap(long array[], long bigdady, long length) {
  long key = array[bigdady];
  long child, par = bigdady;
  for (; par * 2 + 1 < length; par = child) {
    long pl = par * 2 + 1, pr = par * 2 + 2;
    child = pr < length && array[pr] > array[pl] ? pr : pl;
    if (array[child] <= key)
      break;
    array[par] = array[child];
  }
  array[par] = key;
}

void heap(long array[], long length) {
  // heapを構築
  for (long i = (length - 2) / 2; i >= 0; i--)
    downheap(array, i, length);

  for (long i = length - 1; i > 0; i--) {
    swap(long, array[0], array[i]);
    downheap(array, 0, i);
  }
}
