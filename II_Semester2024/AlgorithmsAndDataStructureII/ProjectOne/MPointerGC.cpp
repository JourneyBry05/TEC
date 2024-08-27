#include <list>
#include <thread>
#include <mutex>

class MPointerGC {
private:
    std::list<void*> pointers;
    static MPointerGC* instance;
    std::mutex gcMutex;

    MPointerGC (){}

public:
    static MPointerGC getInstance(){
        if (instance == nullptr){
            instance = new MPointerGC();
        } 
        return instance;
    }

    void registerPointer(void* ptr){
        std::lock_guard<std::mutex> lock(gcMutex);
        pointers.push_back(ptr)
    }

    void unregisterPointer(void* ptr){
        std::lock_guard<std::mutex> lock(gcMutex);
        pointers.remove(ptr);
    }

    void collectGarbaje(){


    }
};
MPointerGC* MPointerGC::instance = nullptr;