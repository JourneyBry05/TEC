#ifndef SORTERS_H
#define SORTERS_H

#include "PagedArray.h"

void quickSort(PagedArray &arr, int left, int right);
void insertionSort(PagedArray &arr, size_t size);
void bubbleSort(PagedArray &arr, size_t size);

#endif // SORTERS_H
