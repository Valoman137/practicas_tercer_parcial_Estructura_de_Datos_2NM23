#include "ColaDinamica.h"

int main() {
    ColaDinamica miCola;
    int tamano, valor;

    cout << "=== CONFIGURACION DE LA COLA (EJERCICIO 7) ===\n";
    cout << "Cuantos elementos deseas encolar? ";
    cin >> tamano;

    for(int i = 0; i < tamano; i++) {
        cout << "Ingresa el valor para el elemento [" << i + 1 << "]: ";
        cin >> valor;
        miCola.enqueue(valor);
    }

    cout << "\n--- Estado de la Cola --\n";
    miCola.mostrarFrente();
    
    cout << "\nAtendiendo al primer cliente (dequeue)..." << endl;
    miCola.dequeue();
    
    miCola.mostrarFrente();

    cout << "\nGenerando reportes de la cola...";
    miCola.guardarArchivos();

    cout << "\nPresiona una tecla para finalizar...";
    cin.ignore();
    cin.get();
    
    return 0;
}
