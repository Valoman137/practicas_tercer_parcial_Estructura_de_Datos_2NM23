#include "Auto.h"
#include <fstream>

using namespace std;

Auto::Auto() {}

void Auto::pedirDatos() {
    cout << "\n--- Datos Auto ---" << endl;

    cout << "Precio: ";
    cin >> precio;

    cout << "Anio: ";
    cin >> anio;
}

void Auto::mostrarDatos() {
    cout << "\nAuto registrado:" << endl;
    cout << "Precio: " << precio << endl;
    cout << "Anio: " << anio << endl;
}

void Auto::guardarTXT() {
    ofstream archivo("auto.txt", ios::app);

    archivo << "Precio: " << precio << endl;
    archivo << "Anio: " << anio << endl;
    archivo << "------------------------" << endl;

    archivo.close();
}

void Auto::leerTXT() {
    ifstream archivo("auto.txt");

    if (archivo.is_open()) {

        string linea;

        cout << "\n=== Autos guardados anteriormente ===\n";

        while (getline(archivo, linea)) {
            cout << linea << endl;
        }

        archivo.close();
    }
}

void Auto::guardarCSV() {
    ofstream archivo("auto.csv", ios::app);

    archivo << precio << "," << anio << endl;

    archivo.close();
}

void Auto::guardarXML() {
    ofstream archivo("auto.xml", ios::app);

    archivo << "<auto>" << endl;
    archivo << "  <precio>" << precio << "</precio>" << endl;
    archivo << "  <anio>" << anio << "</anio>" << endl;
    archivo << "</auto>" << endl;

    archivo.close();
}

void Auto::guardarHTML() {
    ofstream archivo("auto.html", ios::app);

    archivo << "<p>";
    archivo << "Precio: " << precio
            << " - Anio: " << anio;
    archivo << "</p>" << endl;

    archivo.close();
}

void Auto::guardarJSON() {
    ofstream archivo("auto.json", ios::app);

    archivo << "{ ";
    archivo << "\"precio\":" << precio << ", ";
    archivo << "\"anio\":" << anio;
    archivo << " }" << endl;

    archivo.close();
}
