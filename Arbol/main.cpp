#include <iostream>
#include <string>
#include "Arbol.h"

using namespace std;

void mostrarMenu() {
    cout << "\n===== MENU ARBOL BINARIO DE BUSQUEDA =====\n";
    cout << "1. Insertar valor\n";
    cout << "2. Eliminar valor\n";
    cout << "3. Buscar valor\n";
    cout << "4. Recorrido Preorder\n";
    cout << "5. Recorrido Inorder\n";
    cout << "6. Recorrido Postorder\n";
    cout << "7. Mostrar altura del arbol\n";
    cout << "8. Mostrar profundidad de un valor\n";
    cout << "9. Mostrar amplitud (ancho maximo)\n";
    cout << "10. Salir\n";
    cout << "Elige una opcion: ";
}

int main() {
    Arbol arbol("arbol.txt"); // al iniciar, carga lo que ya exista en arbol.txt

    int opcion;
    string valor;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Valor a insertar (letra, numero o combinacion): ";
                cin >> valor;
                arbol.insertar(valor);
                break;

            case 2:
                cout << "Valor a eliminar: ";
                cin >> valor;
                arbol.eliminar(valor);
                break;

            case 3:
                cout << "Valor a buscar: ";
                cin >> valor;
                if (arbol.buscar(valor)) {
                    cout << "El valor \"" << valor << "\" SI esta en el arbol.\n";
                } else {
                    cout << "El valor \"" << valor << "\" NO esta en el arbol.\n";
                }
                break;

            case 4:
                arbol.mostrarPreorder();
                break;

            case 5:
                arbol.mostrarInorder();
                break;

            case 6:
                arbol.mostrarPostorder();
                break;

            case 7:
                arbol.mostrarAltura();
                break;

            case 8:
                cout << "Valor del que quieres saber la profundidad: ";
                cin >> valor;
                arbol.mostrarProfundidad(valor);
                break;

            case 9:
                arbol.mostrarAmplitud();
                break;

            case 10:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opcion no valida.\n";
        }

    } while (opcion != 10);

    return 0;
}
