#include <iostream>
#include <cstring>
#include <chrono>
#include "PagedArray.h"
#include "sorters.h"

int main(int argc, char *argv[]) {
    if (argc != 7) {
        std::cerr << "Usage: sorter -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITMO>" << std::endl;
        return 1;
    }

    std::string inputFilePath, outputFilePath, algorithm;
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "-input") == 0) {
            inputFilePath = argv[++i];
        } else if (std::strcmp(argv[i], "-output") == 0) {
            outputFilePath = argv[++i];
        } else if (std::strcmp(argv[i], "-alg") == 0) {
            algorithm = argv[++i];
        }
    }

    PagedArray arr(inputFilePath);

    auto start = std::chrono::high_resolution_clock::now();

    if (algorithm == "QS") {
        quickSort(arr, 0, arr.size() - 1);
    } else if (algorithm == "IS") {
        insertionSort(arr, arr.size());
    } else if (algorithm == "BS") {
        bubbleSort(arr, arr.size());
    } else {
        std::cerr << "Unknown algorithm: " << algorithm << std::endl;
        return 1;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    arr.writeToFile(outputFilePath);
    arr.writeToTextFile(outputFilePath + ".txt"); // Nueva línea para escribir el archivo de texto
    arr.printStats();

    std::cout << "Algorithm used: " << algorithm << std::endl;
    std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}
