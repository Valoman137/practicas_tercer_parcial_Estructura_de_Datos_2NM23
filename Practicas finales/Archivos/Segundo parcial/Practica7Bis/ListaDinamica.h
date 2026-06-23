#ifndef LISTADINAMICA_H
#define LISTADINAMICA_H

#include <iostream>
#include <fstream> 
#include <string>  

using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
};

class ListaDinamica {
private:
    Nodo* inicio;
    int obtenerSiguienteID(); 

public:
    ListaDinamica();
    ~ListaDinamica();
    void insertar(int valor);
    void eliminarInicio();
    void mostrarLista();
    bool estaVacia();
    void guardarArchivos(); 
};

#endif
