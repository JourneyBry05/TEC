/*
Code that generates a .bin file with random integers in binary mode
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
The function receives the 'FilePath' where the numbers will be saved, and 
the 'numIntegers' that will be generated and written to the file
*/
void generateBinaryFile(const string &filePath, int numIntegers) {
    ofstream outFile(filePath, ios::binary);
    if (!outFile) {
        cerr << "Error opening file for writing: " << filePath << endl;
        return;
    }
    //Initialize the num generator
    srand(time(nullptr));

    //Iterate 'numIntegers' times to generate and write random numbers to file
    for (int i = 0; i < numIntegers; ++i) {
        int randomInt = rand(); //Generate a random integer
        //Write the integer as a sequence of bytes
        outFile.write(reinterpret_cast<char*>(&randomInt), sizeof(randomInt));
    }

    outFile.close();
}

int main() {
    string filePath = "input.bin"; //filePath will be saved as input.bin
    int numIntegers = 1000; // How many numbers will be generated
    generateBinaryFile(filePath, numIntegers);
    cout << "Binary file generated: " << filePath << endl; //If file was created successfully...
    return 0;
}
