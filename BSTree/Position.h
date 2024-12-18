/* 
 * File:   Position.h
 * Author: Diego Hernández
 *
 * Created on 20 de abril de 2020, 19:03
 */

#ifndef POSITION_H
#define POSITION_H

#include <vector>

template <class K, class V>

class Position {
public:
    
    //Constructor i constructor còpia
    Position(const K key);
    Position(const Position<K,V>& orig);
    
    //Destructor
    virtual ~Position();
    
    //Funcions consultores
    int depth() const;
    int height() const;
    const K& getKey() const;
    const std::vector<V>& getValues() const;
    Position<K,V>* parent() const;
    Position<K,V>* left() const;
    Position<K,V>* right() const;
    bool isRoot() const;
    bool isLeaf() const;
    bool operator==(const Position<K,V>& other) const;
    
    //Funcions modificadores
    void setParent(Position<K,V>* parent);
    void setLeft(Position<K,V>* left);
    void setRight(Position<K,V>* right);
    void addValue(const V& value);
    
private:
    
    //Atributs
    K key;
    std::vector<V> values;
    Position<K,V>* _parent;
    Position<K,V>* _left;
    Position<K,V>* _right;
};

/**
 * Funcions constructores
 */

//Constructor, es crea una nova Position amb la clau passada com a paràmetre. Cost O(1)
template <class K, class V> Position<K,V>::Position(const K key) {
    this->key = key;
    _parent = nullptr;
    _left = nullptr;
    _right = nullptr;
}

//Constructor còpia, es copien recursivament la clau i els valors de la Position passada per paràmetre i els seus fills. Cost per Position O(1), cost total O(n)
template <class K, class V> Position<K,V>::Position(const Position<K,V>& orig):Position<K,V>(orig.getKey()) {
    this->values = orig.getValues();
    
    if (orig.left() != nullptr) {
        _left = new Position<K,V>(*orig.left());
        _left->setParent(this);
    }
    
    if (orig.right() != nullptr) {
        _right = new Position<K,V>(*orig.right());
        _right->setParent(this);
    }
}

/**
 * Funció destructora
 */

//Destructor, destrueix els fills primer per destruir l'arbre fent un recorregut de post-ordre. Cost per Position O(1), cost total O(n) (s'eliminen primer els n-1 descendents)
template <class K, class V> Position<K,V>::~Position() {
    delete _left;
    delete _right;
}

/**
 * Funcions consultores
 */

//Es calcula recursivament la profunditat de la Position, es retorna 0 si és l'arrel de l'arbre. Cost O(n) (si l'arbre és lineal)

//NOTA: Tot i que a l'enunciat fiqui que s'ha de retornar 0 si és l'arrel, a teoria estem considerant que 
//      l'alçada d'una fulla i la profunditat de l'arrel és 1. Si no feia aquest canvi hi havia diferència 
//      entre calcular l'alçada i la profunditat de l'arbre (quan en realitat són el mateix).
template <class K, class V> int Position<K,V>::depth() const {
    return 1 + (isRoot()? 0 : parent()->depth());
}

//Es calcula recursivament l'alçada de la Position, es retorna 1 si és una fulla. Cost O(n) (per calcular l'alçada d'una calculem la de dels n descendents)
template <class K, class V> int Position<K,V>::height() const {
    int esq = (left() == nullptr)? 0 : left()->height();
    int dre = (right() == nullptr)? 0 : right()->height();
        
    return 1 + ((esq >= dre)? esq : dre);
}

//Es retorna la clau guardada. Cost O(1)
template <class K, class V> const K& Position<K,V>::getKey() const {
    return key;
}

//Es retorna el vector que guarda els valors. Cost O(1)
template <class K, class V> const std::vector<V>& Position<K,V>::getValues() const {
    return values;
}

//Es retorna l'adreça de la Position pare. Cost O(1)
template <class K, class V> Position<K,V>* Position<K,V>::parent() const {
    return _parent;
}

//Es retorna l'adreça de la Position filla (esquerra). Cost O(1)
template <class K, class V> Position<K,V>* Position<K,V>::left() const {
    return _left;
}

//Es retorna l'adreça de la Position filla (dreta). Cost O(1)
template <class K, class V> Position<K,V>* Position<K,V>::right() const {
    return _right;
}

//Es retorna true si la Position és l'arrel de l'arbre, fals en cas contrari. Cost O(1)
template <class K, class V> bool Position<K,V>::isRoot() const {
    return parent() == nullptr;
}

//Es retorna true si la Position és una fulla de l'arbre, fals en cas contrari. Cost O(1)
template <class K, class V> bool Position<K,V>::isLeaf() const {
    return left() == nullptr and right() == nullptr;
}

//Retorna cert si les claus i els valors són iguals, fals en cas contrari. Cost O(1)
template <class K, class V> bool Position<K,V>::operator ==(const Position<K,V>& other) const {
    return this->getKey() == other.getKey() and this->getValues() == other.getValues();
}

/**
 * Funcions modificadores
 */

//Es redefineix l'adreça de la Position pare. Cost O(1)
template <class K, class V> void Position<K,V>::setParent(Position<K,V>* parent) {
    this->_parent = parent;
}

//Es redefineix l'adreça de la Position filla (esquerrra). Cost O(1)
template <class K, class V> void Position<K,V>::setLeft(Position<K,V>* left) {
    this->_left = left;
}

//Es redefineix l'adreça de la Position filla (dreta). Cost O(1)
template <class K, class V> void Position<K,V>::setRight(Position<K,V>* right) {
    this->_right = right;
}

//S'afegeix un nou valor passat com a paràmetre al vector de valors. Cost O(1)
template <class K, class V> void Position<K,V>::addValue(const V& value) {
    values.push_back(value);
}

#endif /* POSITION_H */