#include <stdio.h>
#include <stdlib.h>

void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void bubbleSort(int arr[], int n) {
  int i, j;
  for (i = 0; i < n - 1; i++)

    for (j = 0; j < n - i - 1; j++)
      if (arr[j] > arr[j + 1])
        swap(&arr[j], &arr[j + 1]);
}

void printArray(int arr[], int size) {
  int i;
  for (i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

void fillUp(int *array, int size) {
  for (int i = 0; i < size; ++i) {
    *(array + i) = rand() % 1000000;
  }
}

int main() {
  int arr_new[100000];
  srand((unsigned)41);
  fillUp(&arr_new[0], 100000);
  bubbleSort(arr_new, 100000);
  return 0;
}