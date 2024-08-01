#ifndef PAGEDARRAY_H
#define PAGEDARRAY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <random>
#include <chrono>

class PagedArray {
    public:
        PagedArray(const std::string &filePath, size_t pageSize = 4096);
        ~PagedArray();

        int operator[](size_t index);
        void set(size_t index, int value);
        
        size_t getPageFaults() const { return pageFaults; }
        size_t getPageHits() const { return pageHits; }

    private:
        size_t pageSize;
        size_t numPages;
        std::string filePath;
        std::vector<int*> pages;
        std::unordered_map <size_t, int*> pageTable;
        size_t pageFaults;
        size_t pageHits;

        void loadPage(size_t pageIndex);
        void unloadPage(size_t pageIndex);
        size_t getPageINdex (size_t index) const {return index/pageSize;}
        size_t getOffset(size_t index) const {return index % pageSize;}
};

#endif