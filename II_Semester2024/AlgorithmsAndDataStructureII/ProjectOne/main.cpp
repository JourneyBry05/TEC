#include "MPointer.h"
#include "SortingAlgorithms.h"
#include <iostream>

int main() {
    MPointer<int> pInt1 = MPointer<int>::New();
    *pInt1 = 42;
    MPointer<int> pInt2 = MPointer<int>::New();
    *pInt2 = 12;
    MPointer<int> pInt3 = MPointer<int>::New();
    *pInt3 = 35;
    MPointer<int> pInt4 = MPointer<int>::New();
    *pInt4 = 7;
    MPointer<int> pInt5 = MPointer<int>::New();
    *pInt5 = 15;

    
    // Crear un arreglo de MPointer<int>
    MPointer<int> arr[] = { pInt1, pInt2, pInt3, pInt4, pInt5 };

    // Imprimir la lista original
    std::cout << "Lista original: ";
    for (int i = 0; i < 5; i++) {
        std::cout << *arr[i] << " ";  
    }
    std::cout << std::endl;

    // Aplicar BubbleSort
    bubbleSort(arr, 5);
    std::cout << "Lista ordenada con BubbleSort: ";
    for (int i = 0; i < 5; i++) {
        std::cout << *arr[i] << " ";
    }
    std::cout << std::endl;

    // Restablecer valores y aplicar InsertionSort
    *pInt1 = 42; *pInt2 = 12; *pInt3 = 35; *pInt4 = 7; *pInt5 = 15;
    insertionSort(arr, 5);
    std::cout << "Lista ordenada con InsertionSort: ";
    for (int i = 0; i < 5; i++) {
        std::cout << *arr[i] << " ";
    }
    std::cout << std::endl;

    // Restablecer valores y aplicar QuickSort
    *pInt1 = 42; *pInt2 = 12; *pInt3 = 35; *pInt4 = 7; *pInt5 = 15;
    quickSort(arr, 0, 4);
    std::cout << "Lista ordenada con QuickSort: ";
    for (int i = 0; i < 5; i++) {
        std::cout << *arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
