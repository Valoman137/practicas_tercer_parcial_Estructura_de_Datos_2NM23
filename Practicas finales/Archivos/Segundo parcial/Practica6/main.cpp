#include "PilaDinamica.h"

int main() {
    PilaDinamica miPila;
    int tamano, valor;

    cout << "=== CONFIGURACION DE LA PILA ===\n";
    cout << "Cuantos elementos deseas ingresar? ";
    cin >> tamano;

    for(int i = 0; i < tamano; i++) {
        cout << "Ingresa el valor para el elemento [" << i + 1 << "]: ";
        cin >> valor;
        miPila.push(valor);
    }

    cout << "\n--- Resultados de la Pila ---\n";
    miPila.mostrarTope();
    
    cout << "\nDeseas eliminar el tope? (Presiona Enter para ver la operacion)";
    cin.ignore();
    cin.get();
    
    miPila.pop();
    miPila.mostrarTope();

    cout << "\nGenerando reportes de la pila...";
    miPila.guardarArchivos();

    cout << "\nPresiona una tecla para salir...";
    cin.get();
    
    return 0;
}
