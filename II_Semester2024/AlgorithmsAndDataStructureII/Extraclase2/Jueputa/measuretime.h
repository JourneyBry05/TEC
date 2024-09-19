#ifndef MEASURETIME_H
#define MEASURETIME_H

#include <iostream>
#include <vector>
#include <chrono>
#include <stdexcept>
#include "Sorters.h"

class MeasureTime {
public:
    double measureTime(const std::string& func, std::vector<int>& data) {
        Sorters sorters;
        auto start = std::chrono::high_resolution_clock::now();
        auto end = start;

        // Seleccionar el algoritmo basado en 'func'
        if (func == "BubbleSort") {
            start = std::chrono::high_resolution_clock::now();
            sorters.bubbleSort(data);
        } else if (func == "InsertionSort") {
            start = std::chrono::high_resolution_clock::now();
            sorters.insertionSort(data);
        } else if (func == "MergeSort") {
            start = std::chrono::high_resolution_clock::now();
            sorters.mergeSort(data);
        } else {
            throw std::invalid_argument("Error: El algoritmo '" + func + "' no es válido.");
        }

        // Medir el tiempo tiempo
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        return duration.count();
    }
};

#endif // MEASURETIME_H
