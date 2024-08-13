/*
File containing the sorting algorithms to be used using the "PagedArray" class.
Each function receives a "PagedArray" reference
*/

#include "sorters.h" //Remember that it includes the sorting functions
#include <algorithm>

/*
Void functions that implements the Quick Sort algorithm
left: first index of the array segment to sort
right: final index of the array segment to sort
*/
void quickSort(PagedArray &arr, int left, int right) {
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    //Recursively calls "quickSort" to sort the segment right or left
    if (left < j) quickSort(arr, left, j);
    if (i < right) quickSort(arr, i, right);
}
/*
Void functions that implements the Insertion Sort algorithm
size: size of the array to be sorted
*/
void insertionSort(PagedArray &arr, size_t size) {
    for (size_t i = 1; i < size; ++i) {
        int key = arr[i];
        size_t j = i;
        while (j > 0 && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = key;
    }
}

/*
Void functions that implements the Bubble Sort algorithm
size: size of the array to be sorted
*/
void bubbleSort(PagedArray &arr, size_t size) {
    bool swapped;
    for (size_t i = 0; i < size - 1; ++i) {
        swapped = false;
        for (size_t j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}
