#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

Grafo::Grafo(string nombreArchivo) {
    archivo = nombreArchivo;
    cargar();
}

bool Grafo::existeArista(const string& a, const string& b) const {
    auto it = adyacencia.find(a);
    if (it == adyacencia.end()) return false;
    return find(it->second.begin(), it->second.end(), b) != it->second.end();
}

void Grafo::agregarNodo(const string& nodo) {
    if (adyacencia.count(nodo)) {
        cout << "El nodo \"" << nodo << "\" ya existe.\n";
        return;
    }
    adyacencia[nodo]; // crea el nodo con su lista de vecinos vacia
    guardar();
    cout << "Nodo \"" << nodo << "\" agregado y guardado en " << archivo << "\n";
}

void Grafo::eliminarNodo(const string& nodo) {
    if (!adyacencia.count(nodo)) {
        cout << "El nodo \"" << nodo << "\" no existe.\n";
        return;
    }
    for (auto& par : adyacencia) {
        auto& vecinos = par.second;
        vecinos.erase(remove(vecinos.begin(), vecinos.end(), nodo), vecinos.end());
    }
    adyacencia.erase(nodo);
    guardar();
    cout << "Nodo \"" << nodo << "\" eliminado y guardado en " << archivo << "\n";
}

void Grafo::agregarArista(const string& a, const string& b) {
    if (existeArista(a, b)) {
        cout << "La arista " << a << "-" << b << " ya existe.\n";
        return;
    }
    adyacencia[a].push_back(b);
    adyacencia[b].push_back(a);
    guardar();
    cout << "Arista " << a << "-" << b << " agregada y guardada en " << archivo << "\n";
}

void Grafo::eliminarArista(const string& a, const string& b) {
    if (!existeArista(a, b)) {
        cout << "La arista " << a << "-" << b << " no existe.\n";
        return;
    }
    auto& va = adyacencia[a];
    va.erase(remove(va.begin(), va.end(), b), va.end());
    auto& vb = adyacencia[b];
    vb.erase(remove(vb.begin(), vb.end(), a), vb.end());
    guardar();
    cout << "Arista " << a << "-" << b << " eliminada y guardada en " << archivo << "\n";
}

void Grafo::mostrarGrafo() const {
    if (adyacencia.empty()) {
        cout << "\nEl grafo esta vacio.\n";
        return;
    }
    cout << "\n--- Grafo actual ---\n";
    for (const auto& par : adyacencia) {
        cout << par.first << " -> ";
        if (par.second.empty()) {
            cout << "(sin conexiones)";
        } else {
            for (size_t i = 0; i < par.second.size(); i++) {
                cout << par.second[i];
                if (i != par.second.size() - 1) cout << ", ";
            }
        }
        cout << "\n";
    }
}

void Grafo::mostrarCamino(const string& origen, const string& destino) const {
    if (!adyacencia.count(origen) || !adyacencia.count(destino)) {
        cout << "Uno o ambos nodos no existen en el grafo.\n";
        return;
    }
    if (origen == destino) {
        cout << "Ya estas en el nodo \"" << origen << "\".\n";
        return;
    }

    // BFS: en un grafo sin peso, el camino mas corto (menos pasos) es siempre
    // el mas conveniente, y BFS lo encuentra de forma garantizada.
    map<string, string> padre;
    map<string, bool> visitado;
    queue<string> cola;
    visitado[origen] = true;
    cola.push(origen);
    bool encontrado = false;

    while (!cola.empty() && !encontrado) {
        string actual = cola.front();
        cola.pop();
        for (const string& vecino : adyacencia.at(actual)) {
            if (!visitado[vecino]) {
                visitado[vecino] = true;
                padre[vecino] = actual;
                if (vecino == destino) { encontrado = true; break; }
                cola.push(vecino);
            }
        }
    }

    if (!encontrado) {
        cout << "No existe ningun camino entre " << origen << " y " << destino << ".\n";
        return;
    }

    vector<string> camino;
    string nodo = destino;
    while (nodo != origen) {
        camino.push_back(nodo);
        nodo = padre[nodo];
    }
    camino.push_back(origen);

    cout << "El camino mas conveniente de " << origen << " hacia " << destino << " es: ";
    for (auto it = camino.rbegin(); it != camino.rend(); ++it) {
        cout << *it;
        if (it + 1 != camino.rend()) cout << " -> ";
    }
    cout << " (" << (camino.size() - 1) << " pasos)\n";
}

void Grafo::guardar() {
    ofstream out(archivo);

    out << "NODOS\n";
    for (const auto& par : adyacencia) out << par.first << "\n";

    out << "ARISTAS\n";
    for (const auto& par : adyacencia) {
        for (const string& vecino : par.second) {
            if (par.first < vecino) out << par.first << "-" << vecino << "\n";
        }
    }
}

void Grafo::cargar() {
    ifstream in(archivo);
    if (!in.is_open()) return; // todavia no existe, se creara al guardar por primera vez

    string linea;
    bool leyendoAristas = false;

    while (getline(in, linea)) {
        if (linea.empty()) continue;
        if (linea == "NODOS") { leyendoAristas = false; continue; }
        if (linea == "ARISTAS") { leyendoAristas = true; continue; }

        if (!leyendoAristas) {
            adyacencia[linea];
        } else {
            size_t pos = linea.find('-');
            if (pos != string::npos) {
                string a = linea.substr(0, pos);
                string b = linea.substr(pos + 1);
                adyacencia[a].push_back(b);
                adyacencia[b].push_back(a);
            }
        }
    }
}
