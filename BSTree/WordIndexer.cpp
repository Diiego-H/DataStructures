/* 
 * File:   WordIndexer.cpp
 * Author: Diego Hernández
 * 
 * Created on 29 de abril de 2020, 20:32
 */

#include "WordIndexer.h"

using namespace std;

/*
 * Funcions constructores
 */

//Constructor per defecte, inicialitza l'arbre.
WordIndexer::WordIndexer() {
    tree = new BSTree<string, Tuple<int,int>>();
}

//Constructor que rep el nom d'un fitxer i 
//emmagatzema el seu contingut al WordIndexer.
WordIndexer::WordIndexer(string filename):WordIndexer() {
    addText(filename);
}

//Constructor còpia.
WordIndexer::WordIndexer(const WordIndexer& orig) {
    this->tree = new BSTree<string, Tuple<int,int>>(*orig.tree);
}

/*
 * Funció destructora
 */

//Destructor, es destrueix l'arbre.
WordIndexer::~WordIndexer() {
    delete tree;
}

/*
 * Funcions consultores
 */

//Es retorna cert si el WordIndexer conté la paraula 
//passada per paràmetre, fals en cas contrari.
bool WordIndexer::contains(string word) const {
    bool trobat = tree->contains(tractamentParaula(word));
    return trobat;
}

//Es retorna el vector de tuples amb les línies i 
//posicions de la paraula en el text. Si la paraula 
//no es troba al WordIndexer, llença una excepció.
const vector<Tuple<int,int>>& WordIndexer::printOccurrences(string word) const {
    try {
        return tree->getValues(tractamentParaula(word));
    } catch (logic_error& e) {
        throw e;
    }
}

//Es mostra per pantalla l'índex de paraules guardades al WordIndexer 
//en ordre alfabètic, junt amb les posicions on apareix cada paraula.
void WordIndexer::printDictionary() const {
    cout << "\tÍndex de les paraules del WordIndexer:\n\n";
    printDictionaryAux(tree->getRoot());
    cout << "\n\tImpressió finalitzada\n";
}

//Es mostra recursivament l'índex de paraules del
//WordIndexer (seguint un recorregut en in-ordre).
void WordIndexer::printDictionaryAux(Position<string, Tuple<int,int>>* pos) const {
    if (pos != nullptr) {
        printDictionaryAux(pos->left());
        
        cout << "\t- " << pos->getKey() << " [";

        vector<Tuple<int,int>> vec = pos->getValues();

        //Imprimim les ocurrències de la paraula al text.
        for (vector<Tuple<int,int>>::iterator it = vec.begin(); it != vec.end(); ++it) {
            cout << "(" << it->getElem1() << ", " << it->getElem2() << ")";

            if (++it != vec.end())
                cout << ", ";
            --it;
        }

        cout << "]\n";

        printDictionaryAux(pos->right());
    }
}

//Es retorna la profunditat de l'arbre guardat al WordIndexer.
int WordIndexer::depth() const {
    try {
        return tree->height();
    } catch (logic_error& e) {
        throw e;
    }
}

//Es mostren les paraules de l'arbre en un recorregut en inordre,
//demanant confirmació cada 40 paraules.
void WordIndexer::printWords() const {
    int counter = 0;
    bool seguir = true;
    
    cout << "\tParaules guardades al WordIndexer:\n\n";
    printWordsAux(tree->getRoot(), counter, seguir);
    cout << "\n\tImpressió finalitzada\n";
}

//Mètode recursiu per mostrar l'arbre fent un recorregut 
//en inordre i demanant confirmació cada 40 paraules.
void WordIndexer::printWordsAux(Position<std::string, Tuple<int,int>>* pos, int& counter, bool& seguir) const {
    if (pos != nullptr and seguir) {
        printWordsAux(pos->left(),counter,seguir);
        
        //Comprovem si l'usuari vol seguir mostrant l'arbre.
        if (seguir and counter != 0 and counter % 40 == 0)
            seguir = confirmar();
        
        //Comprovem que l'usuari no hagi cancel·lat l'operació.
        if (seguir) {
            cout << "\t-" << pos->getKey() << endl;
            counter++;
            printWordsAux(pos->right(),counter,seguir);
        }
    }
}

//Es confirma si es vol seguir mostrant l'arbre del WordIndexer.
bool WordIndexer::confirmar() const {
    char eleccio;
    bool b;
    cout << "\n\tVols seguir mostrant l'arbre (y/n)? ";
    cin >> eleccio;
    
    if (tolower(eleccio) == 'y') {
        cout << "\tContinuant amb la impressió de l'arbre...\n\n";
        b = true;
    } else {
        cout << "\tAturant la impressió de l'arbre...\n";
        b = false;
    }
    
    return b;
}

/*
 * Funcions modificadores
 */

//S'afegeix el text d'un fitxer al WordIndexer.
void WordIndexer::addText(string filename) {
    ifstream file(filename);
    string line, word;
    int numLine = 0, numWord = 0;
    
    while (getline(file,line)) {
        numLine++;
        
        //istringstream separa la línia en paraules.
        istringstream sepParaules(line);
        
        while (!sepParaules.eof()) {
            numWord++;
            sepParaules >> word;
            
            //Convertim la paraula a minúscules i eliminem els signes de puntuació.
            word = tractamentParaula(word);
            
            insertWord(word, numLine, numWord);
        }

        numWord = 0;
    }
    
    file.close();
}

//S'afegeix una paraula a l'arbre (amb la línia i 
//la posició de la paraula guardades a una Tuple).
void WordIndexer::insertWord(string word, int numLine, int numWord) {
    Tuple<int,int> tuple(numLine,numWord);
    tree->insert(word,tuple);
}

//Es processen les paraules.
string WordIndexer::tractamentParaula(string word) const {
    //Passem a minúscules tota la paraula.
    for (int i = 0; i < word.length(); i++)
        word[i] == tolower(word[i]);

    //Comprovem si hi ha signes de puntuació al final de la paraula 
    //i els eliminem (while per si hi ha punts suspensius).
    while (!isalpha(word[word.length()-1]))
        word.pop_back();
    
    return word;
}