#include "Persona.h"
#include <fstream>

using namespace std;

Persona::Persona() {}

void Persona::pedirDatos() {
    cout << "\n--- Datos Persona ---" << endl;

    cout << "Nombre: ";
    cin >> nombre;

    cout << "Apellido Paterno: ";
    cin >> ap;

    cout << "Apellido Materno: ";
    cin >> am;

    cout << "Genero: ";
    cin >> genero;

    cout << "Edad: ";
    cin >> edad;
}

void Persona::mostrarDatos() {
    cout << "\nPersona registrada:" << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Apellido Paterno: " << ap << endl;
    cout << "Apellido Materno: " << am << endl;
    cout << "Genero: " << genero << endl;
    cout << "Edad: " << edad << endl;
}

void Persona::guardarTXT() {
    ofstream archivo("persona.txt", ios::app);

    archivo << "Nombre: " << nombre << endl;
    archivo << "Apellido Paterno: " << ap << endl;
    archivo << "Apellido Materno: " << am << endl;
    archivo << "Genero: " << genero << endl;
    archivo << "Edad: " << edad << endl;
    archivo << "------------------------" << endl;

    archivo.close();
}

void Persona::leerTXT() {
    ifstream archivo("persona.txt");

    if (archivo.is_open()) {

        string linea;

        cout << "\n=== Personas guardadas anteriormente ===\n";

        while (getline(archivo, linea)) {
            cout << linea << endl;
        }

        archivo.close();
    }
}

void Persona::guardarCSV() {
    ofstream archivo("persona.csv", ios::app);

    archivo << nombre << ","
            << ap << ","
            << am << ","
            << genero << ","
            << edad << endl;

    archivo.close();
}

void Persona::guardarXML() {
    ofstream archivo("persona.xml", ios::app);

    archivo << "<persona>" << endl;
    archivo << "  <nombre>" << nombre << "</nombre>" << endl;
    archivo << "  <apellidoPaterno>" << ap << "</apellidoPaterno>" << endl;
    archivo << "  <apellidoMaterno>" << am << "</apellidoMaterno>" << endl;
    archivo << "  <genero>" << genero << "</genero>" << endl;
    archivo << "  <edad>" << edad << "</edad>" << endl;
    archivo << "</persona>" << endl;

    archivo.close();
}

void Persona::guardarHTML() {
    ofstream archivo("persona.html", ios::app);

    archivo << "<p>";
    archivo << nombre << " "
            << ap << " "
            << am
            << " - Genero: " << genero
            << " - Edad: " << edad;
    archivo << "</p>" << endl;

    archivo.close();
}

void Persona::guardarJSON() {
    ofstream archivo("persona.json", ios::app);

    archivo << "{ ";
    archivo << "\"nombre\":\"" << nombre << "\", ";
    archivo << "\"apellidoPaterno\":\"" << ap << "\", ";
    archivo << "\"apellidoMaterno\":\"" << am << "\", ";
    archivo << "\"genero\":\"" << genero << "\", ";
    archivo << "\"edad\":" << edad;
    archivo << " }" << endl;

    archivo.close();
}
