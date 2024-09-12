#include "MPointer.h"
#include <iostream>

int main() {
    // Prueba 1: MPointer con tipo int
    std::cout << "Prueba con int:" << std::endl;
    MPointer<int> pInt = MPointer<int>::New();
    *pInt = 42;
    std::cout << "Valor en pInt: " << *pInt << std::endl;

    // Prueba 2: MPointer con tipo float
    std::cout << "\nPrueba con float:" << std::endl;
    MPointer<float> pFloat = MPointer<float>::New();
    *pFloat = 3.14f;
    std::cout << "Valor en pFloat: " << *pFloat << std::endl;

    // Prueba 3: MPointer con tipo double
    std::cout << "\nPrueba con double:" << std::endl;
    MPointer<double> pDouble = MPointer<double>::New();
    *pDouble = 2.7182818284;
    std::cout << "Valor en pDouble: " << *pDouble << std::endl;

    // Prueba 4: MPointer con tipo char
    std::cout << "\nPrueba con char:" << std::endl;
    MPointer<char> pChar = MPointer<char>::New();
    *pChar = 'A';
    std::cout << "Valor en pChar: " << *pChar << std::endl;

    // Prueba de asignación de punteros
    MPointer<int> pInt2 = MPointer<int>::New();
    *pInt2 = 100;
    std::cout << "\nValor en pInt2 antes de la asignación: " << *pInt2 << std::endl;

    // Asignar pInt a pInt2
    pInt2 = pInt;
    std::cout << "Valor en pInt2 después de la asignación: " << *pInt2 << std::endl;

    // Colectar basura manualmente
    MPointerGC::getInstance()->collectGarbage();

    return 0;
}
