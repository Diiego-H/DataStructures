/* 
 * File:   Registry.cpp
 * Author: Diego Hernández
 * 
 * Created on 25 de marzo de 2020, 13:04
 */

#include "Registry.h"
#include "LinkedList.h"
#include <string>

using namespace std;

/**
 * Funcions constructores
 */

//Constructor per defecte, inicialitza una llista buida.
Registry::Registry():LinkedList<string>() {
}

//Constructor còpia.
Registry::Registry(const Registry& orig):LinkedList<string>(orig) {
}

/**
 * Funció destructora
 */

//Destructor, crida el destructor de LinkedList.
Registry::~Registry() {
}

/**
 * Funció consultora
 */

//Compta quants cops apareix cada usuari en un registre.
void Registry::count(LinkedList<string>& users, LinkedList<int>& counts) const {
    for (Position<string> usuari = users.begin(); usuari != users.end(); usuari = ++usuari) {
        Position<string> pos = this->begin();
        bool seguir = true;
        int counter = 0;
        string cadenaUsu = *usuari;
        
        while(seguir && pos != this->end()) {
            string cadenaPos = *pos;
            
            if (cadenaPos.compare(cadenaUsu) == 0)
                counter++;
            
            else if (cadenaPos.compare(cadenaUsu) > 0)
                seguir = false;
            
            pos = ++pos;
        }
        
        counts.insertBack(counter);
    }
}

/**
 * Funcions modificadores
 */

//Inserta una adreça de correu electrònic alfabèticament.
void Registry::insert(const string& element) {
    Position<string> pos = this->begin();
    bool trobat = false;
    
    while(!trobat && pos != this->end()) {
        if ((*pos).compare(element) > 0)
            trobat = true;
        pos = ++pos;
    }
    
    if (trobat) {
        pos = pos.previous();
        insertBefore(pos, element);
    } else
        insertBack(element);
}
        
//Combina dos registres.
void Registry::merge(const Registry& other) {
    for (Position<string> pos = other.begin(); pos != other.end(); pos = ++pos) {
        string adreca = *pos;
        insert(adreca);
    }
}
  
/**
 * Sobrecàrrega d'operadors
 */

//Retorna true si dos registres contenen els mateixos elements.
bool Registry::operator==(const Registry& other) const {
    Position<string> pos1 = this->begin();
    Position<string> pos2 = other.begin();
    bool iguals = true;
    int i = 0;
    
    if (this->size() != other.size())
        iguals = false;
        
    while (i < this->size() && iguals) {
        if ((*pos1).compare(*pos2) != 0)
            iguals = false;
    
        pos1 = ++pos1;
        pos2 = ++pos2;
        i++;
    }
    
    return iguals;
}