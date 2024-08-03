#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

void generateBinaryFile(const std::string &filePath, int numIntegers) {
    std::ofstream outFile(filePath, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening file for writing: " << filePath << std::endl;
        return;
    }

    std::srand(std::time(nullptr));
    for (int i = 0; i < numIntegers; ++i) {
        int randomInt = std::rand();
        outFile.write(reinterpret_cast<char*>(&randomInt), sizeof(randomInt));
    }

    outFile.close();
}

int main() {
    std::string filePath = "input.bin";
    int numIntegers = 1000; // Modify as needed
    generateBinaryFile(filePath, numIntegers);
    std::cout << "Binary file generated: " << filePath << std::endl;
    return 0;
}
