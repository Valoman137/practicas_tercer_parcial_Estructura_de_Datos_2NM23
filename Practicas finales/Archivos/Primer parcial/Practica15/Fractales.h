#ifndef FRACTALES_H
#define FRACTALES_H

#include <iostream>
#include <cmath>
using namespace std;

class GeneradorFractales {
private:
    void cantorRecursivo(int inicio, int fin, int nivelActual, int nivelMaximo, char* linea);
    void sierpinskiRecursivo(int x, int y, int tamano, char** tablero);

public:
    GeneradorFractales();
    ~GeneradorFractales();

    void generarPolvoCantor(int iteraciones);
    void generarSierpinski(int iteraciones);
};

#endif
