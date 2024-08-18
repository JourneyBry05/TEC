#include <iostream>

using namespace std;



template<typename T>
class Mpointer{
private:
    T* ptr //puntero interno

public:
    MPointer(): ptr(nullptr){} //constructor

    //shallow copy, preguntar
    MPointer<T>& operator=(const Mpointer<T> other){
        if(this!=other){
            delete ptr;
            ptr = other.ptr;
        }
        return *this;
    }

    MPointer<T>& operator=(const T& value) {
        *ptr = value;
        return *this;
    }

    ~MPointer(){delete ptr;} //desctructor

    //Create a new MPointer
    static Mpointer<T> New(){
        MPointer<T> mp;
        mp.ptr = new T();
        return mp;
    }

    T& operator*(){ return *ptr; }

    T operator&(){ return *ptr; }




};



