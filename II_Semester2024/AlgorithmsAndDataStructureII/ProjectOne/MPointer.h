#ifndef MPOINTER_H
#define MPOINTER_H

template<typename T>
class MPointer{
private:
    T* ptr; //puntero interno
public:
    MPointer(): ptr(nullptr){} //constructor

    static MPointer<T> New(){
        MPointer<T> mp;
        mp.ptr = new T();
        return mp
    }

    T& operator*(){return *ptr}
    T* operator&(){return *ptr}

    MPointer<T>& operator=(const MPointer<T>& other){
        //something goes here
    }

    ~MPointer(){
        
    }
}