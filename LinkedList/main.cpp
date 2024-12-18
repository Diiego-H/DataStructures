/* 
 * File:   main.cpp
 * Author: Diego Hernández
 *
 * Created on 18 de marzo de 2020, 12:06
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Position.h"
#include "Registry.h"

using namespace std;

/**
 * 1. La inserció ordenada té un cost de O(n) ja que, en el pitjor
 *    dels casos, si l'adreça de correu a afegir és, alfabèticament,
 *    l'última, s'haurà de recòrrer tot el registre fins afegir-la.
 * 
 * 2. Segons els elements guardats tant a r1 com r2, si r1 té més 
 *    elements amb un valor alfabètic baix, per exemple, que comencin
 *    per (r,s,t,...,z), seria millor fer r1.merge(r2), perquè, tot i
 *    haver de fer n recorreguts, els recorreguts seran, generalment, 
 *    més curts. Per tant, tot i que el cost computacional seria O(mn),
 *    el cost real d'aquesta operació seria menor al de r2.merge(r1), amb
 *    cost també O(mn).
 * 
 * 3. El cost teòric computacional del mètode count és O(mn), amb m el
 *    nombre d'elements de la llista users i n el nombre d'elements del 
 *    registre. Aquest cost, com considerem el pitjor cas, és independent
 *    de si la llista està ordenada o no, perquè es farien, igualment, m
 *    vegades n comparacions. Tot i això, com els elements estan ordenats, el
 *    cost real d'aquest mètode és menor (si en un moment notem que l'adreça
 *    ja no podrà ser igual a cap dels elements que estem recorrent, aturem aquest
 *    recorregut). Per tant, en realitat no es fan m vegades n comparacions, és
 *    a dir, té un cost menor.
 * 
 */

int main(int argc, char** argv) {
    
    //Creem dos registres.
    Registry registre1;
    Registry registre2;
    
    //Inserim diferents adreces en el primer i les mostrem per pantalla.
    registre1.insert("dhernaan8@alumnes.ub.edu");
    registre1.insert("maria.salamo@ub.edu");
    registre1.print();
    
    //Inserim els mateixos elements en diferent ordre per veure si es guarden
    //en ordre alfabètic.
    registre2.insert("maria.salamo@ub.edu");
    registre2.insert("dhernaan8@alumnes.ub.edu");
    
    //Comprovem si els dos registres són iguals.
    cout << "Iguals: " << (registre1 == registre2) << endl;
    
    //Ajuntem els dos registres, afegim una tercera adreça i mostrem per pantalla
    //el contingut.
    registre1.merge(registre2);
    registre1.insert("shernaan7@alumnes.ub.edu");
    registre1.print();
    
    //Comprovem una segona vegada si els registres són iguals (per veure que, en
    //aquest cas, no ho són).
    cout << "Iguals: " << (registre1 == registre2) << endl;
    
    //Creem una llista de comptadors i comptem quants cops estan les dues primeres
    //adreces en el primer registre.
    LinkedList<int> counter;
    registre1.count(registre2, counter);
    
    //Imprimim el contingut del segon registres junt amb el nombre de vegades que
    //es troba cada adreça en el segon registre.
    registre2.print();
    counter.print();
    
    return 0;
}