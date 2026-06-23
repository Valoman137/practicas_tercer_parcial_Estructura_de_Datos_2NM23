#ifndef CALCULADORA_H
#define CALCULADORA_H

#include <iostream>
using namespace std;

class CalculadoraBasica {
public:
    CalculadoraBasica();
    virtual ~CalculadoraBasica();
    
    virtual int sumar(int a, int b);
    virtual int restar(int a, int b);
    virtual int multiplicar(int a, int b);
    virtual int dividir(int a, int b);
};

class CalculadoraSucesiva : public CalculadoraBasica {
public:
    CalculadoraSucesiva();
    ~CalculadoraSucesiva();
    
    int multiplicar(int a, int b) override;
    int dividir(int a, int b) override;
    
    int potencia(int base, int exponente);
};

#endif
