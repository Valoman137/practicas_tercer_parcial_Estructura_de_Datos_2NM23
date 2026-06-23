#include "ColaDinamica.h"
#include <sstream> 

ColaDinamica::ColaDinamica() {
    frente = NULL;
    final = NULL;
}

int ColaDinamica::obtenerSiguienteID() {
    int id = 1;
    while(true) {
        stringstream ss;
        ss << "salida_cola" << id << ".txt";
        string nombreTest = ss.str();
        
        ifstream archivoPrueba(nombreTest.c_str());
        if(!archivoPrueba.good()) { 
            return id;
        }
        archivoPrueba.close();
        id++;
    }
}

void ColaDinamica::guardarArchivos() {
    int id = obtenerSiguienteID();
    
    stringstream ss;
    ss << "salida_cola" << id;
    string base = ss.str();
    
    ofstream fTxt((base + ".txt").c_str());
    ofstream fCsv((base + ".csv").c_str());
    ofstream fXml((base + ".xml").c_str());
    ofstream fHtml((base + ".html").c_str());
    ofstream fJson((base + ".json").c_str());
    
    // Encabezados
    fTxt << "=== ESTADO FINAL DE LA COLA ===\n";
    fCsv << "Posicion,Valor\n";
    fXml << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Cola>\n";
    fHtml << "<!DOCTYPE html>\n<html>\n<body>\n<h2>Contenido de la Cola</h2>\n<ul>\n";
    fJson << "{\n  \"elementos\": [\n";

    Nodo* actual = frente;
    int pos = 1;
    bool primero = true;

    if (actual == NULL) {
        fTxt << "La cola se encuentra vacia.\n";
    }

    while(actual != NULL) {
        // TXT
        fTxt << "Elemento [" << pos << "]: " << actual->dato << "\n";
        
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

    fXml << "</Cola>\n";
    fHtml << "</ul>\n</body>\n</html>\n";
    fJson << "\n  ]\n}\n";

    fTxt.close(); 
    fCsv.close(); 
    fXml.close(); 
    fHtml.close(); 
    fJson.close();
    
    cout << "\n[EXITO] Archivos guardados como " << base << ".* (txt, csv, xml, html, json)\n";
}

void ColaDinamica::enqueue(int valor) {
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->dato = valor;
    nuevoNodo->siguiente = NULL;

    if (estaVacia()) {
        frente = nuevoNodo;
    } else {
        final->siguiente = nuevoNodo;
    }
    final = nuevoNodo;
    cout << "Elemento " << valor << " agregado a la cola.\n";
}

void ColaDinamica::dequeue() {
    if (estaVacia()) {
        cout << "Error: La cola esta vacia.\n";
        return;
    }
    Nodo* temporal = frente;
    int valorEliminado = temporal->dato;
    
    frente = frente->siguiente;
    
    if (frente == NULL) {
        final = NULL;
    }

    delete temporal;
    cout << "Elemento " << valorEliminado << " ha salido de la cola.\n";
}

bool ColaDinamica::estaVacia() {
    return frente == NULL;
}

void ColaDinamica::mostrarFrente() {
    if (!estaVacia()) {
        cout << "Primer elemento en espera (frente): " << frente->dato << "\n";
    } else {
        cout << "La cola esta vacia.\n";
    }
}

ColaDinamica::~ColaDinamica() {
    while (!estaVacia()) {
        dequeue();
    }
}
