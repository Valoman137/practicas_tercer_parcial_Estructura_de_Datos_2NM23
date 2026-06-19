#include <iostream>
#include <string>
#include "Grafo.h"

using namespace std;

void mostrarMenu() {
    cout << "\n===== MENU GRAFO =====\n";
    cout << "1. Agregar nodo\n";
    cout << "2. Eliminar nodo\n";
    cout << "3. Agregar arista\n";
    cout << "4. Eliminar arista\n";
    cout << "5. Mostrar grafo\n";
    cout << "6. Buscar nodo (camino mas conveniente)\n";
    cout << "7. Salir\n";
    cout << "Elige una opcion: ";
}

int main() {
    Grafo grafo("grafo.txt"); // al iniciar, carga lo que ya exista en grafo.txt

    int opcion;
    string nodo, nodoA, nodoB;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Nombre del nodo (letra, numero o combinacion): ";
                cin >> nodo;
                grafo.agregarNodo(nodo);
                break;

            case 2:
                cout << "Nodo a eliminar: ";
                cin >> nodo;
                grafo.eliminarNodo(nodo);
                break;

            case 3:
                cout << "Nodo origen: ";
                cin >> nodoA;
                cout << "Nodo destino: ";
                cin >> nodoB;
                grafo.agregarArista(nodoA, nodoB);
                break;

            case 4:
                cout << "Nodo origen: ";
                cin >> nodoA;
                cout << "Nodo destino: ";
                cin >> nodoB;
                grafo.eliminarArista(nodoA, nodoB);
                break;

            case 5:
                grafo.mostrarGrafo();
                break;

            case 6:
                cout << "Nodo desde donde partes: ";
                cin >> nodoA;
                cout << "Nodo que quieres buscar: ";
                cin >> nodoB;
                grafo.mostrarCamino(nodoA, nodoB);
                break;

            case 7:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opcion no valida.\n";
        }

    } while (opcion != 7);

    return 0;
}
