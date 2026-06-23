#include "ListaDinamica.h"
#include <sstream> 

ListaDinamica::ListaDinamica() {
    inicio = NULL;
}

int ListaDinamica::obtenerSiguienteID() {
    int id = 1;
    while(true) {
        stringstream ss;
        ss << "salida_lista" << id << ".txt";
        string nombreTest = ss.str();
        
        ifstream archivoPrueba(nombreTest.c_str());
        if(!archivoPrueba.good()) { 
            return id;
        }
        archivoPrueba.close();
        id++;
    }
}

void ListaDinamica::guardarArchivos() {
    int id = obtenerSiguienteID();
    
    stringstream ss;
    ss << "salida_lista" << id;
    string base = ss.str();
    
    ofstream fTxt((base + ".txt").c_str());
    ofstream fCsv((base + ".csv").c_str());
    ofstream fXml((base + ".xml").c_str());
    ofstream fHtml((base + ".html").c_str());
    ofstream fJson((base + ".json").c_str());
    
    // Encabezados
    fTxt << "=== ESTADO FINAL DE LA LISTA ===\n";
    fCsv << "Posicion,Valor\n";
    fXml << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Lista>\n";
    fHtml << "<!DOCTYPE html>\n<html>\n<body>\n<h2>Contenido de la Lista</h2>\n<ul>\n";
    fJson << "{\n  \"elementos\": [\n";

    Nodo* actual = inicio;
    int pos = 1;
    bool primero = true;

    if (actual == NULL) {
        fTxt << "La lista se encuentra vacia.\n";
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

    fXml << "</Lista>\n";
    fHtml << "</ul>\n</body>\n</html>\n";
    fJson << "\n  ]\n}\n";

    fTxt.close(); 
    fCsv.close(); 
    fXml.close(); 
    fHtml.close(); 
    fJson.close();
    
    cout << "\n[EXITO] Archivos guardados como " << base << ".* (txt, csv, xml, html, json)\n";
}

void ListaDinamica::insertar(int valor) {
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->dato = valor;
    nuevoNodo->siguiente = NULL;

    if (estaVacia()) {
        inicio = nuevoNodo;
    } else {
        Nodo* temporal = inicio;
        while (temporal->siguiente != NULL) {
            temporal = temporal->siguiente;
        }
        temporal->siguiente = nuevoNodo;
    }
    cout << "Elemento " << valor << " agregado a la lista.\n";
}

void ListaDinamica::eliminarInicio() {
    if (estaVacia()) {
        cout << "La lista esta vacia.\n";
        return;
    }
    Nodo* temporal = inicio;
    inicio = inicio->siguiente;
    cout << "Eliminando dato: " << temporal->dato << endl;
    delete temporal;
}

bool ListaDinamica::estaVacia() {
    return inicio == NULL;
}

void ListaDinamica::mostrarLista() {
    if (estaVacia()) {
        cout << "Lista vacia." << endl;
        return;
    }
    Nodo* temporal = inicio;
    cout << "Contenido de la lista: ";
    while (temporal != NULL) {
        cout << "[" << temporal->dato << "] -> ";
        temporal = temporal->siguiente;
    }
    cout << "NULL" << endl;
}

ListaDinamica::~ListaDinamica() {
    while (!estaVacia()) {
        eliminarInicio();
    }
}
