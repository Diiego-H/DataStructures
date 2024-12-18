/* 
 * File:   Tuple.h
 * Author: Diego Hernández
 *
 * Created on 29 de abril de 2020, 19:23
 */

#ifndef TUPLE_H
#define TUPLE_H

template <class E, class F>

//Especificació TAD Tuple
class Tuple {
public:
    
    Tuple(E& elem1, F& elem2);
    
    const E& getElem1() const;
    const F& getElem2() const;
    
    bool operator<(const Tuple& other) const;
    bool operator==(const Tuple& other) const;
    
    void setElem1(E& elem1);
    void setElem2(F& elem2);
    
private:
    E elem1;
    F elem2;
};

/*
 * Funció constructora
 */

//Constructor amb totes les dades.
template <class E, class F> Tuple<E,F>::Tuple(E& elem1, F& elem2) {
    this->elem1 = elem1;
    this->elem2 = elem2;
}

//Es retorna el primer element guardat al Tuple.
template <class E, class F> const E& Tuple<E,F>::getElem1() const {
    return elem1;
}

//Es retorna el segon element guardat al Tuple.
template <class E, class F> const F& Tuple<E,F>::getElem2() const {
    return elem2;
}

//Es retorna cert si el primer element de la Tuple és menor que el primer
//de la passada per paràmetre o, si els primers elements són iguals, el
//segon element de la Tuple és menor que el segon de la passada.
template <class E, class F> bool Tuple<E,F>::operator<(const Tuple& other) const {
    E e1 = this->getElem1(), e2 = other.getElem1();
    F f1 = this->getElem2(), f2 = other.getElem2();
    
    return e1 <= e2 and (e1 < e2 or f1 < f2);
}

//Es retorna cert si els valors guardats en aquesta Tuple són iguals als
//guardats en la passada per paràmetre.
template <class E, class F> bool Tuple<E,F>::operator==(const Tuple& other) const {
    return this->getElem1() == other.getElem1() and 
           this->getElem2() == other.getElem2();
}

/*
 * Funcions modificadores
 */

//Es modifica el primer element de la Tuple.
template <class E, class F> void Tuple<E,F>::setElem1(E& elem) {
    elem1 = elem;
}

//Es modifica el segon element de la Tuple.
template <class E, class F> void Tuple<E,F>::setElem2(F& elem) {
    elem2 = elem;
}

#endif /* TUPLE_H */