/* 
 * File:   AVLTree.h
 * Author: Diego Hernandez
 *
 * Created on 4 de mayo de 2020, 14:58
 */

#ifndef AVLTREE_H
#define AVLTREE_H

#include "BSTree.h"
#include "Position.h"

template <class K, class V>

/**
 * El TAD AVLTree afegeix a les funcionalitats del TAD BSTree el balanceig.
 * Aquesta nova operació permet balancejar l'arbre per tal que aquest tingui 
 * la mínima alçada possible. De fet, amb aquesta nova implementació, les 
 * funcions contains(), search(), getValues() i insert() tenen ara un cost 
 * computacional teòric O(logn). Un BSTree normal podria tenir una única branca, 
 * fet que faria que l'arbre fós una estructura lineal en el pitjor dels casos i,
 * per tant, el cost d'aquestes funcions seria lineal (O(n)), ara bé, en un arbre
 * balancejat (AVLTree) l'alçada és logaritme en base 2 de n i, per tant, el cost
 * d'aquestes mateixes funcions cridades des d'un AVLTree es redueix considerablement.
 */

class AVLTree:public BSTree<K,V> {
public:
    AVLTree();
    AVLTree(const AVLTree& orig);
    virtual ~AVLTree();
   
    virtual Position<K,V>* insert(const K& key, const V& value);
private:
    void balanceTree(Position<K,V>* pos);
    void rotacioSimple(Position<K,V>* pos, bool esq);
    void rotacioDoble(Position<K,V>* pos, bool esq);
};

/**
 * Funcions constructores
 */

//Constructor per defecte. Cost O(1)
template <class K, class V> AVLTree<K,V>::AVLTree(){
}

//Constructor còpia. Cost O(n) (es copien totes les Position)
template <class K, class V> AVLTree<K,V>::AVLTree(const AVLTree& orig):BSTree<K,V>(orig){
}

/**
 * Funció destructora
 */

//Destructor. Cost O(n) (es destrueixen totes les Position)
template <class K, class V> AVLTree<K,V>::~AVLTree(){
}

/**
 * Funcions modificadores
 */

//S'insereix un element a l'arbre i, si s'escau, es balanceja. Cost O(log n) (O(logn) cercar, O(1) inserir i O(logn) balancejar)
template <class K, class V> Position<K,V>* AVLTree<K,V>::insert(const K& key, const V& value) {
    Position<K,V>* pos = this->BSTree<K,V>::insert(key, value);
   
    if (pos != nullptr)
        balanceTree(pos->parent());
    
    return pos;
}

//Es balanceja l'arbre fent rotacions simples o dobles segons la casuística. Cost O(logn) (l'alçada de l'arbre)
template <class K, class V> void AVLTree<K,V>::balanceTree(Position<K,V>* pos) {
    
    //Actualitzem l'alçada i el factor de balanç de la Position.
    pos->calculateHeight();
    pos->calculateBalance();
    
    //Com el factor de balanç és menor a -1, vol dir que es desbalanceja per l'esquerra.
    if (pos->balance() < -1) {
        //Si el signe del fill esquerre és igual al del pare, rotació simple, si no, doble.
        if (pos->left()->balance() < 0)
            rotacioSimple(pos,false);
        else
            rotacioDoble(pos,false);
    } 
    
    //Com el factor de balanç és major a 1, vol dir que es desbalanceja per la dreta.
    else if (pos->balance() > 1)
        //Si el signe del fill dret és igual al del pare, rotació simple, si no, doble.
        if (pos->right()->balance() > 0)
            rotacioSimple(pos,true);
        else
            rotacioDoble(pos,true);
    
    //Si no hem arribat a l'arrel de l'arbre comprovem els factors de balanç dels pares.
    if (!pos->isRoot())
        balanceTree(pos->parent());
}

//Es fa una rotació simple des de la Position donada cap al sentit donat. Cost O(1)
template <class K, class V> void AVLTree<K,V>::rotacioSimple(Position<K,V>* pos, bool esq) {
    if (esq) {
        if (pos->isRoot()) {
            pos->right()->setParent(nullptr);
            this->root = pos->right();
        }
        else {
            pos->right()->setParent(pos->parent());

            if (pos == pos->parent()->left())
                pos->parent()->setLeft(pos->right());
            else
                pos->parent()->setRight(pos->right());
        }
        
        pos->setParent(pos->right());
        
        if (pos->parent()->left() != nullptr) {
            pos->setRight(pos->parent()->left());
            pos->right()->setParent(pos);
        } else
            pos->setRight(nullptr);
        
        pos->parent()->setLeft(pos); 
    } else {
        if (pos->isRoot()) {
            pos->left()->setParent(nullptr);
            this->root = pos->left();
        }
        else {
            pos->left()->setParent(pos->parent());

            if (pos == pos->parent()->left())
                pos->parent()->setLeft(pos->left());
            else
                pos->parent()->setRight(pos->left());
        }
        
        pos->setParent(pos->left());
        
        if (pos->parent()->right() != nullptr) {
            pos->setLeft(pos->parent()->right());
            pos->left()->setParent(pos);
        } else
            pos->setLeft(nullptr);
        
        pos->parent()->setRight(pos);
    }
    
    pos->calculateHeight();
    pos->calculateBalance();
    pos->parent()->calculateHeight();
    pos->parent()->calculateBalance();
}

//Es fa una rotació doble des de la Position donada cap al sentit donat. Cost O(1)
template <class K, class V> void AVLTree<K,V>::rotacioDoble(Position<K,V>* pos, bool esq) {
    if (esq) {
        rotacioSimple(pos->right(),false);
        rotacioSimple(pos,true);
    } else {
        rotacioSimple(pos->left(), true);
        rotacioSimple(pos,false);
    }
}

#endif /* AVLTREE_H */