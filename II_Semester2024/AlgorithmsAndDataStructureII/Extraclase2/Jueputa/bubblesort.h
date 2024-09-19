#ifndef SORTERS_H
#define SORTERS_H

#include <vector>

class Sorters {
public:
    static void bubbleSort(std::vector<int>& arr);
    static void insertionSort(std::vector<int>& arr);
    static void mergeSort(std::vector<int>& arr);

private:
    static void merge(std::vector<int>& arr, int left, int mid, int right);
