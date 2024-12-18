/* 
 * File:   ArrayStack.h
 * Author: Diego
 *
 * Created on 9 / de març / 2020, 12:08
 */

#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H
#include <initializer_list>
#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

typedef vector<int>::iterator Iterator;

template <class E>

class ArrayStack{
    
private:
    
    enum {DEFAULT_MAX_STACK = 10}; 
    vector<E> S; // stack
    int capacity; 
    int t; // top de la pila 

public:
    
    ArrayStack(int max = DEFAULT_MAX_STACK); // constructor
    ArrayStack(const ArrayStack& orig);      // copy constructor
                                             // inicialitza una pila copiant els elements 
                                             //de la llista que es passa
    
    ArrayStack(initializer_list<E> elements); 
    int size () const;        // retorna el nombre d’elements de la pila  
    bool isEmpty() const;     // indica si la pila és buida 
    bool isFull() const;      // indica si la pila és plena
    const E& top() const ;  // return the top element of stack
    
    // introdueix un element a la pila, 
    //i retorna una excepció si 
    //no ha estat possible
    void push(const E& e); 
    
    // treu un element de la pila, 
    // i retorna una excepció si no ha estat possible
    void pop();  
    
    void print() const; // imprimeix tot el contingut de la pila
};

/**
 * Funcions constructores
 */

//Constructor definint la capacitat màxima de la pila.
template <class E> ArrayStack<E>::ArrayStack(int max) {
    capacity = max;
    t = -1;
}

//Constructor còpia.
template <class E> ArrayStack<E>::ArrayStack(const ArrayStack<E>& orig) {
    t = orig.t;
    S = orig.S;
    capacity = orig.capacity;
}

//Constructor que inicia la pila donada una llista de elements.
template <class E> ArrayStack<E>::ArrayStack(initializer_list<E> elements) {
    capacity = elements.size();
    S.assign(elements);
    t = capacity - 1;
}

/**
 * Funcions consultores
 */

//Retorna el nombre d'elements de la pila.
template <class E> int ArrayStack<E>::size () const {
    return t+1;
}

//Retorna true si la pila està buida.
template <class E> bool ArrayStack<E>::isEmpty() const {
    return t <= -1;
}

//Retorna true si la pila està plena.
template <class E> bool ArrayStack<E>::isFull() const {
    return t >= capacity-1;
}

//Retorna l'element superior de la pila.
template <class E> const E& ArrayStack<E>::top() const {
    return S.at(t);
}

//Imprimeix per pantalla els elements de la pila.
template <class E> void ArrayStack<E>::print() const {
    
    for (int i = size()-1; i >= 0; i--)
        cout << S.at(i) << " ";
    
    cout << endl;
}

/**
 * Funcions modificadores
 */

//Afegeix un element a la pila (llença una excepció si està plena).
template <class E> void ArrayStack<E>::push(const E& e) {
    
    if (isFull())
        throw length_error("No s'ha pogut afegir, la pila està plena.\n");

    else {
        S.push_back(e);
        t += 1;
    }
}

//Elimina un element de la pila (llença una excepció si està buida).
template <class E> void ArrayStack<E>::pop() {
   
    if (isEmpty())
        throw length_error("No s'ha pogut treure, la pila està buida.\n");

    else {
        S.pop_back();
        t -= 1;
    }
}
#endif /* ARRAYSTACK_H */