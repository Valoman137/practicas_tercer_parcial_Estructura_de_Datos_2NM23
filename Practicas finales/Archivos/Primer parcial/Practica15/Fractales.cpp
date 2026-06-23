#include "Fractales.h"

GeneradorFractales::GeneradorFractales() {}
GeneradorFractales::~GeneradorFractales() {}

// Polvo cantor
void GeneradorFractales::cantorRecursivo(int inicio, int fin, int nivelActual, int nivelMaximo, char* linea) {
    if (nivelActual == nivelMaximo) return; // Detener recursividad
    
    int longitud = fin - inicio;
    if (longitud < 3) return; // No se puede dividir mas
    
    int tercio = longitud / 3;
    
    for (int i = inicio + tercio; i < inicio + 2 * tercio; i++) {
        linea[i] = ' ';
    }
    
    // Llamadas recursivas "Divide y venceras" 
    cantorRecursivo(inicio, inicio + tercio, nivelActual + 1, nivelMaximo, linea);
    cantorRecursivo(inicio + 2 * tercio, fin, nivelActual + 1, nivelMaximo, linea);
}

void GeneradorFractales::generarPolvoCantor(int iteraciones) {
    int longitud = pow(3, iteraciones); // El tamaño debe ser múltiplo de 3
    char* linea = new char[longitud + 1]; // Arreglo dinamico
    
    cout << "\n--- POLVO DE CANTOR (Nivel " << iteraciones << ") ---\n\n";
    
    for (int nivel = 0; nivel <= iteraciones; nivel++) {
        for (int i = 0; i < longitud; i++) linea[i] = '#';
        linea[longitud] = '\0';
        
        cantorRecursivo(0, longitud, 0, nivel, linea);
        
        cout << "Paso " << nivel << ": " << linea << "\n";
    }
    cout << "\n";
    delete[] linea; 
}


// Triangulo
void GeneradorFractales::sierpinskiRecursivo(int x, int y, int tamano, char** tablero) {
    if (tamano == 1) {
        tablero[y][x] = '*';
        return;
    }
    
    int mitad = tamano / 2;
    
    // 3 Llamadas recursivas para dibujar los 3 triangulitos
    sierpinskiRecursivo(x, y, mitad, tablero);               // Triangulo superior
    sierpinskiRecursivo(x - mitad, y + mitad, mitad, tablero); // Triangulo inferior izquierdo
    sierpinskiRecursivo(x + mitad, y + mitad, mitad, tablero); // Triangulo inferior derecho
}

void GeneradorFractales::generarSierpinski(int iteraciones) {
    int tamano = pow(2, iteraciones);
    int ancho = tamano * 2;
    
    cout << "\n--- TRIANGULO DE SIERPINSKI (Nivel " << iteraciones << ") ---\n\n";
    
    char** tablero = new char*[tamano];
    for (int i = 0; i < tamano; i++) {
        tablero[i] = new char[ancho];
        for (int j = 0; j < ancho; j++) {
            tablero[i][j] = ' '; 
        }
    }
    
    sierpinskiRecursivo(tamano - 1, 0, tamano, tablero);
    
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < ancho; j++) {
            cout << tablero[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
    
    for (int i = 0; i < tamano; i++) delete[] tablero[i];
    delete[] tablero;
}
