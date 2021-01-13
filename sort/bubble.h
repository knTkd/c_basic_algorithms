#define swap(type, x, y) do { type t = x; x = y; y = t; } while (0)

void bubble(long *array, long length) {
  for (long i = 0; i < length - 1; i++)
    for (long j = length - 1; j > i; j--)
      if (array[j-1] > array[j])
	swap(long, array[j-1], array[j]);
}
