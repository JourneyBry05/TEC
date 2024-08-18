#include <iostream>

using namespace std;



template<typename T>
class Mpointer{
private:
    T* ptr //puntero interno

public:
    MPointer(): ptr(nullptr){} //constructor

    ~MPointer(){delete ptr;} //desctructor

    //Create a new MPointer
    static Mpointer<T> New(){
        MPointer<T> mp;
        mp.ptr = new T();
        return mp;
    }

    T& operator*(){return *ptr;} //// Operator overloading *
};

