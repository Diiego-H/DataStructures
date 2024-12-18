/* 
 * File:   WordIndexer.h
 * Author: Diego Hernández
 *
 * Created on 29 de abril de 2020, 20:32
 */

#ifndef WORDINDEXER_H
#define WORDINDEXER_H

#include "Position.h"
#include "BSTree.h"
#include "Tuple.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

//Especificació TAD WordIndexer
class WordIndexer {
public:
    
    WordIndexer();
    WordIndexer(std::string filename);
    WordIndexer(const WordIndexer& orig);
    
    virtual ~WordIndexer();
    
    bool contains(std::string word) const;
    const std::vector<Tuple<int,int>>& printOccurrences(std::string word) const;
    void printDictionary() const;
    void printWords() const;
    int depth() const;
    
    void addText(std::string filename);
    void insertWord(std::string word, int numLine, int numWord);
    
private:
    BSTree<std::string, Tuple<int,int>>* tree;
    
    void printDictionaryAux(Position<std::string, Tuple<int,int>>* pos) const;
    void printWordsAux(Position<std::string, Tuple<int,int>>* pos, int& counter, bool& seguir) const;
    std::string tractamentParaula(std::string word) const;
    bool confirmar() const;
};

#endif /* WORDINDEXER_H */