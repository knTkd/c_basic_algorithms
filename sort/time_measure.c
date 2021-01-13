#include <stdio.h>
#include <stdlib.h>   // for rand
#include <time.h>     // for clock()
#include <stdbool.h>  // for bool
#include <string.h>   // for memcpy()
#include "quick.h"
#define LENGTH 1e7    // length of array for sort
#define MEASURE_C 1e3 // cnt of running sort for calc average

long *get_array(void);
void set_array_random(long *);
void print_array(long *);
void chk_sort(long *);
int compare_long(const void *, const void *);

long *array, *quick_ar, *qsort_ar;

int main(void) {
  clock_t start_t, end_t;

  array = get_array();
  quick_ar = get_array();
  qsort_ar = get_array();
  
  // 配列を同じランダムの値にする
  set_array_random(array);
  memcpy(quick_ar, array, sizeof(long) * LENGTH);
  memcpy(qsort_ar, array, sizeof(long) * LENGTH);

  start_t = clock();
  quick(quick_ar, 0, LENGTH - 1);
  end_t = clock();
  printf("myquick time = %lf\n", (double)(end_t-start_t)/CLOCKS_PER_SEC);

  start_t = clock();
  qsort(qsort_ar, LENGTH, sizeof(long), compare_long);
  end_t = clock();
  printf("qsort time = %lf\n", (double)(end_t-start_t)/CLOCKS_PER_SEC);

  
  free(array);
  free(quick_ar);
  free(qsort_ar);
  return 0;
}

// 引数の関数をMERSURE_C回実行してその平均実行時間を返す
double mersure_sort() {
  return 0;
}

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

