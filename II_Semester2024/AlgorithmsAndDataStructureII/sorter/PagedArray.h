#ifndef PAGEDARRAY_H
#define PAGEDARRAY_H

#include <vector>
#include <unordered_map>
#include <array>
#include <fstream>

class PagedArray {
public:
    PagedArray(const std::string &filePath, size_t pageSize = 1024);
    ~PagedArray();
    int& operator[](size_t index);
    size_t size() const;

    void writeToFile(const std::string &outputFilePath);
    void writeToTextFile(const std::string &outputFilePath); // Nueva función
    void printStats() const;

private:
    struct Page {
        size_t index;
        std::vector<int> data;
        bool dirty;
    };

    std::ifstream inputFile;
    std::ofstream outputFile;
    size_t pageSize;
    size_t numPages;
    size_t arraySize;
    std::unordered_map<size_t, Page> pages;
    std::array<Page*, 4> pageSlots;
    size_t pageFaults;
    size_t pageHits;

    Page* loadPage(size_t pageIndex);
    void unloadPage(Page* page);
};

#endif // PAGEDARRAY_H
