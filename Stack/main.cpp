 /* 
 * File:   main.cpp
 * Author: Diego Hernández
 *
 * Created on 12 de marzo de 2020, 13:07
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include "ArrayStack.h"
#include <stdexcept>

using namespace std;

/**
 * -Per moure un paquet de pila a pila he afegit a la pila destí l'element
 *  superior (top) de la pila d'origen i, un cop fet això, l'he esborrat de
 *  la pila d'origen. D'aquesta manera, el paquet ha canviat de pila i, per tant,
 *  s'ha mogut.
 * 
 * -Controlo que el nombre de paquets sigui un nombre major a 1, de no ser així,
 *  el problema no tindria sentit. Per controlar-ho torno a demanar el nombre de paquets
 *  a l'usuari. A més, capturo excepcions quan es vol afegir un paquet d'una pila plena
 *  o quan es vol treure un d'una buida, tanmateix, això no fa falta per com està definida
 *  la recursió.
 */

void mostrar(ArrayStack<int>& A, ArrayStack<int>& B, ArrayStack<int>& P) {
    cout << "A: ";
    A.print();
    cout << "P: ";
    P.print();
    cout << "B: ";
    B.print();
    cout << endl;
}

//Funció per moure un paquet de pila.
void moure(ArrayStack<int>& from, ArrayStack<int>& to) {
    try {
        to.push(from.top());
        from.pop();
    } catch (const length_error& e) {
        cout << e.what() << endl;
    }
}

//Funció que ens permet moure els paquets d'una pila A a una B mitjançant una tercera P.
void logistica(int N, ArrayStack<int>& A, ArrayStack<int>& B, ArrayStack<int>& P) {
    
    if (N == 1) {
        moure(A,B);
    } else {
        logistica(N-1, A, P, B);
        logistica(1, A, B, P);
        logistica(N-1, P, B, A);
    }
}

//Funció que realitza totes les operacions necessàries.
void gestioPaquets(int N, ArrayStack<int>& A, ArrayStack<int>& B, ArrayStack<int>& P) {
    
    //Mostrem l'estat inicial de les piles de paquets.
    cout << "L'estat inicial és el següent:\n";
    mostrar(A,B,P);
    
    //Movem els paquets de la pìla A a B per mitjà de P.
    logistica (N, A, B, P);
    
    //Mostrem l'estat final de les piles.
    cout << "L'estat final és el següent:\n";
    mostrar(A,B,P);
}

int main(int argc, char** argv) {
    
    int N;
    
    //Carreguem un exemple amb una pila de 3 elements per utilitzar el 3r constructor.
    cout << "Hola, sóc el braç robòtic.\n";
    N = 3;
    ArrayStack<int> A{3,2,1};
    ArrayStack<int> P(3);
    ArrayStack<int> B(3);
    
    gestioPaquets(N,A,B,P);
    
    //Ara demanem a l'usuari que especifiqui el nombre de paquets.
    cout << "Hola, sóc el braç robòtic.\nIntrodueix el nombre de paquets: ";
    cin >> N;
    
    //Si no introdueix un nombre natural, tornem a demanar-lo.
    while (N < 1) {
        cout << "Error. No hi ha paquets a moure.\nIntrodueix el nombre de paquets: ";
        cin >> N;
    }
    
    //Inicialitzem A,P i B amb una capacitat màxima de N (el nombre de paquets).
    A = ArrayStack<int>(N);
    B = ArrayStack<int>(N);
    P = ArrayStack<int>(N);
     
    //Afegim N paquets a la pila.
    for (int i = N; i > 0; i--)
        A.push(i);
    
    gestioPaquets(N,A,B,P);
    
    return 0;
}