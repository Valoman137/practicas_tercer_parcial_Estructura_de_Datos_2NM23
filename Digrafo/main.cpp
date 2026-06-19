#include <iostream>
#include <string>
#include "Digrafo.h"

using namespace std;

void mostrarMenu() {
    cout << "\n===== MENU DIGRAFO =====\n";
    cout << "1. Agregar nodo\n";
    cout << "2. Eliminar nodo\n";
    cout << "3. Agregar arista (origen -> destino)\n";
    cout << "4. Eliminar arista\n";
    cout << "5. Mostrar digrafo\n";
    cout << "6. Mostrar camino de un nodo inicial a un nodo final\n";
    cout << "7. Salir\n";
    cout << "Elige una opcion: ";
}

int main() {
    Digrafo digrafo("digrafo.txt"); // al iniciar, carga lo que ya exista en digrafo.txt

    int opcion;
    string nodo, origen, destino;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Nombre del nodo (letra, numero o combinacion): ";
                cin >> nodo;
                digrafo.agregarNodo(nodo);
                break;

            case 2:
                cout << "Nodo a eliminar: ";
                cin >> nodo;
                digrafo.eliminarNodo(nodo);
                break;

            case 3:
                cout << "Nodo origen: ";
                cin >> origen;
                cout << "Nodo destino: ";
                cin >> destino;
                digrafo.agregarArista(origen, destino);
                break;

            case 4:
                cout << "Nodo origen: ";
                cin >> origen;
                cout << "Nodo destino: ";
                cin >> destino;
                digrafo.eliminarArista(origen, destino);
                break;

            case 5:
                digrafo.mostrarGrafo();
                break;

            case 6:
                cout << "Nodo inicial: ";
                cin >> origen;
                cout << "Nodo final: ";
                cin >> destino;
                digrafo.mostrarCamino(origen, destino);
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
