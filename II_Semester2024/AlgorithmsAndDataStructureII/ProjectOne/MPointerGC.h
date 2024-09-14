#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <list>
#include <functional>

class MPointerGC {
private:
    std::list<void*> pointers;  // Lista de punteros gestionados
    std::list<int> refCounts;   // Lista paralela de contadores de referencias
    std::list<std::function<void(void*)>> deleters;  // Funciones para eliminar punteros del tipo correcto
    static MPointerGC* instance;

    MPointerGC() {}  

public:
    static MPointerGC* getInstance();

    void registerPointer(void* ptr, std::function<void(void*)> deleter);

    void incrementRef(void* ptr);

    void decrementRef(void* ptr);

    void collectGarbage();

    // Plantilla para eliminar punteros del tipo correcto
    template<typename T>
    static void deletePointer(void* ptr) {
        delete static_cast<T*>(ptr);
    }
};

#endif 
