#include <iostream>
#include <fstream> // trabajar con archivos
#include <random> // ayuda a generar numero aleatorios
#include <cstring> // trabajo con caracteres
#include <stdexcept> //manejar excepciones
#include <getopt.h> // analizar algumentos de linea de comando

using namespace std;

// Se definen los valores que puede tomar la enumeracion 'Size' del argumento
enum Size { SMALL, MEDIUM, LARGE };


/*
    Funcion que parsea la cadena de 
    texto correspondiente a cada tamano de archivo en un valor de
    numeracion 'Size', lanza una excepcion con un argumento invalido
*/
Size parseSize(const string &sizeStr) {
    if (sizeStr == "SMALL") return SMALL;
    if (sizeStr == "MEDIUM") return MEDIUM;
    if (sizeStr == "LARGE") return LARGE;
    throw invalid_argument("Invalid size argument");
}

/*
    Devuelve un valor tipo dato sin signo para representar tamano.
    Maneja los casos para los valores de enumeracion 'Size'. Lanza error
    si 'size' no coincide con ninguno de los casos
*/
size_t getSizeInBytes(Size size) {
    switch (size) {
        case SMALL: return 512 * 1024 * 1024; // 512 MB
        case MEDIUM: return 1024 * 1024 * 1024; // 1 GB
        case LARGE: return 2 * 1024 * 1024 * 1024; // 2 GB
    }
    throw invalid_argument("Invalid size");
}

/*
    Responsable de generar el archivo binario con numeros enteros aleatorios
    Se le pasa como argumento una referencia a la ruta del archivo de salida,
    y el tamano del archivo en bytes
*/
void generateFile(const string &outputPath, size_t sizeInBytes) {
    ofstream outFile(outputPath, ios::binary);
    if (!outFile) { // Si falla la apertura del archivo...
        throw ios_base::failure("Failed to open output file");
    }

    random_device rd; //Proporciona entropia para inicializar el generador de num.Aleatorios
    mt19937 gen(rd()); // Motor de generación de números aleatorois Mersenne Twister
    uniform_int_distribution<int> dis; //Genera números enteros en el rango de "int" 

    //Calcula cuantos enteros caben en un tamaño especificado
    size_t numIntegers = sizeInBytes / sizeof(int);
    //En cada iteración se genera un número aleatorio, se escribe en el archivo de salida en binario
    for (size_t i = 0; i < numIntegers; ++i) {
        int randomNumber = dis(gen);
        outFile.write(reinterpret_cast<const char*>(&randomNumber), sizeof(randomNumber));
    }
}

int main(int argc, char *argv[]) {
    // Se define un array de estructuras para las opciones de línea de comando. Comando obligatorio
    static struct option long_options[] = {
        {"size", required_argument, 0, 0},
        {"output", required_argument, 0, 0},
        {0, 0, 0, 0}
    };

    string sizeStr; // Guarda el valor del argumento "--size"
    string outputPath; // Almacena la ruta del archivo de salida


    //Bucle para procesar argumentos de línea de comando
    int option_index = 0;
    int c;
    while ((c = getopt_long(argc, argv, "", long_options, &option_index)) != -1) {
        if (c == 0) {
            if (string(long_options[option_index].name) == "size") {
                sizeStr = optarg;
            } else if (string(long_options[option_index].name) == "output") {
                outputPath = optarg;
            }
        } else {
            cerr << "Usage: " << argv[0] << " --size <SIZE> --output <OUTPUT FILE PATH>\n";
            return EXIT_FAILURE;
        }
    }

    //Verifica que los argumentos --size y --output se hayan proporcionado
    if (sizeStr.empty() || outputPath.empty()) {
        cerr << "Both --size and --output arguments are required\n";
        return EXIT_FAILURE;
    }

    // Intenta ejecutar la lógica principal
    try {
        Size size = parseSize(sizeStr);
        size_t sizeInBytes = getSizeInBytes(size);
        generateFile(outputPath, sizeInBytes);
        cout << "File generated successfully at " << outputPath << "\n";
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
