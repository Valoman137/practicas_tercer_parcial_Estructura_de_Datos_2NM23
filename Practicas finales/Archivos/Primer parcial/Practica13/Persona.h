#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>
#include <string>

using namespace std;

class Persona {
private:
    string nombre;
    string ap;
    string am;
    string genero;
    int edad;

public:
    Persona();

    void pedirDatos();
    void mostrarDatos();

    // Funciones para archivos
    void guardarTXT();
    void guardarCSV();
    void guardarXML();
    void guardarHTML();
    void guardarJSON();
    void leerTXT();
};

#endif
