#ifndef MERGESORT_H
#define MERGESORT_H

#include <iostream>
#include <fstream> 
#include <string>  

using namespace std;

class OrdenamientoMerge {
private:
    int obtenerSiguienteID(); 

public:
    void ordenar(int arreglo[], int izquierda, int derecha);
    
    void mezclar(int arreglo[], int izquierda, int medio, int derecha);
    
    void imprimirArreglo(int arreglo[], int tamano);

    void guardarArchivos(int arreglo[], int tamano);
};

#endif
