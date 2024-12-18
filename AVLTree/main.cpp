/* 
 * File:   main.cpp
 * Author: Diego Hernández
 *
 * Created on 17 de mayo de 2020, 19:58
 */

#include <iostream>
#include <stdexcept>
#include <ctime>
#include <fstream>
#include "WordIndexerAVL.h"
#include "Tuple.h"

using namespace std;

/**
 * EXERCICI 4:
 * 
 * He reutilitzat els fitxers dels exercicis 2 i 3.
 * He copiat les classes WordIndexer i Tuple (WordIndexer l'he
 * canviat només afegint el sufix AVL, ja que ara la classe és
 * WordIndexerAVL). De l'exercici 3 he copiat les classes BSTree,
 * Position i AVLTree.
 * 
 * També he copiat el main de l'exercici 2 i he modificat les variables
 * de tipus WordIndexer perquè siguin de tipus WordIndexerAVL. He pogut
 * reutilitzar d'aquesta manera el codi ja que AVLTree és una classe que
 * hereta de BSTree i, per tant, els mètodes que utilitzava la classe
 * WordIndexer en l'exercici 2 també estan definits en la classe AVLTree.
 * En altres paraules, l'única diferència entre aquest exercici i el 2 és
 * l'ús d'un arbre AVL intern al WordIndexer en comptes d'un arbre binari
 * normal (BSTree), fet que optimitzarà el seu ús, tal i com veurem al següent
 * exercici.
 */

/**
 * EXERCICI 5:
 * 
 *          Inserció        Inserció        Cerca           Cerca
 *          Fitxer SHORT    Fitxer LONG     Fitxer Short    Fitxer LONG
 * 
 * BSTree   0 segons        0.093 segons    2.839 segons    3.291 segons
 * AVLTree  0 segons        0.11  segons    2.465 segons    2.699 segons
 * 
 * El temps d'inserció dels fitxers és el temps que es triga en generar l'arbre intern
 * amb les paraules del text. Podem observar que la inserció en el cas de l'AVLTree és
 * més costosa (ja que, a més d'inserir les paraules, ha de balancejar l'arbre en el cas
 * que es produeixi algun desbalanceig. Tanmateix, el temps de cerca (mesurat amb la cerca
 * de les paraules del fitxer dictionary.txt) és major si utilitzem un arbre BSTree, això
 * és degut a que aquest és un arbre que pot estar desbalancejat i arribar a ser lineal (en
 * el pitjor cas), com, en canvi, l'arbre AVLTree és un arbre quasi complet, optimitza molt
 * més aquesta cerca ja que ha de recòrrer menys nivells i, per tant, ha de completar menys
 * recursions en el pitjor dels casos (que la paraula no es trobi en l'arbre o es trobi a
 * l'últim nivell).
 * 
 * L'operació de cerca té un cost de O(n) en el cas del TAD BSTree (si està completament
 * desbalancejat i és una estructura lineal, el cost en cercar l'últim element serà el temps
 * que triguem en recòrrer tota la llista i, per tant, serà de n comprovacions). En canvi, 
 * com el TAD AVLTree és un arbre binari balancejat, només haurem de fer logn comprovacions 
 * en el pitjor dels casos i, per tant, obtenim un cost molt menor: O(logn).
 * 
 * L'operació d'inserció cerca internament la paraula en l'arbre (si ja hi és actualitza les
 * seves aparicions al text). Per tant, el seu cost en el cas del TAD BSTree és O(n) (O(n) cercar
 * i O(1) inserir) i O(logn) en el cas del TAD AVLTree (O(logn) cercar, O(1) inserir i O(logn)
 * balancejar l'arbre). 
 * 
 * En resum, ambdues operacions són menys costoses en el cas de l'arbre balancejat però la 
 * inserció seria menys costosa en el TAD BSTree si no haguéssim de cercar la paraula internament.
 */

//Demanem a l'usuari amb quin fitxer vol inicialitzar 
//el WordIndexer i mostrem el temps de la seva creació.
WordIndexerAVL* pas1() {
    char tipus;
    string fitxer;
    
    cout << "\tQuin fitxer vols(P/G)? ";
    cin >> tipus;
    
    if (toupper(tipus) == 'P')
        fitxer = "shortText.txt";
    
    else if (toupper(tipus) == 'G')
        fitxer = "longText.txt";
    
    else {
        cout << "\tError de lectura. Llegint fitxer per defecte (shortText.txt)...\n";
        fitxer = "shortText.txt";
    }
    
    clock_t timer = clock();
    WordIndexerAVL* index = new WordIndexerAVL(fitxer);
    timer = clock() - timer;
    
    cout << "\tWordIndexerAVL creat en " << ((double)timer)/CLOCKS_PER_SEC << "s\n";

    return index;
}

//Mostrem l'arbre per ordre alfabètic, demanant confirmació
//cada 40 paraules per seguir mostrant-lo.
void pas2(WordIndexerAVL* index) {
    index->printWords();
}

//Llegim el fitxer dictionary.txt, fem una cerca de cadascuna
//de les paraules al WordIndexer i avaluem el temps de cerca.
void pas3(WordIndexerAVL* index) {
    fstream file("dictionary.txt");
    string paraula;
    bool b;
    
    cout << "\tParaules a dictionary.txt i si es troba o no al WordIndexerAVL:\n\n";
    
    clock_t timer = clock();
    
    while (!file.eof()) {
        file >> paraula;
        b = index->contains(paraula);
        cout << "\t-" << paraula << ": " << (b? "Es " : "No es ") << "troba al WordIndexerAVL";
        
        if (b) {
            vector<Tuple<int,int>> occurrences = index->printOccurrences(paraula);
            cout << " [";
            
            //Imprimim les ocurrències de la paraula en el text guardat al WordIndexer.
            for (vector<Tuple<int,int>>::iterator it = occurrences.begin(); it != occurrences.end(); ++it) {
                cout << "(" << it->getElem1() << ", " << it->getElem2() << ")";

                //Mirem si seguim imprimim comes.
                if (++it != occurrences.end())
                    cout << ", ";
                --it;
            }
            cout << "]";
        }
        cout << endl;
    }
    
    timer = clock() - timer;
    cout << "\n\tS'ha trigat " << ((double)timer)/CLOCKS_PER_SEC << "s en cercar totes les paraules de dictionary.txt\n";

    file.close();
}

//Generem i visualitzem l'índex de les paraules del diccionari.
void pas4(WordIndexerAVL* index) {
    clock_t timer = clock();
    index->printDictionary();
    timer = clock() - timer;
    cout << "\n\tS'ha trigat " << ((double)timer)/CLOCKS_PER_SEC << "s en generar l'índex de paraules del WordIndexer\n";
}

//Visualitzem per pantalla la profunditat de l'arbre guardat a WordIndexer.
//Si l'arbre està buit es mostra per pantalla.
void pas5(WordIndexerAVL* index) {
    try {
        cout << "\tLa profunditat de l'arbre guardat és " << index->depth() << endl;
    } catch (logic_error e) {
        cout << "\t" << e.what() << endl;
    }
}

int main(int argc, char** argv) {
    int option;
    WordIndexerAVL* index = nullptr;
    
    cout << "CAS DE PROVA EXERCICI 4:\n";

    do {
        cout << "\nQuè vols fer?\n\n\t1. Crear un WordIndexerAVL i inicialitzar-lo."
             << "\n\t2. Mostrar el WordIndexerAVL guardat en ordre alfabètic.\n\t"
             << "3. Llegir el fitxer dictionary.txt i cercar les seves paraules al "
             << "WordIndexerAVL.\n\t4. Generar i visualitzar l'índex de les paraules "
             << "del WordIndexerAVL.\n\t5. Visualitzar per pantalla la profunditat de "
             << "l'arbre guardat al WordIndexerAVL.\n\t6. Sortir.\n\nElecció (1-6): ";
        cin >> option;
        cout << endl;
        
        switch (option) {
            case 1:
                delete index;
                index = pas1();
                break;
                
            case 2:
                if (index == nullptr)
                    cout << "\tCrea primer un WordIndexerAVL!\n";
                else
                    pas2(index);
                break;
                
            case 3:
                if (index == nullptr)
                    cout << "\tCrea primer un WordIndexerAVL!\n";
                else
                    pas3(index);
                break;
                
            case 4:
                if (index == nullptr)
                    cout << "\tCrea primer un WordIndexerAVL!\n";
                else
                    pas4(index);
                break;
                
            case 5:
                if (index == nullptr)
                    cout << "\tCrea primer un WordIndexerAVL!\n";
                else
                    pas5(index);
                break;
                
            case 6:
                cout << "\tFinalitzant la prova...\n";
                delete index;
                break;
                
            default:
                cout << "\tError. Introdueix un enter entre 1 i 6!\n";
                break;
        }
    } while (option != 6);
    return 0;
}