#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "MPointer.h"

template<typename T>
class Node {
public:
    T data;
    MPointer<Node<T>> next;
    MPointer<Node<T>> prev;

    // Constructor por defecto
    Node() : next(nullptr), prev(nullptr) {}

    // Constructor con valor
    Node(T value) : data(value), next(nullptr), prev(nullptr) {}
};


template<typename T>
class LinkedList {
private:
    MPointer<Node<T>> head;
    MPointer<Node<T>> last;
    int size;

public:
    LinkedList() : head(nullptr), last(nullptr), size(0) {}

    // Insertar al final de la lista
    void append(T value) {
        MPointer<Node<T>> newNode = MPointer<Node<T>>::New();
        *newNode = Node<T>(value);
        
        if (last == nullptr) {
            head = newNode;
            last = newNode;
        } else {
            (*last).next = newNode;
            (*newNode).prev = last;
            last = newNode;
        }
        size++;
    }

    // Obtener tamaño de la lista
    int getSize() const {
        return size;
    }

    // Obtener el nodo en la posición indicada
    Node<T>* getNode(int index) {
        if (index < 0 || index >= size) return nullptr;
        
        MPointer<Node<T>> current = head;
        for (int i = 0; i < index; i++) {
            current = (*current).next;
        }
        return &(*current);  // Retornar el puntero crudo
    }

    // Intercambiar los datos entre dos nodos
    void swap(Node<T>* a, Node<T>* b) {
        T temp = a->data;
        a->data = b->data;
        b->data = temp;
    }
};

#endif 