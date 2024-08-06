/*
File that defines a 'PagedArray' class to handle a large array
of integers using pagination
*/

// Inclusion guards
#ifndef PAGEDARRAY_H
#define PAGEDARRAY_H

#include <vector>
#include <unordered_map>
#include <array>
#include <fstream>

using namespace std;

class PagedArray {
public:
    /* Constructor that initializes the 'PagedArray' object by reading data from a binary file    
    filePath: path of the binary file containing the data
    pageSize: page size in integers
    */
    PagedArray(const string &filePath, size_t pageSize = 1024);
    ~PagedArray();
    int& operator[](size_t index);
    size_t size() const;

    void writeToFile(const string &outputFilePath); // Writes the array content to a binary file
    void writeToTextFile(const string &outputFilePath); // Writes the array content to a text file separated by commas
    void printStats() const; // Prints page faults and page hits

private:
    // Internal structure to represent a data page
    struct Page {
        size_t index;
        vector<int> data;
        bool dirty; // Indicates if the page has been modified
    };

    ifstream inputFile; // Reads data from a binary file
    ofstream outputFile; // Writes data to a binary file
    size_t pageSize;
    size_t numPages;
    size_t arraySize;
    unordered_map<size_t, Page> pages; // Stores the loaded pages in memory
    array<Page*, 4> pageSlots; // Represents the page slots in memory
    size_t pageFaults; // Faults counter 
    size_t pageHits; // Hits counter

    Page* loadPage(size_t pageIndex); // Loads a page from disk
    void unloadPage(Page* page); // Unloads a page to disk if it was modified
};

#endif