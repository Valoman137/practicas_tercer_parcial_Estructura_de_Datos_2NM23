#ifndef PILADINAMICA_H
#define PILADINAMICA_H

#include <iostream>
#include <fstream> 
#include <string>  

using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
};

class PilaDinamica {
private:
    Nodo* tope;
    int obtenerSiguienteID(); 

public:
    PilaDinamica();
    ~PilaDinamica();
    void push(int valor);
    void pop();
    bool estaVacia();
    void mostrarTope();
    void guardarArchivos(); 
};

#endif
