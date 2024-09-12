#ifndef MPOINTER_H
#define MPOINTER_H

#include "MPointerGC.h"

template<typename T>
class MPointer {
private:
    T* ptr; // Puntero interno

public:
    MPointer() : ptr(nullptr) {} // Constructor

    // Método para crear un nuevo MPointer
    static MPointer<T> New() {
        MPointer<T> mp;
        mp.ptr = new T();
        MPointerGC::getInstance()->registerPointer(mp.ptr, &MPointerGC::deletePointer<T>);
        return mp;
    }

    // Sobrecarga del operador *
    T& operator*() {
        return *ptr;
    }

    // Sobrecarga del operador &
    T* operator&() {
        return ptr;
    }

    // Operador de asignación para MPointer
    MPointer<T>& operator=(const MPointer<T>& other) {
        if (this != &other) {
            MPointerGC::getInstance()->decrementRef(ptr);
            ptr = other.ptr;
            MPointerGC::getInstance()->incrementRef(ptr);
        }
        return *this;
    }

    // Operador de asignación para asignar un valor al puntero
    MPointer<T>& operator=(const T& value) {
        *ptr = value;
        return *this;
    }

    // Destructor
    ~MPointer() {
        MPointerGC::getInstance()->decrementRef(ptr);
    }
};

#endif // MPOINTER_H
