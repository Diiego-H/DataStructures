/* 
 * File:   Registry.h
 * Author: Diego Hernández
 *
 * Created on 25 de marzo de 2020, 13:04
 */

#ifndef REGISTRY_H
#define REGISTRY_H
#include "LinkedList.h"
#include "Position.h"

class Registry: public LinkedList<std::string> {
public:
    
    Registry();
    Registry(const Registry& orig);
    virtual ~Registry();
    
    void insert(const std::string& element);      //inserta nou element ordenat alfabèticament
    void merge(const Registry& other);            //barreja amb un altre registre mantenint l'ordre
    bool operator==(const Registry& other) const; //mira si dos registres són iguals
    
    //Opcional: quants cops apareix cada usuari en un registre
    void count(LinkedList<std::string>& users, LinkedList<int>& counts) const;
};

#endif /* REGISTRY_H */