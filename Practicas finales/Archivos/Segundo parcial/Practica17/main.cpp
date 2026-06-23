#include "MergeSort.h"

int main() {
    OrdenamientoMerge ms;
    int n;

    cout << "=== ALGORITMO MERGE SORT (EJERCICIO 17) ===\n";
    cout << "Cuantos numeros deseas ordenar? ";
    cin >> n;

    int* datos = new int[n];

    for (int i = 0; i < n; i++) {
        cout << "Ingresa el valor para la posicion [" << i << "]: ";
        cin >> datos[i];
    }

    cout << "\nArreglo original:\n";
    ms.imprimirArreglo(datos, n);

    ms.ordenar(datos, 0, n - 1);

    cout << "\nArreglo ordenado:\n";
    ms.imprimirArreglo(datos, n);

    cout << "\nGenerando reportes del arreglo ordenado...";
    ms.guardarArchivos(datos, n);

    delete[] datos; 
    
    cout << "\nPresiona una tecla para finalizar...";
    cin.ignore();
    cin.get();
    
    return 0;
}
