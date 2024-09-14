#ifndef SORTINGALGORITHMS_H
#define SORTINGALGORITHMS_H

#include "MPointer.h"

// Implementación de BubbleSort para MPointer<int>
void bubbleSort(MPointer<int> arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (*arr[j] > *arr[j + 1]) {
                int temp = *arr[j];
                *arr[j] = *arr[j + 1];
                *arr[j + 1] = temp;
            }
        }
    }
}

// Implementación de InsertionSort para MPointer<int>
void insertionSort(MPointer<int> arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = *arr[i];
        int j = i - 1;
        while (j >= 0 && *arr[j] > key) {
            *arr[j + 1] = *arr[j];
            j = j - 1;
        }
        *arr[j + 1] = key;
    }
}

// Implementación de QuickSort para MPointer<int>
int partition(MPointer<int> arr[], int low, int high) {
    int pivot = *arr[high];
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        if (*arr[j] < pivot) {
            i++;
            int temp = *arr[i];
            *arr[i] = *arr[j];
            *arr[j] = temp;
        }
    }
    int temp = *arr[i + 1];
    *arr[i + 1] = *arr[high];
    *arr[high] = temp;
    return (i + 1);
}

void quickSort(MPointer<int> arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

#endif // SORTINGALGORITHMS_H
