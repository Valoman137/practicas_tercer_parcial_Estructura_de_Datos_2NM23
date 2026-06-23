#include "ListaDinamica.h"

int main() {
    ListaDinamica miLista;
    int tamano, valor;

    cout << "=== CONFIGURACION DE LA LISTA (EJERCICIO 7 BIS) ===\n";
    cout << "Cuantos elementos deseas agregar a la lista? ";
    cin >> tamano;

    for(int i = 0; i < tamano; i++) {
        cout << "Ingresa el valor para el nodo [" << i + 1 << "]: ";
        cin >> valor;
        miLista.insertar(valor);
    }

    cout << "\n--- Visualizacion de la Lista ---\n";
    miLista.mostrarLista();

    cout << "\nGenerando reportes de la lista...";
    miLista.guardarArchivos();

    cout << "\nPresiona una tecla para finalizar...";
    cin.ignore();
    cin.get();
    
    return 0;
}
