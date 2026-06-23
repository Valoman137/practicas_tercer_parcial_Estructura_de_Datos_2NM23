#include "Calculadora.h"
#include <stdexcept> 
#include <cstdlib>   

CalculadoraBasica::CalculadoraBasica() {}
CalculadoraBasica::~CalculadoraBasica() {}

int CalculadoraBasica::sumar(int a, int b) { return a + b; }
int CalculadoraBasica::restar(int a, int b) { return a - b; }
int CalculadoraBasica::multiplicar(int a, int b) { return a * b; }
int CalculadoraBasica::dividir(int a, int b) { 
    if(b == 0) throw invalid_argument("Division por cero");
    return a / b; 
}

CalculadoraSucesiva::CalculadoraSucesiva() {}
CalculadoraSucesiva::~CalculadoraSucesiva() {}

int CalculadoraSucesiva::multiplicar(int a, int b) {
    int resultado = 0;
    for(int i = 0; i < abs(b); i++) {
        resultado += abs(a);
    }
    if ((a < 0 && b > 0) || (a > 0 && b < 0)) return -resultado;
    return resultado;
}

int CalculadoraSucesiva::dividir(int a, int b) {
    if (b == 0) {
        cout << "Error: Division por cero.\n";
        return 0; 
    }
    int dividendo = abs(a);
    int divisor = abs(b);
    int cociente = 0;
    
    while (dividendo >= divisor) {
        dividendo -= divisor;
        cociente++;
    }
    
    if ((a < 0 && b > 0) || (a > 0 && b < 0)) return -cociente;
    return cociente;
}

int CalculadoraSucesiva::potencia(int base, int exponente) {
    if (exponente == 0) return 1;
    int resultado = 1;
    for (int i = 0; i < exponente; i++) {
        resultado = multiplicar(resultado, base); 
    }
    return resultado;
}
