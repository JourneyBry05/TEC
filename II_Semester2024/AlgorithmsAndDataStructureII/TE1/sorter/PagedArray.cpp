/*
Manages a large array of integers using pagination
*/

#include "PagedArray.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <fstream> 

/*
Initializes an object of class 'PagedArray' by reading data from a binary file
filePath: path to the binary file that stores the data
pageSize: size of each page on 'PagedArray'
*/
PagedArray::PagedArray(const std::string &filePath, size_t pageSize)
    : pageSize(pageSize), pageFaults(0), pageHits(0) {
    inputFile.open(filePath, std::ios::binary);
    if (!inputFile) {
        throw std::runtime_error("Cannot open input file");
    }

    inputFile.seekg(0, std::ios::end);
    size_t fileSize = inputFile.tellg();
    arraySize = fileSize / sizeof(int); // Calculating array size
    numPages = (fileSize + pageSize * sizeof(int) - 1) / (pageSize * sizeof(int)); //Calculating number of pages
    inputFile.seekg(0, std::ios::beg);

    //Initializing Page Slots
    for (auto &slot : pageSlots) {
        slot = nullptr;
    }
}
/*
Clean up resources associated with the 'PagedArray' object when it's destroyed
*/
PagedArray::~PagedArray() {
    for (auto &slot : pageSlots) {
        if (slot && slot->dirty) {
            unloadPage(slot); // Calls 'unloadPage' function to write the modified page back to the file 
        }
    }
    inputFile.close();
    if (outputFile.is_open()) {
        outputFile.close();
    }
}

/*
Provides access to the elements of the paginated array
*/
int& PagedArray::operator[](size_t index) {
    size_t pageIndex = index / pageSize; //Calculate the index of the page that stores the element
    size_t offset = index % pageSize; //Calculates the offset of the element within the page

    for (auto &slot : pageSlots) {
        if (slot && slot->index == pageIndex) {
            ++pageHits;
            return slot->data[offset];
        }
    }

    ++pageFaults;
    Page* page = loadPage(pageIndex); //Calls the 'loadPage' to load the page that contains the index
    return page->data[offset];
}


/*
Responsible for loading a page of data from the file into memory
*/
PagedArray::Page* PagedArray::loadPage(size_t pageIndex) {
    if (pages.count(pageIndex)) {
        return &pages[pageIndex];
    }
    //Page replacement if memory is full
    if (pages.size() >= 4) {
        size_t randomIndex = std::rand() % 4;
        Page* oldPage = pageSlots[randomIndex];
        unloadPage(oldPage);
        pages.erase(oldPage->index);
    }
    //New Page Load
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

/*
Writes a page of data to the file if it was modified
'Page' contains the page data to download
 */
void PagedArray::unloadPage(Page* page) {
    if (page->dirty) {
        outputFile.seekp(page->index * pageSize * sizeof(int), std::ios::beg);
        outputFile.write(reinterpret_cast<char*>(page->data.data()), pageSize * sizeof(int));
    }
}
/*
Writes the content of 'PagedArray' to a binary file specified by 'outputFilePath'
*/
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
/*
Writes the contents of the PagedArray to a text file, with the elements separated by commas
 */
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
/*
Print statistics about the page hits and page faults of the PagedArray.
*/
void PagedArray::printStats() const {
    std::cout << "Page Hits: " << pageHits << std::endl;
    std::cout << "Page Faults: " << pageFaults << std::endl;
}
/*
Returns the total size of the PagedArray, stored in the arraySize member.
*/
size_t PagedArray::size() const {
    return arraySize;
}
