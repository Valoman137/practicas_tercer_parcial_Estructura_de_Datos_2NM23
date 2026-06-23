#include <iostream>
#include "Persona.h"
#include "Auto.h"

using namespace std;

int main() {

    int n, m;

    Persona personaAux;
    Auto autoAux;

    personaAux.leerTXT();
    autoAux.leerTXT();

    cout << "\nCuantas personas deseas registrar?: ";
    cin >> n;

    Persona* personas = new Persona[n];

    for (int i = 0; i < n; i++) {
        cout << "\nPersona #" << i + 1 << endl;

        personas[i].pedirDatos();

        personas[i].guardarTXT();
        personas[i].guardarCSV();
        personas[i].guardarXML();
        personas[i].guardarHTML();
        personas[i].guardarJSON();
    }

    cout << "\n===== LISTA DE PERSONAS =====\n";

    for (int i = 0; i < n; i++) {
        personas[i].mostrarDatos();
    }

    cout << "\nCuantos autos deseas registrar?: ";
    cin >> m;

    Auto* autos = new Auto[m];

    for (int i = 0; i < m; i++) {
        cout << "\nAuto #" << i + 1 << endl;

        autos[i].pedirDatos();

        autos[i].guardarTXT();
        autos[i].guardarCSV();
        autos[i].guardarXML();
        autos[i].guardarHTML();
        autos[i].guardarJSON();
    }

    cout << "\n===== LISTA DE AUTOS =====\n";

    for (int i = 0; i < m; i++) {
        autos[i].mostrarDatos();
    }

    cout << "\n----- Tamaño de datos -----\n";
    cout << "int: " << sizeof(int) << " bytes" << endl;
    cout << "float: " << sizeof(float) << " bytes" << endl;
    cout << "Persona: " << sizeof(Persona) << " bytes" << endl;
    cout << "Auto: " << sizeof(Auto) << " bytes" << endl;

    delete[] personas;
    delete[] autos;

    cout << "\nDatos guardados correctamente en TXT, CSV, XML, HTML y JSON.\n";

    return 0;
}
