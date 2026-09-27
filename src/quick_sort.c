#include <time.h>
#include <stdlib.h>

#include "quick_sort.h"

typedef struct SizeTPair{
  size_t first;
  size_t second;
} SizeTPair;

size_t randomIndex(size_t start, size_t end) {

  size_t index = (size_t)rand() % (end - start + 1) + start;
  return index;
}

void charPtrSwap(char** c1, char** c2){
  char* tmp = *c1;
  *c1 = *c2;
  *c2 = tmp;
}

SizeTPair partition(char** base, int (*compare)(const void*, const void*), char* pivot, size_t start, size_t end) {
  size_t l = start;
  size_t r = end;
  size_t i = start;
  while (i < r) {
    int cmpWithPivotRes = compare(&base[i], &pivot);
    if (cmpWithPivotRes < 0) { //base[i] < pivot
      charPtrSwap(&base[i], &base[l]);
      i++;
      l++;
    } else if (cmpWithPivotRes > 0) { // base[i] > pivot
      r--;
      charPtrSwap(&base[i], &base[r]);
    } else { // base[i] == pivot
      i++;
    }
  }
  return (SizeTPair){l, r};
}

void sortImpl(char** base, int (*compare)(const void*, const void*), size_t start, size_t end) {
  if (end - start <= 1) {
    return;
  }
  char* pivot = base[randomIndex(start, end-1)];
  SizeTPair bounds = partition(base, compare, pivot, start, end);
  sortImpl(base, compare, start, bounds.first);
  sortImpl(base, compare, bounds.second, end);
}

void myQsort(char** base, size_t num, int (*compare)(const void*, const void*)){
  srand(time(NULL));
  sortImpl(base, compare, 0, num);
}