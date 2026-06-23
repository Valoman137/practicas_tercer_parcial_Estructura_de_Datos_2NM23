#include "PilaDinamica.h"
#include <sstream> 

PilaDinamica::PilaDinamica() {
    tope = NULL;
}

int PilaDinamica::obtenerSiguienteID() {
    int id = 1;
    while(true) {
        stringstream ss;
        ss << "salida_pila" << id << ".txt";
        string nombreTest = ss.str();
        
        ifstream archivoPrueba(nombreTest.c_str());
        if(!archivoPrueba.good()) { 
            return id;
        }
        archivoPrueba.close();
        id++;
    }
}

void PilaDinamica::guardarArchivos() {
    int id = obtenerSiguienteID();
    
    stringstream ss;
    ss << "salida_pila" << id;
    string base = ss.str();
    
    ofstream fTxt((base + ".txt").c_str());
    ofstream fCsv((base + ".csv").c_str());
    ofstream fXml((base + ".xml").c_str());
    ofstream fHtml((base + ".html").c_str());
    ofstream fJson((base + ".json").c_str());
    
    // Emcabezados
    fTxt << "=== ESTADO FINAL DE LA PILA ===\n";
    fCsv << "Posicion,Valor\n";
    fXml << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Pila>\n";
    fHtml << "<!DOCTYPE html>\n<html>\n<body>\n<h2>Contenido de la Pila</h2>\n<ul>\n";
    fJson << "{\n  \"elementos\": [\n";

    Nodo* actual = tope;
    int pos = 1;
    bool primero = true;

    if (actual == NULL) {
        fTxt << "La pila se encuentra vacia.\n";
    }

    while(actual != NULL) {
        // TXT
        fTxt << "Nodo [" << pos << "]: " << actual->dato << "\n";
        
        // CSV
        fCsv << pos << "," << actual->dato << "\n";
        
        // XML
        fXml << "  <Nodo>\n    <Posicion>" << pos << "</Posicion>\n    <Valor>" << actual->dato << "</Valor>\n  </Nodo>\n";
        
        // HTML
        fHtml << "  <li>Posición " << pos << ": <strong>" << actual->dato << "</strong></li>\n";
        
        // JSON
        if(!primero) fJson << ",\n";
        fJson << "    {\n      \"posicion\": " << pos << ",\n      \"valor\": " << actual->dato << "\n    }";
        primero = false;
        
        actual = actual->siguiente;
        pos++;
    }

    fXml << "</Pila>\n";
    fHtml << "</ul>\n</body>\n</html>\n";
    fJson << "\n  ]\n}\n";

    fTxt.close(); 
    fCsv.close(); 
    fXml.close(); 
    fHtml.close(); 
    fJson.close();
    
    cout << "\n[EXITO] Archivos guardados como " << base << ".* (txt, csv, xml, html, json)\n";
}

void PilaDinamica::push(int valor) {
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->dato = valor;
    nuevoNodo->siguiente = tope;
    tope = nuevoNodo;
    cout << "Elemento " << valor << " insertado correctamente.\n";
}

void PilaDinamica::pop() {
    if (estaVacia()) {
        cout << "Error: Pila vacia.\n";
        return;
    }
    Nodo* temporal = tope;
    int valorEliminado = temporal->dato;
    tope = tope->siguiente;
    delete temporal;
    cout << "Elemento " << valorEliminado << " sacado de la pila.\n";
}

bool PilaDinamica::estaVacia() {
    return tope == NULL;
}

void PilaDinamica::mostrarTope() {
    if (!estaVacia()) {
        cout << "Tope actual: " << tope->dato << "\n";
    } else {
        cout << "Pila vacia.\n";
    }
}

PilaDinamica::~PilaDinamica() {
    while (!estaVacia()) {
        pop();
    }
}
