#include "PagedArray.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <fstream> // Añadir para escribir en archivo de texto

PagedArray::PagedArray(const std::string &filePath, size_t pageSize)
    : pageSize(pageSize), pageFaults(0), pageHits(0) {
    inputFile.open(filePath, std::ios::binary);
    if (!inputFile) {
        throw std::runtime_error("Cannot open input file");
    }

    inputFile.seekg(0, std::ios::end);
    size_t fileSize = inputFile.tellg();
    arraySize = fileSize / sizeof(int);
    numPages = (fileSize + pageSize * sizeof(int) - 1) / (pageSize * sizeof(int));
    inputFile.seekg(0, std::ios::beg);

    for (auto &slot : pageSlots) {
        slot = nullptr;
    }
}

PagedArray::~PagedArray() {
    for (auto &slot : pageSlots) {
        if (slot && slot->dirty) {
            unloadPage(slot);
        }
    }
    inputFile.close();
    if (outputFile.is_open()) {
        outputFile.close();
    }
}

int& PagedArray::operator[](size_t index) {
    size_t pageIndex = index / pageSize;
    size_t offset = index % pageSize;

    for (auto &slot : pageSlots) {
        if (slot && slot->index == pageIndex) {
            ++pageHits;
            return slot->data[offset];
        }
    }

    ++pageFaults;
    Page* page = loadPage(pageIndex);
    return page->data[offset];
}

PagedArray::Page* PagedArray::loadPage(size_t pageIndex) {
    if (pages.count(pageIndex)) {
        return &pages[pageIndex];
    }

    if (pages.size() >= 4) {
        size_t randomIndex = std::rand() % 4;
        Page* oldPage = pageSlots[randomIndex];
        unloadPage(oldPage);
        pages.erase(oldPage->index);
    }

    Page newPage;
    newPage.index = pageIndex;
    newPage.data.resize(pageSize);
    newPage.dirty = false;

    inputFile.seekg(pageIndex * pageSize * sizeof(int), std::ios::beg);
    inputFile.read(reinterpret_cast<char*>(newPage.data.data()), pageSize * sizeof(int));

    pages[pageIndex] = std::move(newPage);
    Page* page = &pages[pageIndex];
    pageSlots[std::rand() % 4] = page;

    return page;
}

void PagedArray::unloadPage(Page* page) {
    if (page->dirty) {
        outputFile.seekp(page->index * pageSize * sizeof(int), std::ios::beg);
        outputFile.write(reinterpret_cast<char*>(page->data.data()), pageSize * sizeof(int));
    }
}

void PagedArray::writeToFile(const std::string &outputFilePath) {
    outputFile.open(outputFilePath, std::ios::binary);
    if (!outputFile) {
        throw std::runtime_error("Cannot open output file");
    }

    for (size_t i = 0; i < numPages; ++i) {
        Page* page = loadPage(i);
        outputFile.seekp(page->index * pageSize * sizeof(int), std::ios::beg);
        outputFile.write(reinterpret_cast<char*>(page->data.data()), pageSize * sizeof(int));
    }

    outputFile.close();
}

void PagedArray::writeToTextFile(const std::string &outputFilePath) {
    std::ofstream outFile(outputFilePath);
    if (!outFile) {
        throw std::runtime_error("Cannot open output text file");
    }

    for (size_t i = 0; i < arraySize; ++i) {
        if (i != 0) {
            outFile << ",";
        }
        outFile << (*this)[i];
    }

    outFile.close();
}

void PagedArray::printStats() const {
    std::cout << "Page Hits: " << pageHits << std::endl;
    std::cout << "Page Faults: " << pageFaults << std::endl;
}

size_t PagedArray::size() const {
    return arraySize;
}
