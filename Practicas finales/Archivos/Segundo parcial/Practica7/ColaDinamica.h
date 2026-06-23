#ifndef COLADINAMICA_H
#define COLADINAMICA_H

#include <iostream>
#include <fstream> 
#include <string>  

using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
};

class ColaDinamica {
private:
    Nodo* frente;
    Nodo* final;
    int obtenerSiguienteID(); 

public:
    ColaDinamica();
    ~ColaDinamica();
    void enqueue(int valor); 
    void dequeue();         
    bool estaVacia();
    void mostrarFrente();
    void guardarArchivos();  
};

#endif
