/* 
 * File:   BSTree.h
 * Author: Diego Hernández
 *
 * Created on 20 de abril de 2020, 19:50
 */

#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include "Position.h"

template <class K, class V>

class BSTree {
public:
    
    //Constructor i constructor còpia
    BSTree();
    BSTree(const BSTree<K,V>& orig);
    
    //Destructor
    virtual ~BSTree();
    
    //Funcions consultores
    bool isEmpty() const;
    Position<K,V>* getRoot() const;
    int size() const;
    int sizeRec() const;
    int height() const;
    
    bool contains(const K& key) const;
    const std::vector<V>& getValues(const K& key) const;
    
    void printPreOrder(const Position<K,V>* pos = nullptr) const;
    void printPostOrder(const Position<K,V>* pos = nullptr) const;
   
    bool identicalTree(const BSTree<K,V>& other) const;
    
    //Funció modificadora
    virtual Position<K,V>* insert(const K& key, const V& value);
    
protected:    
    
    //Arrel de l'arbre
    Position<K,V>* root;
    
private:
    
    //Tamany de l'arbre
    int _size;
    
    //Mètodes privats (funcions auxiliars necessàries per fer recursions i search)
    Position<K,V>* search(const K& key) const;
    Position<K,V>* searchAux(const K& key, Position<K,V>* pos) const;
    int sizeAux(const Position<K,V>* pos) const;
    bool identicalAux(const Position<K,V>* pos1, const Position<K,V>* pos2) const;
};

/**
 * Funcions constructores
 */

//Constructor per defecte. Cost O(1)
template <class K, class V> BSTree<K,V>::BSTree() {
    root = nullptr;
    _size = 0;
}

//Constructor còpia. Cost O(n) (es copien totes les Position de l'arbre orig)
template <class K, class V> BSTree<K,V>::BSTree(const BSTree<K,V>& orig) {
    if (orig.isEmpty()) 
        throw std::logic_error("L'arbre està buit!");
    else {
        root = new Position<K,V>(*orig.getRoot());
        _size = orig._size;
    }
}

/**
 * Funció destructora
 */

//Destructor, s'inicia una destrucció en cadena de l'arbre, que inicia a l'arrel. Cost O(n)
template <class K, class V> BSTree<K,V>::~BSTree() {
    delete root;
}

/**
 * Funcions consultores
 */

//Es retorna cert si l'arbre està buit, fals en cas contrari. Cost O(1)
template <class K, class V> bool BSTree<K,V>::isEmpty() const {
    return getRoot() == nullptr;
}

//Es retorna l'adreça de l'arrel de l'arbre. Cost O(1)
template <class K, class V> Position<K,V>* BSTree<K,V>::getRoot() const {
    return root;
}

//Es retorna el nombre de nodes de l'arbre. Cost O(1)
template <class K, class V> int BSTree<K,V>::size() const {
    return _size;
}

//Es retorna el nombre de nodes de l'arbre (es calcula recursivament fent un recorregut en pre-ordre). Cost O(n)
template <class K, class V> int BSTree<K,V>::sizeRec() const {
    return sizeAux(getRoot());
}

//Es calcula recursivament el nombre de Position de l'arbre. Cost per recursió O(1), cost total O(n)
template <class K, class V> int BSTree<K,V>::sizeAux(const Position<K,V>* pos) const{
    if (pos == nullptr)
        return 0;
    else
        return 1 + sizeAux(pos->left()) + sizeAux(pos->right());
}

//Es retorna l'alçada de l'arbre, inicia un càlcul recursiu des de l'arrel. Cost O(n)
template <class K, class V> int BSTree<K,V>::height() const {
    if (isEmpty())
        throw std::logic_error("L'arbre està buit!");
    else
        return getRoot()->height();
}

//Es retorna cert si l'arbre conté la Key, fals en cas contrari. Cost O(n) (si l'arbre és lineal)
template <class K, class V> bool BSTree<K,V>::contains(const K& key) const {
    Position<K,V>* pos = getRoot();
    bool trobat = false;
    
    while (pos != nullptr && !trobat) {
        if (key == pos->getKey())
            trobat = true;
        else if (key < pos->getKey())
            pos = pos->left();
        else
            pos = pos->right();
    }
    
    return trobat;
}

//Es cerca una clau a l'arbre, es retorna la Position si la troba, nullptr en cas contrari. Cost O(n) (si l'arbre és lineal)
template <class K, class V> Position<K,V>* BSTree<K,V>::search(const K& key) const {
    return searchAux(key, getRoot());
}

//Es cerca recursivament una clau a l'arbre. Cost per recursió O(1), cost total O(n)
template <class K, class V> Position<K,V>* BSTree<K,V>::searchAux(const K& key, Position<K,V>* pos) const {
    if (pos == nullptr || key == pos->getKey())
        return pos;
    else if (key < pos->getKey())
        return searchAux(key, pos->left());
    else
        return searchAux(key, pos->right());
}

//Es retorna un vector amb tots els valors associats a una clau. Es llença una excepció si no es troba la clau a l'arbre. Cost O(n) (cost O(1) retornar el valor però O(n) trobar la Position)
template <class K, class V> const std::vector<V>& BSTree<K,V>::getValues(const K& key) const {
    if (!contains(key))
        throw std::logic_error("La clau no es troba a l'arbre!");
    else
        return search(key)->getValues();
}

//Es mostra per consola el contingut de l'arbre seguint un recorregut en pre-ordre. Cost per recursió O(1), cost total O(n)
template <class K, class V> void BSTree<K,V>::printPreOrder(const Position<K,V>* pos) const {
    if (pos == nullptr) {
        std::cout << "\tPreordre = {";
        
        if (!isEmpty()) {
            Position<K,V>* pos = getRoot();
            std::cout << pos->getKey();
            
            if (pos->left() != nullptr)
                printPreOrder(pos->left());
            if (pos->right() != nullptr)
                printPreOrder(pos->right());
        }
        
        std::cout << "}\n";
    } else {
        std::cout << ", " << pos->getKey();
        
        if (pos->left() != nullptr)
            printPreOrder(pos->left());
        if (pos->right() != nullptr)
            printPreOrder(pos->right());
    }
}

//Es mostra per consola el contingut de l'arbre seguint un recorregut en post-ordre. Cost per recursió O(1), cost total O(n)
template <class K, class V> void BSTree<K,V>::printPostOrder(const Position<K,V>* pos) const {
    if (pos == nullptr) {
        std::cout << "\tPostordre = {";
        
        if (!isEmpty()) {
            Position<K,V>* pos = getRoot();
            
            if (pos->left() != nullptr)
                printPostOrder(pos->left());
            if (pos->right() != nullptr)
                printPostOrder(pos->right());
            
            std::cout << pos->getKey();
        }
        
        std::cout << "}\n";
    } 
    else {
        if (pos->left() != nullptr)
            printPostOrder(pos->left());
        if (pos->right() != nullptr)
            printPostOrder(pos->right());
        
        std::cout << pos->getKey() << ", ";
    }
}

//Es retorna cert si l'arbre binari és igual al passat per paràmetre, fals en cas contrari. Cost O(n)
template <class K, class V> bool BSTree<K,V>::identicalTree(const BSTree<K,V>& other) const {
    return identicalAux(this->getRoot(), other.getRoot());
}

//Es determina si l'arbre binari i el passat per paràmetre són iguals recorrent totes les Position. Cost per recursió O(1), cost total O(n)
template <class K, class V> bool BSTree<K,V>::identicalAux(const Position<K,V>* pos1, const Position<K,V>* pos2) const {
    
    //Es retorna fals si un dels dos punters apunta a nullptr i l'altre no.
    if (pos1 == nullptr xor pos2 == nullptr)
        return false;
    else if (pos1 == nullptr and pos2 == nullptr)
        return true;
    else 
        return *pos1 == *pos2 and identicalAux(pos1->left(),pos2->left()) and identicalAux(pos1->right(), pos2->right());
}

/**
 * Funció modificadora
 */

//Afegeix un node amb una nova clau a l'arbre binari de cerca (si existeix afegeix el valor passat per paràmetre). Cost O(n) (O(n) cercar O(1) inserir)
template <class K, class V> Position<K,V>* BSTree<K,V>::insert(const K& key, const V& value) {
    
    if (isEmpty()) {
        root = new Position<K,V>(key);
        getRoot()->addValue(value);
        _size++;
        
        //Retornem nullptr perquè no cal fer rotacions.
        return nullptr;
    } else if (contains(key)) {
        search(key)->addValue(value);
        
        //Retornem nullptr perquè no cal fer rotacions.
        return nullptr;
    } else {
        Position<K,V>* pos = getRoot();
        bool left = false;
        bool right = false;
        
        while(!left and !right) {
            if (key < pos->getKey())
                if (pos->left() == nullptr)
                    left = true;
                else
                    pos = pos->left();
            else
                if (pos->right() == nullptr)
                    right = true;
                else
                    pos = pos->right();
        }
        
        //Creació de nova Position
        Position<K,V>* tmp = new Position<K,V>(key);
        tmp->addValue(value);
        tmp->setParent(pos);
        ++_size;
        
        if (left)
            pos->setLeft(tmp);
        else
            pos->setRight(tmp);
        
        return tmp;
    }
}

#endif /* BSTREE_H */