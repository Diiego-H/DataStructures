/* 
 * File:   LinkedList.h
 * Author: Diego Hernández
 *
 * Created on 18 de marzo de 2020, 12:07
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <initializer_list>
#include "Position.h"

template <class Element>

class LinkedList {
    
public:
    LinkedList();
    LinkedList(std::initializer_list<Element> elements);
    LinkedList(const LinkedList<Element>& list);
    virtual ~LinkedList();
    
    int size() const;
    bool isEmpty() const;
    
    Position<Element> begin() const; // return first position
    Position<Element> end() const;   // return last position
    
    void insertFront(const Element & element);
    void insertBack(const Element & element);
    void insertAfter(Position<Element>& position, const Element &element);
    void insertBefore(Position<Element>& position, const Element &element);
    
    void print() const;
    
private:
    NodeList<Element>* head;
    NodeList<Element>* rear;
    int _size;
};

/**
 * Funcions constructores
 */

//Constructor per defecte, crea els sentinelles.
template <class Element> LinkedList<Element>::LinkedList() {
    head = new NodeList<Element>();
    rear = new NodeList<Element>();
    head->setNext(rear);
    head->setPrevious(nullptr);
    rear->setPrevious(head);
    rear->setNext(nullptr);
    _size = 0;
}

//Constructor que inicialitza una llista amb els elements donats.
template <class Element> LinkedList<Element>::LinkedList(std::initializer_list<Element> elements):LinkedList<Element>() {
    typename std::initializer_list<Element>::iterator it;
    
    for(it = elements.begin(); it != elements.end(); ++it)
        insertBack(*it);
}

//Constructor còpia.
template <class Element> LinkedList<Element>::LinkedList(const LinkedList<Element>& list):LinkedList<Element>() {
    for (Position<Element> itr = list.begin(); itr != list.end(); itr = ++itr)
        insertBack(*itr);
}

/**
 * Funció destructora
 */

//Destructor, s'eliminen tots els nodes i, per últim, els sentinelles.
template <class Element> LinkedList<Element>::~LinkedList() {
    if (!isEmpty()) {
        NodeList<Element>* itr = head->getNext();
        while (itr != rear) {
            itr = itr->getNext();
            delete itr->getPrevious();
        }
    }
    
    delete head;
    delete rear;
}

/**
 * Funcions consultores
 */

//Retorna el nombre d'elements de la llista.
template <class Element> int LinkedList<Element>::size() const {
    return _size;
}

//Retorna true si la llista està buida.
template <class Element> bool LinkedList<Element>::isEmpty() const {
    return _size == 0;
}

//Retorna la posició del primer element.
template <class Element> Position<Element> LinkedList<Element>::begin() const {
    Position<Element> beginPos(head->getNext());
    return beginPos;
}

//Retorna la posició posterior de l'últim element.
template <class Element> Position<Element> LinkedList<Element>::end() const {
    Position<Element> endPos(rear);
    return endPos;
}

//Mostra per pantalla tots els elements de la llista.
template <class Element> void LinkedList<Element>::print() const {
    for (Position<Element> itr = begin(); itr != end(); itr = ++itr)
        std::cout << *itr << " ";
    std::cout << std::endl;
}

/**
 * Funcions modificadores
 */

//Inserta un element a l'inici de la llista.
template <class Element> void LinkedList<Element>::insertFront(const Element& element) {
    NodeList<Element>* tmp = head->getNext();
    NodeList<Element>* insert = new NodeList<Element>(element);
    head->setNext(insert);
    insert->setPrevious(head);
    tmp->setPrevious(insert);
    insert->setNext(tmp);
    _size++;
}

//Inserta un element al final de la llista.
template <class Element> void LinkedList<Element>::insertBack(const Element& element) {
    NodeList<Element>* tmp = rear->getPrevious();
    NodeList<Element>* insert = new NodeList<Element>(element);
    rear->setPrevious(insert);
    insert->setNext(rear);
    tmp->setNext(insert);
    insert->setPrevious(tmp);
    _size++;
}

//Inserta un element a la posició posterior d'una donada.
template <class Element> void LinkedList<Element>::insertAfter(Position<Element>& position, const Element& element) {
    Position<Element> itrPos = begin();
    NodeList<Element>* itrNod = head->getNext();
    
    while (position != itrPos && itrPos != end()) {
        itrPos = ++itrPos;
        itrNod = itrNod->getNext();
    }
    
    if (position == itrPos) {
        Position<Element> nextPos = itrPos.next();
        NodeList<Element>* tmp = new NodeList<Element>(element);
        tmp->setNext(itrNod->getNext());
        tmp->setPrevious(itrNod);
        nextPos.setPrevious(tmp);
        itrPos.setNext(tmp);
        _size++;
    } else
        std::cout << "L'element no es troba a la llista.\n";
}

//Inserta un element a la posició anterior d'una donada.
template <class Element> void LinkedList<Element>::insertBefore(Position<Element>& position, const Element& element) {
    Position<Element> itrPos = begin();
    NodeList<Element>* itrNod = head->getNext();
    
    while (position != itrPos && itrPos != end()) {
        itrPos = ++itrPos;
        itrNod = itrNod->getNext();
    }
    
    if (position == itrPos) {
        Position<Element> previousPos = itrPos.previous();
        NodeList<Element>* tmp = new NodeList<Element>(element);
        tmp->setPrevious(itrNod->getPrevious());
        tmp->setNext(itrNod);
        previousPos.setNext(tmp);
        itrPos.setPrevious(tmp);
        _size++;
    } else
        std::cout << "L'element no es troba a la llista.\n";
}
#endif /* LINKEDLIST_H */