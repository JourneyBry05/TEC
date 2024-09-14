#ifndef MPOINTER_H
#define MPOINTER_H

#include "MPointerGC.h"

template<typename T>
class MPointer {
private:
    T* ptr; // Puntero interno

public:
    // Constructor predeterminado
    MPointer() : ptr(nullptr) {} 

    // Constructor utilizado en caso de usar nullpoint
    MPointer(std::nullptr_t) : ptr(nullptr) {}

    // Método para crear un nuevo MPointer
    static MPointer<T> New() {
        MPointer<T> mp;
        mp.ptr = new T();
        MPointerGC::getInstance()->registerPointer(mp.ptr, &MPointerGC::deletePointer<T>);
        return mp;
    }

    T& operator*() {
        return *ptr;
    }

    T* operator&() {
        return ptr;
    }

    bool operator==(std::nullptr_t) const {
        return ptr == nullptr;
    }

    bool operator!=(std::nullptr_t) const {
        return ptr != nullptr;
    }

    //Incrementar o decrementar referencia con MPointerGC
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

#endif 
