/* 
 * File:   main.cpp
 * Author: Diego Hernández
 *
 * Created on 29 de abril de 2020, 19:01
 */

#include <iostream>
#include <stdexcept>
#include <ctime>
#include <fstream>
#include "WordIndexer.h"
#include "Tuple.h"

using namespace std;

//Demanem a l'usuari amb quin fitxer vol inicialitzar 
//el WordIndexer i mostrem el temps de la seva creació.
WordIndexer* pas1() {
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
    WordIndexer* index = new WordIndexer(fitxer);
    timer = clock() - timer;
    
    cout << "\tWordIndexer creat en " << ((double)timer)/CLOCKS_PER_SEC << "s\n";

    return index;
}

//Mostrem l'arbre per ordre alfabètic, demanant confirmació
//cada 40 paraules per seguir mostrant-lo.
void pas2(WordIndexer* index) {
    index->printWords();
}

//Llegim el fitxer dictionary.txt, fem una cerca de cadascuna
//de les paraules al WordIndexer i avaluem el temps de cerca.
void pas3(WordIndexer* index) {
    fstream file("dictionary.txt");
    string paraula;
    bool b;
    
    cout << "\tParaules a dictionary.txt i si es troba o no al WordIndexer:\n\n";
    
    clock_t timer = clock();
    
    while (!file.eof()) {
        file >> paraula;
        b = index->contains(paraula);
        cout << "\t-" << paraula << ": " << (b? "Es " : "No es ") << "troba al WordIndexer";
        
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
void pas4(WordIndexer* index) {
    clock_t timer = clock();
    index->printDictionary();
    timer = clock() - timer;
    cout << "\n\tS'ha trigat " << ((double)timer)/CLOCKS_PER_SEC << "s en generar l'índex de paraules del WordIndexer\n";
}

//Visualitzem per pantalla la profunditat de l'arbre guardat a WordIndexer.
//Si l'arbre està buit es mostra per pantalla.
void pas5(WordIndexer* index) {
    try {
        cout << "\tLa profunditat de l'arbre guardat és " << index->depth() << endl;
    } catch (logic_error e) {
        cout << "\t" << e.what() << endl;
    }
}

int main(int argc, char** argv) {
    int option;
    WordIndexer* index = nullptr;
    
    cout << "CAS DE PROVA EXERCICI 2:\n";

    do {
        cout << "\nQuè vols fer?\n\n\t1. Crear un WordIndexer i inicialitzar-lo."
             << "\n\t2. Mostrar el WordIndexer guardat en ordre alfabètic.\n\t"
             << "3. Llegir el fitxer dictionary.txt i cercar les seves paraules al "
             << "WordIndexer.\n\t4. Generar i visualitzar l'índex de les paraules "
             << "del WordIndexer.\n\t5. Visualitzar per pantalla la profunditat de "
             << "l'arbre guardat al WordIndexer.\n\t6. Sortir.\n\nElecció (1-6): ";
        cin >> option;
        cout << endl;
        
        switch (option) {
            case 1:
                delete index;
                index = pas1();
                break;
                
            case 2:
                if (index == nullptr)
                    cout << "\tCrea primer un WordIndexer!\n";
                else
                    pas2(index);
                break;
                
            case 3:
                if (index == nullptr)
                    cout << "\tCrea primer un WordIndexer!\n";
                else
                    pas3(index);
                break;
                
            case 4:
                if (index == nullptr)
                    cout << "\tCrea primer un WordIndexer!\n";
                else
                    pas4(index);
                break;
                
            case 5:
                if (index == nullptr)
                    cout << "\tCrea primer un WordIndexer!\n";
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