#include "Fractales.h"

int main() {
    GeneradorFractales generador;
    int opcion;
    
    do {
        cout << "=== FRACTALES RECURSIVOS ===\n";
        cout << "1. Polvo de Cantor\n";
        cout << "2. Triangulo de Sierpinski\n";
        cout << "3. Salir\n";
        cout << "Elige un fractal: ";
        cin >> opcion;
        
        if (opcion == 1) {
            int nivel;
            cout << "Ingresa el numero de iteraciones (sugiero entre 2 y 4): ";
            cin >> nivel;
            generador.generarPolvoCantor(nivel);
            
        } else if (opcion == 2) {
            int nivel;
            // Si se hace más de 5 se deforma el triangulo
            cout << "Ingresa la profundidad del triangulo (sugiero entre 3 y 5): "; 
            cin >> nivel;
            generador.generarSierpinski(nivel);
            
        } else if (opcion != 3) {
            cout << "Opcion invalida.\n\n";
        }
        
    } while (opcion != 3);
    
    cout << "Saliendo...\n";
    return 0;
}
