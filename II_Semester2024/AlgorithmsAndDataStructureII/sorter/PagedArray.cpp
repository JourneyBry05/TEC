#include "PagedArray.h"

PagedArray::PagedArray(const std::string &filePath, size_t pageSize)
    : filePath(filePath), pageSize(pageSize), pageFaults(0), pageHits(0) {
    // Open file and calculate number of pages
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file) {
        throw std::runtime_error("Failed to open file.");
    }
    size_t fileSize = file.tellg();
    numPages = (fileSize + pageSize - 1) / pageSize;
    pages.resize(4, nullptr);
    file.close();
}

PagedArray::~PagedArray() {
    // Unload all loaded pages and save them to disk
    for (size_t i = 0; i < pages.size(); ++i) {
        if (pages[i]) {
            unloadPage(i);
            delete[] pages[i];
        }
    }
}

int PagedArray::operator[](size_t index) {
    size_t pageIndex = getPageIndex(index);
    size_t offset = getOffset(index);

    if (pageTable.find(pageIndex) != pageTable.end()) {
        // Page hit
        ++pageHits;
        return pageTable[pageIndex][offset];
    } else {
        // Page fault
        ++pageFaults;
        loadPage(pageIndex);
        return pageTable[pageIndex][offset];
    }
}

void PagedArray::set(size_t index, int value) {
    size_t pageIndex = getPageIndex(index);
    size_t offset = getOffset(index);

    if (pageTable.find(pageIndex) != pageTable.end()) {
        // Page hit
        ++pageHits;
        pageTable[pageIndex][offset] = value;
    } else {
        // Page fault
        ++pageFaults;
        loadPage(pageIndex);
        pageTable[pageIndex][offset] = value;
    }
}

void PagedArray::loadPage(size_t pageIndex) {
    if (pageTable.size() == 4) {
        // Choose a page to unload randomly
        size_t pageToUnload = std::rand() % 4;
        auto it = std::next(pageTable.begin(), pageToUnload);
        unloadPage(it->first);
        delete[] it->second;
        pageTable.erase(it);
    }

    // Load the new page
    int* pageData = new int[pageSize];
    std::ifstream file(filePath, std::ios::binary);
    file.seekg(pageIndex * pageSize * sizeof(int));
    file.read(reinterpret_cast<char*>(pageData), pageSize * sizeof(int));
    pageTable[pageIndex] = pageData;
}

void PagedArray::unloadPage(size_t pageIndex) {
    int* pageData = pageTable[pageIndex];
    std::ofstream file(filePath, std::ios::binary | std::ios::in | std::ios::out);
    file.seekp(pageIndex * pageSize * sizeof(int));
    file.write(reinterpret_cast<const char*>(pageData), pageSize * sizeof(int));
}
