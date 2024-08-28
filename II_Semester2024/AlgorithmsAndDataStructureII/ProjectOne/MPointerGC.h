#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <list>
#include <thread>
#include <mutex>

class MPointerGC{
private:
    std::list<void*> pointers;
    std::list<void*> refCounts;
    static MPointerGC* instance;
    std::mutex gcMutex;

    MPointerGC(){}

public:
    static MPointerGC* getInstance();

    void registerPonter(void* ptr);
    void incrementRef(void* ptr);
    void decrementRef(void* ptr);
    void collectGarbage();
}

#endif