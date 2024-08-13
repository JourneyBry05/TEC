/*
Sorts a large array of integers stored in a binary file using a specified sorting algorithm. 
It uses a paginated array to handle large datasets efficiently.
*/

#include <iostream>
#include <cstring>
#include <chrono>
#include "PagedArray.h"
#include "sorters.h"

/*Main function to execute the sorter program
argc: The number of command line arguments passed to the program
*argv: contain the command line arguments
*/
int main(int argc, char *argv[]) {
    // Check for correct number of arguments
    if (argc != 7) {
        std::cerr << "Usage: sorter -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITHM>" << std::endl;
        return 1;
    }

    // Variables to store input, output file paths and algorithm name
    std::string inputFilePath, outputFilePath, algorithm;

    // Parse command line arguments
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "-input") == 0) {
            inputFilePath = argv[++i];
        } else if (std::strcmp(argv[i], "-output") == 0) {
            outputFilePath = argv[++i];
        } else if (std::strcmp(argv[i], "-alg") == 0) {
            algorithm = argv[++i];
        }
    }

    // Create PagedArray from the input file
    PagedArray arr(inputFilePath);

    // Start timing the sorting process
    auto start = std::chrono::high_resolution_clock::now();

    // Perform sorting based on the specified algorithm
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

    // End timing the sorting process
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Write sorted data to output file
    arr.writeToFile(outputFilePath);
    arr.writeToTextFile(outputFilePath + ".txt"); // Write data to text file as well

    // Print statistics and time taken
    arr.printStats();
    std::cout << "Algorithm used: " << algorithm << std::endl;
    std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}

