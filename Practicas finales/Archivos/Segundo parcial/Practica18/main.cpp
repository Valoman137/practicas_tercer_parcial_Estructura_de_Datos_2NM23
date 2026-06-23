#include "QuickSort.h"

int main() {
    OrdenamientoQuick qs;
    int n;

    cout << "=== ALGORITMO QUICK SORT (EJERCICIO 18) ===\n";
    cout << "Cuantos numeros deseas ordenar? ";
    cin >> n;

    int* datos = new int[n];

    for (int i = 0; i < n; i++) {
        cout << "Ingresa el valor para [" << i << "]: ";
        cin >> datos[i];
    }

    cout << "\nArreglo original:\n";
    qs.imprimirArreglo(datos, n);

    qs.ordenar(datos, 0, n - 1);

    cout << "\nArreglo ordenado:\n";
    qs.imprimirArreglo(datos, n);

    cout << "\nGenerando reportes del arreglo ordenado...";
    qs.guardarArchivos(datos, n);

    delete[] datos; 
    
    cout << "\nPresiona una tecla para salir...";
    cin.ignore();
    cin.get();
    
    return 0;
}
