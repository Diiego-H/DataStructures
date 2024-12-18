/* 
 * File:   WordIndexerAVL.h
 * Author: Diego Hernández
 *
 * Created on 17 de mayo de 2020, 19:59
 */

#ifndef WORDINDEXERAVL_H
#define WORDINDEXERAVL_H

#include "Position.h"
#include "AVLTree.h"
#include "Tuple.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

//Especificació TAD WordIndexerAVL
class WordIndexerAVL {
public:
    
    WordIndexerAVL();
    WordIndexerAVL(std::string filename);
    WordIndexerAVL(const WordIndexerAVL& orig);
    
    virtual ~WordIndexerAVL();
    
    bool contains(std::string word) const;
    const std::vector<Tuple<int,int>>& printOccurrences(std::string word) const;
    void printDictionary() const;
    void printWords() const;
    int depth() const;
    
    void addText(std::string filename);
    void insertWord(std::string word, int numLine, int numWord);
    
private:
    AVLTree<std::string, Tuple<int,int>>* tree;
    
    void printDictionaryAux(Position<std::string, Tuple<int,int>>* pos) const;
    void printWordsAux(Position<std::string, Tuple<int,int>>* pos, int& counter, bool& seguir) const;
    std::string tractamentParaula(std::string word) const;
    bool confirmar() const;
};

#endif /* WORDINDEXERAVL_H */