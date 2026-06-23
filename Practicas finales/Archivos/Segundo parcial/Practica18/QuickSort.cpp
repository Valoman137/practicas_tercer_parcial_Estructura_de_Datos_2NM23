#include "QuickSort.h"
#include <sstream> 

int OrdenamientoQuick::obtenerSiguienteID() {
    int id = 1;
    while(true) {
        stringstream ss;
        ss << "salida_quicksort" << id << ".txt";
        string nombreTest = ss.str();
        
        ifstream archivoPrueba(nombreTest.c_str());
        if(!archivoPrueba.good()) { 
            return id;
        }
        archivoPrueba.close();
        id++;
    }
}

void OrdenamientoQuick::guardarArchivos(int arreglo[], int tamano) {
    int id = obtenerSiguienteID();
    
    stringstream ss;
    ss << "salida_quicksort" << id;
    string base = ss.str();
    
    ofstream fTxt((base + ".txt").c_str());
    ofstream fCsv((base + ".csv").c_str());
    ofstream fXml((base + ".xml").c_str());
    ofstream fHtml((base + ".html").c_str());
    ofstream fJson((base + ".json").c_str());
    
    // Encabezados
    fTxt << "=== ESTADO FINAL DEL ARREGLO ORDENADO ===\n";
    fCsv << "Indice,Valor\n";
    fXml << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Arreglo>\n";
    fHtml << "<!DOCTYPE html>\n<html>\n<body>\n<h2>Arreglo Ordenado (Quick Sort)</h2>\n<ul>\n";
    fJson << "{\n  \"elementos\": [\n";

    if (tamano == 0) {
        fTxt << "El arreglo esta vacio.\n";
    }

    for (int i = 0; i < tamano; i++) {
        // TXT
        fTxt << "Indice [" << i << "]: " << arreglo[i] << "\n";
        
        // CSV
        fCsv << i << "," << arreglo[i] << "\n";
        
        // XML
        fXml << "  <Elemento>\n    <Indice>" << i << "</Indice>\n    <Valor>" << arreglo[i] << "</Valor>\n  </Elemento>\n";
        
        // HTML
        fHtml << "  <li>Índice " << i << ": <strong>" << arreglo[i] << "</strong></li>\n";
        
        // JSON
        if(i > 0) fJson << ",\n";
        fJson << "    {\n      \"indice\": " << i << ",\n      \"valor\": " << arreglo[i] << "\n    }";
    }

    fXml << "</Arreglo>\n";
    fHtml << "</ul>\n</body>\n</html>\n";
    fJson << "\n  ]\n}\n";

    fTxt.close(); 
    fCsv.close(); 
    fXml.close(); 
    fHtml.close(); 
    fJson.close();
    
    cout << "\n[EXITO] Archivos guardados como " << base << ".* (txt, csv, xml, html, json)\n";
}

void OrdenamientoQuick::intercambiar(int& a, int& b) {
    int temporal = a;
    a = b;
    b = temporal;
}

int OrdenamientoQuick::particion(int arreglo[], int bajo, int alto) {
    int pivote = arreglo[alto]; 
    int i = (bajo - 1); 

    for (int j = bajo; j <= alto - 1; j++) {
        if (arreglo[j] <= pivote) {
            i++;
            intercambiar(arreglo[i], arreglo[j]);
        }
    }
    intercambiar(arreglo[i + 1], arreglo[alto]);
    return (i + 1);
}

void OrdenamientoQuick::ordenar(int arreglo[], int bajo, int alto) {
    if (bajo < alto) {
        int pi = particion(arreglo, bajo, alto);

        ordenar(arreglo, bajo, pi - 1);
        ordenar(arreglo, pi + 1, alto);
    }
}

void OrdenamientoQuick::imprimirArreglo(int arreglo[], int tamano) {
    for (int i = 0; i < tamano; i++) {
        cout << "[" << arreglo[i] << "] ";
    }
    cout << endl;
}
