#include "Calculadora.h"
#include <stdexcept> 

int main() {
    CalculadoraSucesiva miCalc;
    int opcion;
    int num1, num2;
    
    do {
        cout << "\n=== CALCULADORA POR SUCESIONES ===\n";
        cout << "1. Suma\n";
        cout << "2. Resta\n";
        cout << "3. Multiplicacion\n";
        cout << "4. Dividision\n";
        cout << "5. Potencia\n";
        cout << "6. Salir\n";
        cout << "Elige una opcion: ";
        cin >> opcion;
        
        if (opcion >= 1 && opcion <= 5) {
            cout << "Ingresa el primer numero: ";
            cin >> num1;
            cout << "Ingresa el segundo numero: ";
            cin >> num2;
            
            cout << "\n--- Resultado ---\n";
            
            try {
                switch(opcion) {
                    case 1: 
                        cout << num1 << " + " << num2 << " = " << miCalc.sumar(num1, num2) << "\n"; 
                        break;
                    case 2: 
                        cout << num1 << " - " << num2 << " = " << miCalc.restar(num1, num2) << "\n"; 
                        break;
                    case 3: 
                        cout << num1 << " * " << num2 << " = " << miCalc.multiplicar(num1, num2) << "\n"; 
                        break;
                    case 4: 
                        cout << num1 << " / " << num2 << " = " << miCalc.dividir(num1, num2) << "\n"; 
                        break;
                    case 5: 
                        cout << num1 << " ^ " << num2 << " = " << miCalc.potencia(num1, num2) << "\n"; 
                        break;
                }
            } catch (const invalid_argument& e) {
                cout << "Excepcion atrapada: " << e.what() << "\n";
            }
            
        } else if (opcion != 6) {
            cout << "Opcion no valida. Intenta de nuevo.\n";
        }
        
    } while (opcion != 6);
    
    cout << "Saliendo de la calculadora...\n";
    
    return 0;
}
