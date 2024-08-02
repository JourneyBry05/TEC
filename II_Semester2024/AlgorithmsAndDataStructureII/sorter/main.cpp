#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>
#include "PagedArray.h"
#include "sorters.h"

int main(int argc, char *argv[]) {
    if (argc != 7) {
        std::cerr << "Usage: " << argv[0] << " --input <INPUT FILE PATH> --output <OUTPUT FILE PATH> --alg <ALGORITHM>\n";
        return EXIT_FAILURE;
    }

    std::string inputPath, outputPath, algorithm;
    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "--input") == 0) {
            inputPath = argv[i + 1];
        } else if (strcmp(argv[i], "--output") == 0) {
            outputPath = argv[i + 1];
        } else if (strcmp(argv[i], "--alg") == 0) {
            algorithm = argv[i + 1];
        } else {
            std::cerr << "Invalid argument: " << argv[i] << "\n";
            return EXIT_FAILURE;
        }
    }

    if (inputPath.empty() || outputPath.empty() || algorithm.empty()) {
        std::cerr << "All arguments are required.\n";
        return EXIT_FAILURE;
    }

    // Copiar el archivo de entrada al archivo de salida
    std::ifstream src(inputPath, std::ios::binary);
    std::ofstream dst(outputPath, std::ios::binary);
    dst << src.rdbuf();
    src.close();
    dst.close();

    // Inicializar PagedArray
    PagedArray arr(outputPath);

    // Determinar el tamaño del archivo
    std::ifstream file(outputPath, std::ios::binary | std::ios::ate);
    size_t fileSize = file.tellg();
    file.close();
    size_t numElements = fileSize / sizeof(int);

    // Ordenar usando el algoritmo especificado
    auto start = std::chrono::high_resolution_clock::now();

    if (algorithm == "QS") {
        quickSort(arr, 0, numElements - 1);
    } else if (algorithm == "IS") {
        insertionSort(arr, numElements);
    } else if (algorithm == "BS") {
        bubbleSort(arr, numElements);
    } else {
        std::cerr << "Invalid algorithm: " << algorithm << "\n";
        return EXIT_FAILURE;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Sorting completed in " << elapsed.count() << " seconds.\n";
    std::cout << "Algorithm used: " << algorithm << "\n";
    std::cout << "Page faults: " << arr.getPageFaults() << "\n";
    std::cout << "Page hits: " << arr.getPageHits() << "\n";

    // Convertir el archivo a formato legible
    std::ifstream inFile(outputPath, std::ios::binary);
    std::ofstream outFile(outputPath + ".txt");
    int value;
    while (inFile.read(reinterpret_cast<char*>(&value), sizeof(int))) {
        outFile << value << ",";
    }

    return EXIT_SUCCESS;
}
+