#include "MergeSort.h"
#include <sstream> 

int OrdenamientoMerge::obtenerSiguienteID() {
    int id = 1;
    while(true) {
        stringstream ss;
        ss << "salida_mergesort" << id << ".txt";
        string nombreTest = ss.str();
        
        ifstream archivoPrueba(nombreTest.c_str());
        if(!archivoPrueba.good()) { 
            return id;
        }
        archivoPrueba.close();
        id++;
    }
}

void OrdenamientoMerge::guardarArchivos(int arreglo[], int tamano) {
    int id = obtenerSiguienteID();
    
    stringstream ss;
    ss << "salida_mergesort" << id;
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
    fHtml << "<!DOCTYPE html>\n<html>\n<body>\n<h2>Arreglo Ordenado (Merge Sort)</h2>\n<ul>\n";
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

void OrdenamientoMerge::mezclar(int arreglo[], int izquierda, int medio, int derecha) {
    int n1 = medio - izquierda + 1;
    int n2 = derecha - medio;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arreglo[izquierda + i];
    for (int j = 0; j < n2; j++) R[j] = arreglo[medio + 1 + j];

    int i = 0, j = 0, k = izquierda;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arreglo[k] = L[i];
            i++;
        } else {
            arreglo[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arreglo[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arreglo[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void OrdenamientoMerge::ordenar(int arreglo[], int izquierda, int derecha) {
    if (izquierda < derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;

        ordenar(arreglo, izquierda, medio);
        ordenar(arreglo, medio + 1, derecha);

        mezclar(arreglo, izquierda, medio, derecha);
    }
}

void OrdenamientoMerge::imprimirArreglo(int arreglo[], int tamano) {
    for (int i = 0; i < tamano; i++) {
        cout << "[" << arreglo[i] << "] ";
    }
    cout << endl;
}
