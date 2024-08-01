#include "sorters.h"

void quickSort(PagedArray &arr, int left, int right){
    int i = left, j =right;
    int pivot = arr[(left + right) / 2];
    while (i <= j){
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i<=j){
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    if (left < j) quickSort(arr, left, right);
    if (i < right) quickSort(arr, left, right);
}

void insertionSort(PagedArray &arr, int n){
    for (int i = 1; i < n; ++i){
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key){
            arr[j + 1] = arr[j];
            j++;
        }
        arr [j+1] = key;
    }
}

void bubbleSort(PagedArray &arr, int n){
    for (int i = 0; i < n - 1; ++i){
        for (int j = 0; j< n-i-1;++j){
            if(arr[j]> arr[j+1]){
                std::swap(arr[j], arr[j+1]);
            }
        }
    }
}