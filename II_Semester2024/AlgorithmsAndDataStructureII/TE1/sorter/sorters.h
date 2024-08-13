/*
Declare sort functions that operate on 'PagedArray' objects
*/
/*
Include guards to make sure the content is included just once
*/
#ifndef SORTERS_H
#define SORTERS_H

#include "PagedArray.h" //Include 'PagedArray' definitions for sorting functions

/*
Void function declarations for each sorting algorithm,
each function receives a reference to a 'PagedArray' object as "PagedArray &arr"
*/
void quickSort(PagedArray &arr, int left, int right); //Initial and last index to sort, respectively
void insertionSort(PagedArray &arr, size_t size); //size: Size of array to be sorted
void bubbleSort(PagedArray &arr, size_t size); //size: Size of array to be sorted

#endif
