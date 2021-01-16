#include <stdio.h>
#include <stdlib.h>   // for rand
#include <time.h>     // for clock()
#include <stdbool.h>  // for bool
#include <string.h>   // for memcpy()
#include "insertion.h"
#include "bubble.h"
#include "quick.h"
#include "heap.h"
#define LENGTH 1e3    // length of array for sort
#define MEASURE_C 1e6 // cnt of running sort for calc average


long int *array = NULL, *qsort_ar = NULL, *quick_ar = NULL, *insert_ar = NULL, *bubble_ar = NULL, *heap_ar = NULL;


// 配列を確保する
// 確保に失敗したらエラーを出す
long *get_array(void) {
  long *array;
  array = (long *)malloc(sizeof(long) * LENGTH);
  if (array == NULL) {
    printf("メモリ確保に失敗しました。");
    exit(EXIT_FAILURE);
  }
  return array;
}

void set_array_random(long *array) {
  for (int i = 0; i < LENGTH; i++)
    array[i] = rand();
}

void init_arrays(void) {
  if (array == NULL)  array = get_array();
  if (bubble_ar == NULL)  bubble_ar = get_array();
  if (insert_ar == NULL)  insert_ar = get_array();
  if (quick_ar == NULL)  quick_ar = get_array();
  if (heap_ar == NULL)  heap_ar = get_array();
  if (qsort_ar == NULL)  qsort_ar = get_array();

  set_array_random(array);
  memcpy(bubble_ar, array, sizeof(long) * LENGTH);
  memcpy(insert_ar, array, sizeof(long) * LENGTH);
  memcpy(quick_ar, array, sizeof(long) * LENGTH);
  memcpy(heap_ar, array, sizeof(long) * LENGTH);
  memcpy(qsort_ar, array, sizeof(long) * LENGTH);
}


// 配列の中身をすべて表示する
void print_array(long *a) {
  printf("%ld", a[0]);
  for (long i = 1; i < LENGTH; i++)
    printf(", %ld", a[i]);
  printf("\n");
  return;
}

// 昇順ソートが正しくできているかチェック
// できていない場合はエラーを出して終了
void chk_sort(long *a) {
  for (int i = 1; i < LENGTH; i++)
    if (a[i-1] > a[i]) {
      printf("ソートが正しく行われていません\n");
      printf("終了します\n");
      exit(EXIT_FAILURE);
    }
}

// qsort用の比較関数
// qsortではint型を想定しているので return a-b みたいにそのままだと
// オーバーフローが発生する 
int compare_long(const void *a, const void *b) {
  long *A = (long *)a;
  long *B = (long *)b;
  if (*A > *B) return 1;
  if (*A < *B) return -1;
  return 0;
}

// 仮
// 引数の関数をMEASURE_C回実行してその平均実行時間を返す
double measure_sort(void (*sortfn)(long [], long), long array[], char name[]) {
  clock_t start_t, end_t;
  double sum = 0;

  for (int i = 0; i < MEASURE_C; i++) {
    start_t = clock();
    sortfn(array, (long)LENGTH);
    end_t = clock();
    sum += (double)(end_t - start_t) / CLOCKS_PER_SEC;
  }

  printf("%s\t : time = %lf\n", name, sum / MEASURE_C);
  return 0;
}

int main(void) {
  // 配列を用意しセットする
  init_arrays();

  measure_sort(insertion, insert_ar, "insert_hehe");
  measure_sort(bubble, bubble_ar, "bubble_hehe");
  measure_sort(quick, quick_ar, "quick_hehe");
  measure_sort(heap, heap_ar, "heap_heheheh");

  clock_t start_t, end_t;
  start_t = clock();
  qsort(qsort_ar, LENGTH, sizeof(long), compare_long);
  end_t = clock();
  printf("qsort time = %lf\n", (double)(end_t-start_t)/CLOCKS_PER_SEC);

  free(array);
  free(quick_ar);
  free(qsort_ar);
  return 0;
}
