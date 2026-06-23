#include <iostream>
#include <string>
#include "Estructuras.h"

using namespace std;

// Una sola funcion para elegir unidad: esTiempo=false -> metros/cm/km, esTiempo=true -> s/min/h
string elegirUnidad(bool esTiempo) {
    int opcion;
    if (esTiempo) cout << "Unidad de tiempo:\n1. Segundos (s)\n2. Minutos (min)\n3. Horas (h)\n";
    else cout << "Unidad de distancia:\n1. Metros (m)\n2. Centimetros (cm)\n3. Kilometros (km)\n";
    cout << "Elige una opcion: ";
    cin >> opcion;
    if (esTiempo) return opcion == 2 ? "min" : opcion == 3 ? "h" : "s";
    return opcion == 2 ? "cm" : opcion == 3 ? "km" : "m";
}

// Un solo submenu para Grafo y Digrafo: el parametro "dirigido" controla
// el titulo y se lo pasa tal cual al objeto, que ya sabe comportarse distinto.
void menuGrafo(Grafo& g, bool dirigido) {
    int opcion;
    string nodo, nodoA, nodoB;
    string titulo = dirigido ? "DIGRAFO (dirigido)" : "GRAFO (no dirigido)";

    do {
        cout << "\n===== MENU " << titulo << " =====\n";
        cout << "1. Agregar nodo\n";
        cout << "2. Eliminar nodo\n";
        cout << "3. Agregar arista (con distancia y tiempo)\n";
        cout << "4. Eliminar arista\n";
        cout << "5. Mostrar " << (dirigido ? "digrafo" : "grafo") << "\n";
        cout << "6. Buscar camino mas conveniente (Dijkstra)\n";
        cout << "7. Regresar al menu principal\n";
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Nombre del nodo (letra, numero o combinacion): ";
                cin >> nodo;
                g.agregarNodo(nodo);
                break;

            case 2:
                cout << "Nodo a eliminar: ";
                cin >> nodo;
                g.eliminarNodo(nodo);
                break;

            case 3: {
                cout << "Nodo origen: ";
                cin >> nodoA;
                cout << "Nodo destino: ";
                cin >> nodoB;

                double distValor, tiempoValor;
                cout << "Valor de la distancia: ";
                cin >> distValor;
                string distUnidad = elegirUnidad(false);

                cout << "Valor del tiempo: ";
                cin >> tiempoValor;
                string tiempoUnidad = elegirUnidad(true);

                g.agregarArista(nodoA, nodoB, distValor, distUnidad, tiempoValor, tiempoUnidad);
                break;
            }

            case 4:
                cout << "Nodo origen: ";
                cin >> nodoA;
                cout << "Nodo destino: ";
                cin >> nodoB;
                g.eliminarArista(nodoA, nodoB);
                break;

            case 5:
                g.mostrarGrafo();
                break;

            case 6:
                cout << "Nodo desde donde partes: ";
                cin >> nodoA;
                cout << "Nodo que quieres buscar: ";
                cin >> nodoB;
                g.mostrarCamino(nodoA, nodoB);
                break;

            case 7:
                cout << "Regresando al menu principal...\n";
                break;

            default:
                cout << "Opcion no valida.\n";
        }

    } while (opcion != 7);
}

void menuArbol(Arbol& arbol) {
    int opcion;
    string valor;

    do {
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
        cout << "10. Regresar al menu principal\n";
        cout << "Elige una opcion: ";
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
                cout << "Regresando al menu principal...\n";
                break;

            default:
                cout << "Opcion no valida.\n";
        }

    } while (opcion != 10);
}

int main() {
    Grafo grafo("grafo.json", false);   // no dirigido
    Grafo digrafo("digrafo.json", true); // dirigido
    Arbol arbol("arbol.json");

    int opcion;

    do {
        cout << "\n===== MENU PRINCIPAL =====\n";
        cout << "1. Trabajar con Grafo (no dirigido)\n";
        cout << "2. Trabajar con Digrafo (dirigido)\n";
        cout << "3. Trabajar con Arbol Binario de Busqueda\n";
        cout << "4. Salir del programa\n";
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: menuGrafo(grafo, false); break;
            case 2: menuGrafo(digrafo, true); break;
            case 3: menuArbol(arbol); break;
            case 4: cout << "Saliendo del programa...\n"; break;
            default: cout << "Opcion no valida.\n";
        }

    } while (opcion != 4);

    return 0;
}
