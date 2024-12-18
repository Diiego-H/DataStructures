/* 
 * File:   Position.h
 * Author: Diego Hernández
 *
 * Created on 18 de marzo de 2020, 13:12
 */

#ifndef POSITION_H
#define POSITION_H
#include <stdexcept>
#include "NodeList.h"

template <class Element>

class Position {
public:
    
    Position(NodeList<Element>* node);                  // Constructor amb paràmetres
    
    Position<Element> next() const;                     // retorna la següent posició
    Position<Element> previous() const;                 // retorna l’anterior posició
    const Element& element() const;                     // retorna el contingut de l’actual posició
    void setPrevious(NodeList<Element> *node);          // assigna l’adreça de l’anterior node
    void setNext(NodeList<Element> *node);              // assigna l’adreça del següent node
    
    Position<Element> operator++() const;               // sobrecarrega operador ++
    bool operator==(const Position & other) const;      // sobrecarrega operador ==
    bool operator!=(const Position & other) const;      // sobrecarrega operador !=
    const Element& operator*() const;                   // sobrecarrega operador contingut

private:
    NodeList<Element>* node;
};

/**
 * Funció constructora
 */

//Constructor, crea una posició que encapsula un node donat.
template <class Element> Position<Element>::Position(NodeList<Element>* node) {
    this->node = node;
}

/**
 * Funcions consultores
 */

//Retorna la següent posició.
template <class Element> Position<Element> Position<Element>::next() const {
    Position<Element> nextPos(node->getNext());
    return nextPos;
}

//Retorna l'anterior posició.
template <class Element> Position<Element> Position<Element>::previous() const {
    Position<Element> prevPos(node->getPrevious());
    return prevPos;
}

//Retorna l'element guardat a la posició.
template <class Element> const Element& Position<Element>::element() const {
    return node->getElement();
}

/**
 * Funcions modificadores
 */

//Estableix quina és la posició anterior.
template <class Element> void Position<Element>::setPrevious(NodeList<Element>* node) {
    (this->node)->setPrevious(node);
}

//Estableix quina és la posició posterior.
template <class Element> void Position<Element>::setNext(NodeList<Element>* node) {
    (this->node)->setNext(node);
}

/**
 * Sobrecàrregues d'operadors
 */

//Retorna la següent posició.
template <class Element> Position<Element> Position<Element>::operator ++() const {
    return next();
}

//Retorna true si els nodes de les posicions guarden la mateixa adreça.
template <class Element> bool Position<Element>::operator ==(const Position& other) const {
    return this->node == other.node;
}

//Retorna true si els nodes de les posicions guarden diferents adreces.
template <class Element> bool Position<Element>::operator !=(const Position& other) const {
    return this->node != other.node;
}

//Retorna el contingut d'una posició (l'element que guarda).
template <class Element> const Element& Position<Element>::operator *() const {
    return element();
}

#endif /* POSITION_H */