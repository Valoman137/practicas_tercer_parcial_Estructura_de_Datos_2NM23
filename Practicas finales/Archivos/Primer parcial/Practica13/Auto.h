#ifndef AUTO_H
#define AUTO_H

#include <iostream>
#include <string>

using namespace std;

class Auto {
private:
    float precio;
    int anio;

public:
    Auto();

    void pedirDatos();
    void mostrarDatos();

    void guardarTXT();
    void guardarCSV();
    void guardarXML();
    void guardarHTML();
    void guardarJSON();
    void leerTXT();
};

#endif
