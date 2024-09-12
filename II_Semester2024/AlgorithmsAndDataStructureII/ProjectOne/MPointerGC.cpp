#include "MPointerGC.h"
#include <algorithm>

MPointerGC* MPointerGC::instance = nullptr;

MPointerGC* MPointerGC::getInstance() {
    if (instance == nullptr) {
        instance = new MPointerGC();
    }
    return instance;
}

void MPointerGC::registerPointer(void* ptr, std::function<void(void*)> deleter) {
    pointers.push_back(ptr);
    refCounts.push_back(1);  // Inicializa el contador de referencias en 1
    deleters.push_back(deleter);  // Guarda la función deleter para eliminar correctamente
}

void MPointerGC::incrementRef(void* ptr) {
    auto it = std::find(pointers.begin(), pointers.end(), ptr);
    if (it != pointers.end()) {
        auto index = std::distance(pointers.begin(), it);
        auto refIt = std::next(refCounts.begin(), index);
        (*refIt)++;
    }
}

void MPointerGC::decrementRef(void* ptr) {
    auto it = std::find(pointers.begin(), pointers.end(), ptr);
    if (it != pointers.end()) {
        auto index = std::distance(pointers.begin(), it);
        auto refIt = std::next(refCounts.begin(), index);
        auto delIt = std::next(deleters.begin(), index);
        (*refIt)--;

        if (*refIt == 0) {
            (*delIt)(*it);  // Llama al deleter para eliminar el puntero
            pointers.erase(it);
            refCounts.erase(refIt);
            deleters.erase(delIt);
        }
    }
}

void MPointerGC::collectGarbage() {
    auto it = pointers.begin();
    auto refIt = refCounts.begin();
    auto delIt = deleters.begin();

    while (it != pointers.end()) {
        if (*refIt == 0) {
            (*delIt)(*it);  // Llama a la función deleter para eliminar el puntero
            it = pointers.erase(it);
            refIt = refCounts.erase(refIt);
            delIt = deleters.erase(delIt);
        } else {
            ++it;
            ++refIt;
            ++delIt;
        }
    }
}
