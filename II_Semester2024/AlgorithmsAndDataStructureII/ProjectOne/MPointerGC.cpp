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
    deleters.push_back(deleter); 
}

void MPointerGC::incrementRef(void* ptr) {
    auto element = std::find(pointers.begin(), pointers.end(), ptr);
    if (element != pointers.end()) {
        auto index = std::distance(pointers.begin(), element);
        auto next = std::next(refCounts.begin(), index);
        (*next)++;
    }
}

void MPointerGC::decrementRef(void* ptr) {
    auto element = std::find(pointers.begin(), pointers.end(), ptr);
    if (element != pointers.end()) {
        auto index = std::distance(pointers.begin(), element);
        auto next = std::next(refCounts.begin(), index);
        auto delElement = std::next(deleters.begin(), index);
        (*next)--;

        if (*next == 0) {
            (*delElement)(*element);  // Llama al deleter para eliminar el puntero
            pointers.erase(element);
            refCounts.erase(next);
            deleters.erase(delElement);
        }
    }
}

void MPointerGC::collectGarbage() {
    auto element = pointers.begin();
    auto next = refCounts.begin();
    auto delElement = deleters.begin();

    while (element != pointers.end()) {
        if (*next == 0) {
            (*delElement)(*element);  // Llama a la función deleter para eliminar el puntero
            element = pointers.erase(element);
            next = refCounts.erase(next);
            delElement = deleters.erase(delElement);
        } else {
            ++element;
            ++next;
            ++delElement;
        }
    }
}
