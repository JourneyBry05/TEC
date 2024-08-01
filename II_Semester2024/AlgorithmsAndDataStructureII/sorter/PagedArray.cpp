#include "PagedArray.h"

PagedArray::PagedArray(const std::string &filePath, size_t pageSize)
    :filePath(filePath), pageSize(pageSize), pageFaults(0), pageHits(0){
        std::ifstream file(filePath, std::ios::binary | std::ios::ate);
        if (!file){
            throw std::runtime_error("Failed to open file");
        }
        size_t fileSize = file.tellg();
        numPages - (fileSize + pageSize - 1)/pageSize;
        file.close();

PagedArray::~PagedArray() {
    for (size_t i = 0; i < pages.size(); ++i) {
        if (pages[i]) {
            unloadPage(i);
            delete[] pages[i];
        }
    }
}

int PagedArray::operator[](size_t index){
    size_t pageIndex = getPageIndex(index);
    size_t offset = getOffset(index);

    if(pageTable.find(pageIndex) != pageTable.end()){
        ++pageHits;
        return pageTable[pageIndex][offset];
    } else {
        ++pageFaults;
        loadPage(pageIndex);
        return pageTable[pageIndex][offset];
    }
}

void PagedArray::set(size_t index, int value){
    size_t PageIndex = getPageIndex(index);
    size_t offset = getOffset(index);

    if(pageTable.find(pageIndex) != pageTable.end()){
        ++pageHits;
        pageTable[pageIndex][offset] = value;
    } else{
        ++pageFaults;
        loadPage(pageIndex);
        pageTable[pageIndex][offset] = value;
    }
}

void PagedArray::loadPage(size_t pageIndex){
    if (pageTable.size()==4){
        size_t pageToUnload = std::rand() % 4;
        auto it = std::next(pageTable.begin(), pageToUnload);
        unloadPage(it->first);
        unloadPage(it->second);
        pageTable.erase(it);
    }

    int* pageData = new int[pageSize];
    std::ifstream file(filePath, std::ios::binary);
    file.seekg(pageIndex * pageSize * sizeof(int));
    file.read(reinterpret_cast<char*>(pageData), pageSize * sizeof(int));
    pageTable[pageIndex] =  pageData;
}

void pagedArray::unloadPage(size_t pageIndex){
    int* pageData = pageTable[pageIndex];
    std::pfstream file(filePath, std::ios::binary | std::ios::in | std::ios::out);
    file.seekp(pageIndex * pageSize * sizeof(int));
    file.write(reinterpret_cast<const char*>(pageData), pageSize * sizeof(int));
}