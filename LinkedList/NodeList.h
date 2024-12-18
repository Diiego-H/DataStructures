/* 
 * File:   NodeList.h
 * Author: Diego Hernández
 *
 * Created on 18 de marzo de 2020, 12:16
 */

#ifndef NODELIST_H
#define NODELIST_H

template <class Element>

class NodeList {
public:
    NodeList();
    NodeList(Element);
    const Element& getElement() const;
    NodeList<Element>* getNext() const;
    void setNext(NodeList<Element>* newNext);
    NodeList<Element>* getPrevious() const;
    void setPrevious(NodeList<Element>* newPrevious);
    
private:
    Element element;
    NodeList<Element>* previous;
    NodeList<Element>* next;
};

/**
 * Funcions constructores
 */

//Constructor per defecte, crea un node sense element.
template <class Element> NodeList<Element>::NodeList() {
}

//Constructor, es crea un node amb un element donat.
template <class Element> NodeList<Element>::NodeList(Element e) {
    element = e;
}

/**
 * Funcions consultores
 */

//Retorna l'element guardat al node.
template <class Element> const Element& NodeList<Element>::getElement() const {
    return element;
}

//Retorna un punter amb la direcció del node que guarda l'anterior element.
template <class Element> NodeList<Element>* NodeList<Element>::getPrevious() const {
    return previous;
}

//Retorna un punter amb la direcció del node que guarda el següent element.
template <class Element> NodeList<Element>* NodeList<Element>::getNext() const {
    return next;
}

/**
 * Funcions modificadores
 */

//Estableix quin és el node posterior.
template <class Element> void NodeList<Element>::setNext(NodeList<Element>* newNext) {
    next = newNext;
}

//Estableix quin és el node anterior.
template <class Element> void NodeList<Element>::setPrevious(NodeList<Element>* newPrevious) {
    previous = newPrevious;
}

#endif /* NODELIST_H */