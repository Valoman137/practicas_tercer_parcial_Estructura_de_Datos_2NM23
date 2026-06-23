#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <iostream>
#include <fstream> 
#include <string> 

using namespace std;

class OrdenamientoQuick {
private:
    int obtenerSiguienteID(); 

public:
    void intercambiar(int& a, int& b);
    
    int particion(int arreglo[], int bajo, int alto);
    
    void ordenar(int arreglo[], int bajo, int alto);
    
    void imprimirArreglo(int arreglo[], int tamano);

    void guardarArchivos(int arreglo[], int tamano);
};

#endif
